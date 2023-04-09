from paho.mqtt.client import Client
from django.conf import settings
import json
from django.utils import timezone


def on_connect(mqtt_client, userdata, flags, rc):
    if rc == 0:
        print("server connected to MQTT Broker successfully")

        from mqtt.models import Device
        mqtt_client.subscribe([(device[0],2) for device in Device.objects.all().values_list('id')])

    else:
        print('Bad Connection rc= '+str(rc))

def on_message(mqtt_client,userdata,message):
    
    from mqtt.models import Device,DevicePowerLog,DeviceTimerLog

    try:
        data=json.loads(message.payload)
        event=data["event"]
        device=Device.objects.get_or_create(id=message.topic)[0]
        
        if event=="status":

            device.status=data["value"]
            device.save(update_fields=["status","updatedAt"])

            
            timerLogLatest=DeviceTimerLog.objects.filter(deviceId=device)
            if len(timerLogLatest)==0 or device.status==True:
                timerLog=DeviceTimerLog()
                timerLog.deviceId=device
                timerLog.startTime=timezone.now()
                timerLog.save()

            timerLogLatest=timerLogLatest=DeviceTimerLog.objects.filter(deviceId=device).latest('deviceId','startTime')
            print(timerLogLatest)
            if(device.status==False and timerLogLatest.endTime==None and timerLogLatest.startTime!=None):
                timerLogLatest.endTime=timezone.now()
                timerLogLatest.save(update_fields=["endTime"])

        elif event=="data":

            timerLog=DeviceTimerLog.objects.filter(deviceId=device).latest("deviceId","startTime")
            
            device.power=data["power"]
            device.current=data["current"]
            device.voltage=data["voltage"]

            log=DevicePowerLog()
            log.logId=timerLog
            log.power=device.power
            log.save()
        
            device.save(update_fields=["power","current","voltage","updatedAt"])
            

    except Exception as e:
        print(message.payload,e)


client=Client()
client.on_connect=on_connect
client.on_message=on_message

client.connect(
    host=settings.MQTT_SERVER,
    port=settings.MQTT_PORT,
    keepalive=settings.MQTT_KEEPALIVE
)
from channels.generic.websocket import WebsocketConsumer
from asgiref.sync import async_to_sync
import channels.layers
import json


from websocket.models import Client

class powerMonitorConsumer(WebsocketConsumer):
    def connect(self):


        async_to_sync(self.channel_layer.group_add)(
            "deviceGroup",self.channel_name
        )
            
        self.accept()

        print("connected "+self.channel_name)

        from mqtt.models import Device
        for instance in Device.objects.all():
            data=toJson(instance)
            self.send_message({"message":data})

    def receive(self, text_data=None, bytes_data=None):
        requestData=json.loads(text_data)
        if(requestData["request"]=="result"):
            from mqtt.models import Device
            from django.db.models import Sum

            totalUnit=Device.objects.aggregate(Sum("unit"))
            rawData={
                "content":"result",
                "totalUnit":totalUnit["unit__sum"]
            }
            data=json.dumps(rawData)

            print(self.channel_name)

            self.send_message({"message":data})
    
    def send_message(self,event):
        self.send(event["message"])

    def disconnect(self,close_code):
        print("connection disconnected for "+self.channel_name)  

        async_to_sync(self.channel_layer.group_discard)(
            "deviceGroup",self.channel_name
        )


def sendDatatoClient(sender,instance,**kwargs):
    print("received",sender,instance)
    channel_layer=channels.layers.get_channel_layer()
    data=toJson(instance)
    print(data)
            
    async_to_sync(channel_layer.group_send)(
        "deviceGroup",
        {
            "type":"send.message",
            "message":data,
            
        })

    from mqtt.models import Device
    from django.db.models import Sum

    totalUnit=Device.objects.aggregate(Sum("unit"))
    total_unit=totalUnit["unit__sum"]
    remaining_unit=100-total_unit #slab-1

    data={}
    for instance in Device.objects.all():
        data[instance.id]={}
        data[instance.id]["prev_percent_rate"]=instance.unit/total_unit
    
        #for slab-1 100
        data[instance.id]["allot_usage_limit"]=data[instance.id]["prev_percent_rate"]*remaining_unit

    for instance in data:
        sendData=json.dumps({
            "content":"deviceLimit",
            "deviceId":instance,
            "value":data[instance]["allot_usage_limit"]
        })
        async_to_sync(channel_layer.group_send)(
            "deviceGroup",
            {
                "type":"send.message",
                "message":sendData
            }

        )

    
def toJson(instance):
    return json.dumps({
                "content":"deviceInfo",
                "deviceId":instance.id,
                "power":instance.power,
                "current":instance.current,
                "voltage":instance.voltage,
                "modified":instance.updatedAt.ctime(),
                "status":instance.status,
                "unit":instance.unit})
    
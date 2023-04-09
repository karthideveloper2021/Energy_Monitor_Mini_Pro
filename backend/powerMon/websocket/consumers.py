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
            data=json.dumps({
                "deviceId":instance.id,
                "power":instance.power,
                "current":instance.current,
                "voltage":instance.voltage,
                "modified":instance.updatedAt.ctime(),
                "status":instance.status
            })
            async_to_sync(self.channel_layer.group_send)(
                "deviceGroup",
                {
                    "type":"send.message",
                    "message":data,
                })

    def receive(self, text_data=None, bytes_data=None):
        print(text_data)
    
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
    data=json.dumps({
                "deviceId":instance.id,
                "power":instance.power,
                "current":instance.current,
                "voltage":instance.voltage,
                "modified":instance.updatedAt.ctime(),
                "status":instance.status

            })
    print(data)
    async_to_sync(channel_layer.group_send)(
        "deviceGroup",
        {
            "type":"send.message",
            "message":data,
            
        })
    
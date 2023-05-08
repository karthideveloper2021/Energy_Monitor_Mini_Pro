from django.db import models
from django.db.models.signals import post_save
from websocket.consumers import sendDatatoClient

# Create your models here.
class Device(models.Model):
    id=models.CharField(max_length=5,primary_key=True)
    deviceName=models.CharField(max_length=12,default="")
    status=models.BooleanField(default=False)
    power=models.FloatField(default=0)
    voltage=models.FloatField(default=0)
    current=models.FloatField(default=0)
    unit=models.FloatField(default=0)
    powerRate=models.FloatField(default=0)
    updatedAt=models.DateTimeField(auto_now=True)
    registeredAt=models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return str(self.id)

class DeviceTimerLog(models.Model):
    deviceId=models.ForeignKey(Device,on_delete=models.CASCADE)
    startTime=models.DateTimeField()
    endTime=models.DateTimeField(null=True,blank=True)
    averagePower=models.FloatField(default=0)

    def __str__(self):
        return str(self.deviceId)+" -- [ "+str(self.startTime.astimezone())+" : "+str(self.endTime.astimezone() if self.endTime!=None else None)+" ]"

class DevicePowerLog(models.Model):
    logId=models.ForeignKey(DeviceTimerLog,on_delete=models.CASCADE)
    power=models.FloatField()
    createdAt=models.DateTimeField(auto_now_add=True)

    def __str__(self):
        
        return str(self.logId)

    
post_save.connect(sendDatatoClient,sender=Device)
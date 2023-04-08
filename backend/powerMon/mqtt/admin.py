from django.contrib import admin
from  mqtt.models import Device,DevicePowerLog,DeviceTimerLog


# Register your models here.
class DeviceAdminView(admin.ModelAdmin):
    list_display=[
        "id",
        "status",
        "power",
        "voltage",
        "current",
        "updatedAt",
        "registeredAt"
    ]


class DevicePowerLogAdminView(admin.ModelAdmin):
    list_display=[
        "id",
        "logId",
        "power",
        "createdAt"
    ]

class DeviceTimerLogAdminView(admin.ModelAdmin):
    list_display=[
        "deviceId",
        "startTime",
        "endTime"
    ]

admin.site.register(Device,DeviceAdminView)
admin.site.register(DevicePowerLog,DevicePowerLogAdminView)
admin.site.register(DeviceTimerLog,DeviceTimerLogAdminView)
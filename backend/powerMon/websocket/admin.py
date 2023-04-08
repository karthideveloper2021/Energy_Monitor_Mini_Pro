from django.contrib import admin
from websocket.models import Client

# Register your models here.

class ClientAdminView(admin.ModelAdmin):
    list_display=[
        "id",
        "created"
    ]

admin.site.register(Client,ClientAdminView)
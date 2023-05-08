from django.urls import path
from websocket import views

urlpatterns=[
    path("home",views.home),
    path("device/all",views.listAll),
    path("sendAlert",views.sendAlert),
]
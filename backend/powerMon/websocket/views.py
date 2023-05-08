from django.shortcuts import render
from django.http import HttpResponse,JsonResponse
from mqtt.models import Device
from telegramBot import telegram

# Create your views here.
def home(request):
    return render(request,"home.html")

def listAll(request):
    devices=[device[0] for device in Device.objects.all().values_list("id")]
    json={
        'devices':devices
    }
    return JsonResponse(json)

def sendAlert(request):
    telegram.sendMessage("Alert user!!")
    return HttpResponse("OK")

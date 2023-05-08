import requests
from django.conf import settings

def sendMessage(message):
    url="https://api.telegram.org/bot"+settings.TELEGRAM_API+"/sendMessage?chat_id=1158294284&text="+message
    response=requests.get(url)
    if(response.status_code==200):
        print("Message sent to the user")

    else:
        print("Error : sending the alert...")
    
    
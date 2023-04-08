from django.urls import path
from websocket.consumers import powerMonitorConsumer

websocket_urlpatterns=[
    path("device/<str:deviceId>",powerMonitorConsumer.as_asgi())
]


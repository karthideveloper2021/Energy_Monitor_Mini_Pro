from django.urls import path
from websocket.consumers import powerMonitorConsumer

websocket_urlpatterns=[
    path("device/",powerMonitorConsumer.as_asgi())
]


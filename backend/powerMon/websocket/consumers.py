from channels.generic.websocket import WebsocketConsumer

class powerMonitorConsumer(WebsocketConsumer):
    def connect(self):
        self.accept()

        print("connected")

    def receive(self, text_data=None, bytes_data=None):
        print(text_data)

    def disconnect(self,close_code):
        print("connection disconnected for ")        
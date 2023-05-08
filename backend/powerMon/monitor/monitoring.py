import threading,time



class MonitorApp(threading.Thread):
    def _init__(self):
        super.__init__(self)

    def run(self) :
        from mqtt.models import Device
        while True:
            # print(Device.objects.all().values())
            time.sleep(2)


monitor_app=MonitorApp()
monitor_app.daemon=True
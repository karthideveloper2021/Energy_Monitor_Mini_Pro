#include "volt.cpp"
#include "current.cpp"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

struct deviceInfo
{
  float power,voltage,current;
  String id;
  bool statusFlag=false;
};

void reconnect();
void process(deviceInfo);
void publishStatus(String,bool);
void publishData(deviceInfo);

Voltage voltSensor;
Current currentSensor1;
Current currentSensor2;
Current currentSensor3;

int voltPin=32;
float voltage=0; //buffer


const char* ssid="karthiLap";
const char* password="KarthiPc";
const char* server = "192.168.137.1";
const int port= 1883;

WiFiClient espWiFiClient; //
PubSubClient mqttClient(espWiFiClient);

DynamicJsonDocument data(1024);

String Jsondata;  //buffer


deviceInfo device1,device2,device3;



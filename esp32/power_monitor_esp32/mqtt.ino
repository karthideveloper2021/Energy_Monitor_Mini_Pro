void reconnect()
{
  while(!mqttClient.connected())
  {
    Serial.println("Attempting MQTT Connection..");
    mqttClient.connect("PowerMon device");
  }
  Serial.println("Connected");
}


void publishStatus(String id,bool value){
  Jsondata="";
  data.clear();
  data["event"]="status";
  data["value"]=value;
  serializeJson(data, Jsondata);
  mqttClient.publish(id.c_str(),Jsondata.c_str()); 
}

void publishData(struct deviceInfo device){
  Jsondata="";
  data.clear();
  data["event"]="data";
  data["voltage"]=device.voltage;
  data["current"]=device.current;
  data["power"]=device.power;
  serializeJson(data,Jsondata);
  mqttClient.publish(device.id.c_str(),Jsondata.c_str()); 
}

void publishDatatoDebug(){
  Jsondata="";
  Jsondata="voltage: "+ String(voltage)+"\n"+"c1: "+String(device1.current)+"c2: "+String(device2.current)+"c3: "+String(device3.current)+"\n"+"p1: "+String(device1.power)+"p2: "+String(device2.power)+"p3: "+String(device3.power);
  mqttClient.publish("debug",Jsondata.c_str()); 
}
void setup() {

  // put your setup code here, to run once:
  voltSensor.calibrate(voltPin,42,3.2266);     //(pin, ghost_value/initial_value,calibrated_scaleup_value);   242/75

  currentSensor1.calibrate(39,28,0.01384);  //0.01384(0.18/13)
  currentSensor2.calibrate(34,28,0.01384);

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("\nConnecting...");
  mqttClient.setServer(server,port);
  mqttClient.setKeepAlive(60);

  device1.id="1001";
  device2.id="1002";
  device3.id="1003";

}

void loop() {
  // float temp=voltSensor.getVoltage(3000,30);
  // Serial.print(temp);
  // Serial.print(" ");
  // // Serial.println(analogRead(voltPin));

  // temp=currentSensor1.getCurrent(2000);
  // Serial.print(temp,5);
  // Serial.print(" ");
  // temp=currentSensor2.getCurrent(2000);
  // Serial.println(temp,5);







  if(!mqttClient.connected())
  {
    reconnect();
  }

  device1.current=currentSensor1.getCurrent(2000);
  Serial.print(device1.current,4);
  Serial.print(" ");

  device2.current=currentSensor2.getCurrent(2000);
  Serial.println(device2.current,4);

  // device3.current=currentSensor3.getCurrent(2000);

  voltage=voltSensor.getVoltage(3000,30);
  device1.voltage=voltage;
  device2.voltage=voltage;
  device3.voltage=voltage;

  Serial.println(voltage);

  device1.power=device1.voltage*device1.current;
  Serial.print(device1.power);
  Serial.print(" ");

  device2.power=device2.voltage*device2.current;
  Serial.println(device2.power);
  // device3.power=device3.voltage*device3.current;






  process(&device1);
  process(&device2);
  // process(device3);
  

  // data["event"]="status";
  // data["value"]=1;
  // data["power"]=0;
  // data["voltage"]=0;
  // data["current"]=0;




  mqttClient.loop();


}

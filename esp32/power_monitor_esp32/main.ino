void setup() {

  // put your setup code here, to run once:
  voltSensor.calibrate(voltPin,42,3.5571);     //(pin, ghost_value/initial_value,calibrated_scaleup_value);   242/75.....239/92.3831818.....220/61.8464

  currentSensor1.calibrate(39,0.014,1);  //28,0.01384(0.18/13)
  currentSensor2.calibrate(34,0.014,1);
  currentSensor3.calibrate(35,0.014,2.022471);

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.print("\nConnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(100);
  }

  mqttClient.setServer(server,port);
  mqttClient.setKeepAlive(60);
  Serial.println("");
  Serial.println("MQTT server initialized");


  device1.id="1001";
  device2.id="1002";
  device3.id="1003";

}

void loop() {

  if(!mqttClient.connected())
  {
    reconnect();
  }

  // Serial.println(analogRead(35));
  // delay(200);

  device1.current=currentSensor1.getCurrent(100,20);
  Serial.println("New reading.....");
  Serial.print("C1: ");
  Serial.print(device1.current,4);

 
  device2.current=currentSensor2.getCurrent(100,20);
  Serial.print(" C2: ");
  Serial.print(device2.current,4);


  device3.current=currentSensor3.getCurrent(100,20);
  Serial.print(" C3: ");
  Serial.println(device3.current,4);
  
  voltage=voltSensor.getVoltage(3000,30);
  device1.voltage=voltage;
  device2.voltage=voltage;
  device3.voltage=voltage;

  Serial.print("Voltage : ");
  Serial.println(voltage);

  device1.power=device1.voltage*device1.current;
  Serial.print("P1: ");
  Serial.print(device1.power);


  device2.power=device2.voltage*device2.current;
    Serial.print(" P2: ");
  Serial.print(device2.power);

  device3.power=device3.voltage*device3.current;
  Serial.print(" P3: ");
  Serial.println(device3.power);






  process(&device1);
  process(&device2);
  process(&device3);
  

  // data["event"]="status";
  // data["value"]=1;
  // data["power"]=0;
  // data["voltage"]=0;
  // data["current"]=0;



  publishDatatoDebug();   //for debuging
  mqttClient.loop();


}

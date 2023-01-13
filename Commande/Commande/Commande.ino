

#include <ArduinoBLE.h>


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
unsigned long currentTime=0;
unsigned long previousTime=0;
bool ledState=LOW;


void setup() {
  Serial.begin(9600);
  
  pinMode(LEDG, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LEDG, HIGH);
  digitalWrite(LED_BUILTIN, ledState);

  if (!BLE.begin()) {
    while (1);
  }
  
  BLE.setLocalName("Nano 33 BLE (Central)"); 
  BLE.advertise();
}

void loop() {
  currentTime=millis();
  connectToPeripheral();
}

void connectToPeripheral(){
  BLEDevice peripheral;
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();
  
  if (peripheral) {
    BLE.stopScan();
    controlPeripheral(peripheral);
  }
  else{
    digitalWrite(LEDG,HIGH);
    if((currentTime-previousTime)>500){
      previousTime=currentTime;
      ledState=!ledState;
      digitalWrite(LED_BUILTIN,!ledState);
    }

  }
  
}

void controlPeripheral(BLEDevice peripheral) {

  if (peripheral.connect()) {
    digitalWrite(LEDG,LOW);
  }
  else {
    return;
  }



 
    
  
  while (peripheral.connected()) {


  
  }
  Serial.println("- Peripheral device disconnected!");
}
  
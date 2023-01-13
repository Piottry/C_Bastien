#include <ArduinoBLE.h>
      


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
unsigned long currentTime=0;
unsigned long previousTime=0;
bool ledState=LOW;


BLEService gestureService(deviceServiceUuid); 
BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  while (!Serial);  
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LED_BUILTIN, ledState);

  
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  gestureCharacteristic.writeValue(-1);
  BLE.advertise();

}

void loop() {

  currentTime=millis();
  BLEDevice central = BLE.central();

  if(!central){
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    if((currentTime-previousTime)>500){
      Serial.println("- Discovering central device...");
      previousTime=currentTime;
      ledState=!ledState;
      digitalWrite(LED_BUILTIN,!ledState);
    }
  }
  else if(central) {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {

    }
    Serial.println("* Disconnected to central device!");
    
  }
  
}

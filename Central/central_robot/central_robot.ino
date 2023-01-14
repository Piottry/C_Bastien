#include <ArduinoBLE.h>
      


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


BLEService gestureService(deviceServiceUuid); 



void setup() {
  Serial.begin(9600);  
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);

  
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  BLE.advertise();

}

void loop() {
  BLEDevice central = BLE.central();

  if(!central){
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
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

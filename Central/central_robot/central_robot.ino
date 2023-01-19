#include <ArduinoBLE.h>

enum {
  DIRECTION_NONE = -1,
  DIRECTION_UP = 0,
  DIRECTION_RIGHT = 1,
  DIRECTION_DOWN = 2,
  DIRECTION_LEFT =3,

};
      


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int mypos=-1;

BLEService Service(deviceServiceUuid); 
BLEByteCharacteristic Characteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);  
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);

  
  if (!BLE.begin()) {
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(Service);
  Service.addCharacteristic(Characteristic);
  BLE.addService(Service);
  Characteristic.writeValue(-1);
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

    while (central.connected()) {
      if (Characteristic.written()) {
         mypos = Characteristic.value();
         writeMypos(mypos);
       }
    }   
  }
}


void writeMypos(int mypos){
  switch(mypos){
    case DIRECTION_UP:
      Serial.println("UP");
      break;
    case DIRECTION_RIGHT:
      Serial.println("RIGHT");
      break;
    case DIRECTION_DOWN:
      Serial.println("DOWN");
      break;
    case DIRECTION_LEFT:
      Serial.println("LEFT");
      break;
    
  }
}

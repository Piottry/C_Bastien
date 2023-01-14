#include <ArduinoBLE.h>

#define CS 10

#include <SPI.h>


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

unsigned long currentTime=0;
unsigned long previousTime=0;
bool ledState=LOW;

int mypos=-1;
int myoldpos=-1;


void setup() {
  Serial.begin(9600);

  // initialization of SPI port
  SPI.begin(); 
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  delay(100);
  pinMode(CS, OUTPUT);


  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);

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
    digitalWrite(LEDR, HIGH);
    BLE.stopScan();
    controlPeripheral(peripheral);
  }
  else{
    //digitalWrite(LEDG,HIGH);
    if((currentTime-previousTime)>500){
      previousTime=currentTime;
      ledState=!ledState;
      digitalWrite(LEDG,ledState);
      digitalWrite(LEDR,ledState);
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

  if (peripheral.discoverAttributes()) {
    digitalWrite(LEDG,HIGH);
    delay(500);
    digitalWrite(LEDG,LOW);
    delay(500);
  } else {
    peripheral.disconnect();
    return;
  }

  BLECharacteristic Characteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);



  while (peripheral.connected()) {
    float X, Y;
    JSTK2_read(X, Y);
    delay(200);
    if(X>0.5){
      Serial.println("RIGHT");
      mypos=1;
      Characteristic.writeValue((byte)mypos);
    }
    else if(X<-0.5){
      Serial.println("LEFT");
      mypos=3;
      Characteristic.writeValue((byte)mypos);
    }
    else if(Y<-0.5){
      Serial.println("DOWN");
      mypos=2;
      Characteristic.writeValue((byte)mypos);
    }
    else if(Y>0.5){
      Serial.println("UP");
      mypos=0;
      Characteristic.writeValue((byte)mypos);
    }
  }
  Serial.println("- Peripheral device disconnected!");
}

void JSTK2_read(float& X, float& Y) {
  byte* data = new byte[5];

  digitalWrite(CS, LOW); // activation of CS line
  delayMicroseconds(15); // see doc: wait 15us after activation of CS line
  for (int i = 0; i < 5; i++) { // get 5 bytes of data
    data[i] = SPI.transfer(0);
    delayMicroseconds(10); // see doc: wait 10us after sending each data
  }
  digitalWrite(CS, HIGH); // deactivation of CS line
  delay(10);

  X = (data[1] << 8) | data[0]; //recunstruct 10-bit X value

  Y = (data[3] << 8) | data[2]; //recunstruct 10-bit Y value
  //Normalisation
  X -= 512;
  X /= (512 * 1.0);
  Y -= 512;
  Y /= (512 * 1.0);


}
  
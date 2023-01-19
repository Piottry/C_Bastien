#include <ArduinoBLE.h> 

#define CS 10     //"Chip Select" pin that the controller can use to enable or desable the device

#include <SPI.h>  //Lbrary for data exchange with the joystick


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214"; //Uuid of the ArduinoBLE of the robot
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214"; //The Characteristic that the robot is supposed to have (allow data transfer between the 2 Arduino)

unsigned long currentTime=0;
unsigned long previousTime=0;
bool ledState=LOW;




void setup() {
  Serial.begin(9600);

  // initialization of SPI port
  SPI.begin(); 
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  delay(100);
  pinMode(CS, OUTPUT);

  // Initialization of LED's
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);


  if (!BLE.begin()) { //BLE.begin() Initializes the Bluetooth Low Energy device
    while (1);
  }
  
  BLE.setLocalName("Nano 33 BLE (Central)");
  BLE.advertise();    // Allow other peripheral to detect this one 
}

void loop() {
  currentTime=millis();
  connectToPeripheral();
}

void connectToPeripheral(){
  BLEDevice peripheral;
    BLE.scanForUuid(deviceServiceUuid);   // Scan devices that are advertising with a certain Uuid
    peripheral = BLE.available(); // Return the discovered device
  
  if (peripheral) { // Return true if a peripheral has been found
    digitalWrite(LEDR, HIGH); // turn off red LED
    BLE.stopScan();           // We stop the scan since we found our other device
    controlPeripheral(peripheral);
  }
  else{             // If no peripheral found yellow LED blinking
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

  if (peripheral.discoverAttributes()) {    // Discover all of the attribut of the peripheral
    digitalWrite(LEDG,HIGH);
    delay(500);
    digitalWrite(LEDG,LOW);
    delay(500);
  } else {                                  // If no attribut found disconnect
    peripheral.disconnect();
    return;
  }


  while (peripheral.connected()) {
    int mypos=-1;   //What we are going to transfer via the Characteristic
    
    float X, Y;     //Our Joystick coordinate
    JSTK2_read(X, Y);
    delay(100);     //wait between 2 transfer
    if(X>0.5){
      mypos=1;
      Characteristic.writeValue((byte)mypos); //send via the Characteristic mypos as a byte
    }
    else if(X<-0.5){
      mypos=3;
      Characteristic.writeValue((byte)mypos);
    }
    else if(Y<-0.5){
      mypos=2;
      Characteristic.writeValue((byte)mypos);
    }
    else if(Y>0.5){
      mypos=0;
      Characteristic.writeValue((byte)mypos);
    }
  }
}



void JSTK2_read(float& X, float& Y) {
  byte* data = new byte[5];

  digitalWrite(CS, LOW); // Activation of CS line
  delayMicroseconds(15);
  for (int i = 0; i < 5; i++) { // Get 5 bytes of data
    data[i] = SPI.transfer(0);  // send data
    delayMicroseconds(10);
  }
  digitalWrite(CS, HIGH); // Deactivation of CS line
  delay(10);

  X = (data[1] << 8) | data[0]; // Recunstruct 10-bit X value

  Y = (data[3] << 8) | data[2]; // Recunstruct 10-bit Y value
 
  //Normalisation
  X -= 512;
  X /= (512 * 1.0);
  Y -= 512;
  Y /= (512 * 1.0);

}
  
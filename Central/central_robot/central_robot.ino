#include <ArduinoBLE.h>
#include <Servo.h>

enum {  //Different values received via bluetooth
  DIRECTION_NONE = -1,
  DIRECTION_UP = 0,
  DIRECTION_RIGHT = 1,
  DIRECTION_DOWN = 2,
  DIRECTION_LEFT = 3,

};

Servo myservo[4][3];


const char* deviceServiceUuid = "23298108-5bd2-4ca3-ad3b-758a16358bbb"; //Uuid of the ArduinoBLE of the robot
const char* deviceServiceCharacteristicUuid = "23298108-5bd2-4ca3-ad3b-758a16358bbb"; //The Characteristic that the robot is supposed to have (allow data transfer between the 2 Arduino)

int mypos = -1; //Variable that keeps the information received by Bluetooth
bool myvar = true;

BLEService Service(deviceServiceUuid);
BLEByteCharacteristic Characteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {

  myservo[0][0].attach(8);  //Attach the pin 8 to the corresponding Servo
  myservo[0][1].attach(A3);
  myservo[0][2].attach(A2);

  myservo[1][0].attach(11);
  myservo[1][1].attach(12);
  myservo[1][2].attach(13);

  myservo[2][0].attach(2);
  myservo[2][1].attach(3);
  myservo[2][2].attach(A4);

  myservo[3][0].attach(5);
  myservo[3][1].attach(6);
  myservo[3][2].attach(7);



  //Set the different LED mod
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);


  if (!BLE.begin()) { //BLE.begin() Initializes the Bluetooth Low Energy device
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)"); //Set our Nano Name (by using an app who can detect Low Energi device that's the name you gonna see)
  BLE.setAdvertisedService(Service);
  Service.addCharacteristic(Characteristic);
  BLE.addService(Service);
  Characteristic.writeValue(-1); //Set the default value of our caracteristic
  BLE.advertise(); //Allow other peripheral to detect this one 
}

void loop() {
  BLEDevice central = BLE.central();

  if (!central) { // If no peripheral found 
    ini();
    myvar = true;
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    
  } else if (central) {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    ini();
    delay(3000);
    while (central.connected()) {
      if (Characteristic.written()) {
        mypos = Characteristic.value();
        writeMypos(mypos);
      }
      if (myvar == true) {
        stand();
        delay(1000);
        myvar = false;
      }
    }
  }
}


void writeMypos(int mypos) {
  switch (mypos) {
    case DIRECTION_UP:
      forward();
      break;
    case DIRECTION_RIGHT:
      rotateright();
      break;
    case DIRECTION_DOWN:
      break;
    case DIRECTION_LEFT:
      rotateleft();
      break;
  }
}

void ini(){
  for (int i=0;i<4;i++){
  myservo[i][2].write(0);
  delay(100);
  myservo[i][1].write(90);
  delay(100);
  myservo[i][0].write(90);
  delay(100);
  }
}


void stand() {
  for (int i = 0; i < 4; i++) {
    myservo[i][2].write(120);
    myservo[i][1].write(135);
    delay(100);
  }
  for (int i = 0; i < 4; i++) {
    myservo[i][2].write(90);
    myservo[i][1].write(90);
    delay(100);
  }
}

void rotateleft(){
  default_action();
  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(135);
  delay(200);
  myservo[0][2].write(90);
  myservo[0][1].write(90);
  delay(100);
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(135);
  delay(200);
  myservo[3][2].write(90);
  myservo[3][1].write(90);
  delay(100);
  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(100);
  myservo[2][0].write(135);
  delay(200);
  myservo[2][2].write(90);
  myservo[2][1].write(90);
  delay(100);
  myservo[1][2].write(120);
  myservo[1][1].write(135);
  delay(100);
  myservo[1][0].write(135);
  delay(200);
  myservo[1][2].write(90);
  myservo[1][1].write(90);
  delay(100);
  for(i=0;i<4;i++){
    myservo[i][0].write(90);
  }

}
void rotateright(){
  default_action();
  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(45);
  delay(200);
  myservo[0][2].write(90);
  myservo[0][1].write(90);
  delay(100);
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(45);
  delay(200);
  myservo[3][2].write(90);
  myservo[3][1].write(90);
  delay(100);
  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(100);
  myservo[2][0].write(45);
  delay(200);
  myservo[2][2].write(90);
  myservo[2][1].write(90);
  delay(100);
  myservo[1][2].write(120);
  myservo[1][1].write(135);
  delay(100);
  myservo[1][0].write(45);
  delay(200);
  myservo[1][2].write(90);
  myservo[1][1].write(90);
  delay(100);
  for(i=0;i<4;i++){
    myservo[i][0].write(90);
  }
}

void forward() {  //procedure pour avancer

  positionnement_action();


  //patte 3
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(70);
  delay(400);
  myservo[3][2].write(90);
  myservo[3][1].write(90);
  delay(1000);
  
  //allongement patte 0

  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(65);
  delay(400);
  myservo[0][2].write(20);
  delay(300);
  myservo[0][1].write(90);
  myservo[0][1].write(50);

  delay(1000);

  //avancement du corps
  
  myservo[2][2].write(20); 
  myservo[2][1].write(50);
 
  myservo[0][2].write(75); 
  myservo[0][1].write(90);

  myservo[1][0].write(110); 
  myservo[3][0].write(130);

  delay(1000);

  //ajustement poids patte 1
  myservo[1][2].write(120);
  myservo[1][1].write(135);

  delay(400);
  myservo[1][2].write(90);
  myservo[1][2].write(20);
  delay(300);
  myservo[1][1].write(100);
  myservo[1][1].write(50);
  delay(100);
  
  delay(1000);

  //patte 2
  
  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(300);
  myservo[2][0].write(130);
  delay(400);
  myservo[2][2].write(100);  
  myservo[2][2].write(90);
  myservo[2][1].write(100);
  myservo[2][1].write(90);

  delay(1000);  


//avancement corps
  myservo[3][2].write(20); 
  myservo[3][1].write(50);
 
  myservo[1][2].write(75); 
  myservo[1][1].write(90);

  myservo[0][0].write(110); 
  myservo[2][0].write(110);

  delay(1500);

  //patte 2
  
  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(300);
  myservo[2][0].write(80);
  delay(400);
  myservo[2][2].write(100);  
  myservo[2][2].write(90);
  myservo[2][1].write(100);
  myservo[2][1].write(90);

  delay(1500);

//patte 3
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(70);
  delay(400);
  myservo[3][2].write(105);
  myservo[3][2].write(90);
  myservo[3][1].write(115);
  myservo[3][1].write(70);
  delay(3000);  

  
}


void positionnement_action(){ //position du robot lui permettant d'entamer la procedure pour avancer
  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(120);
  delay(400);
  myservo[0][2].write(90);
  myservo[0][1].write(90);
  delay(500);
}

void default_action(){  //position par defaut les 4 pattes sont a 90°

  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(90);
  delay(200);
  myservo[0][2].write(90);
  myservo[0][1].write(90);
  delay(100);
  
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(90);
  delay(200);
  myservo[3][2].write(90);
  myservo[3][1].write(90);
  delay(100);

  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(100);
  myservo[2][0].write(90);
  delay(200);
  myservo[2][2].write(90);
  myservo[2][1].write(90);
  delay(100);

  myservo[1][2].write(120);
  myservo[1][1].write(135);
  delay(100);
  myservo[1][0].write(90);
  delay(200);
  myservo[1][2].write(90);
  myservo[1][1].write(90);
  delay(100);
}

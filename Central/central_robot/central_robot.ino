#include <ArduinoBLE.h>
#include <Servo.h>

enum {
  DIRECTION_NONE = -1,
  DIRECTION_UP = 0,
  DIRECTION_RIGHT = 1,
  DIRECTION_DOWN = 2,
  DIRECTION_LEFT = 3,

};

Servo myservo[4][3];


const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int mypos = -1;
bool myvar = true;

BLEService Service(deviceServiceUuid);
BLEByteCharacteristic Characteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {

  myservo[0][0].attach(8);
  myservo[0][1].attach(A1);
  myservo[0][2].attach(A2);

  myservo[1][0].attach(11);
  myservo[1][1].attach(12);
  myservo[1][2].attach(13);

  myservo[2][0].attach(2);
  myservo[2][1].attach(3);
  myservo[2][2].attach(4);

  myservo[3][0].attach(5);
  myservo[3][1].attach(6);
  myservo[3][2].attach(7);


  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);


  if (!BLE.begin()) {
    while (1)
      ;
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

  if (!central) {
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
        delay(2000);
        myvar = false;
      }
    }
  }
}


void writeMypos(int mypos) {
  switch (mypos) {
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

void ini() {
  for (int i = 0; i < 4; i++) {
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

void forward() {

  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(50);
  myservo[0][0].write(45);
  delay(100);
  myservo[0][2].write(90);
  myservo[0][1].write(90);

  //patte 4
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(50);
  myservo[0][0].write(135);
  delay(100);
  myservo[0][2].write(90);
  myservo[0][1].write(90);


  //allongement patte1

  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(50);
  myservo[0][0].write(90);
  delay(100);
  myservo[0][2].write(70);
  myservo[0][1].write(70);
}

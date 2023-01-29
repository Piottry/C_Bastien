#include <Servo.h>

Servo myservo;



void setup() {
  myservo.attach(3);

}

void loop() {

  myservo.write(90);
  delay(500);
  myservo.write(180);
  delay(1000);
  myservo.write(1);
  delay(1000);

}


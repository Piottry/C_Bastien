#include <Servo.h>
#include <time.h>

Servo myservo[4][3];
int angle[4][3];

const int pin_motors[4][3] = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 }, { 11, 12, 13 } };  //define ports

float alpha1=0, alpha2=0, alpha3=0;

//robot's size ► voir s'il ne faut pas prendre les longueurs entre les pivots

const float hip_length = 35;  
const float thigh_length = 82;
const float tibia_length = 94;

float x=0,y=0, z=0;

//number pi
const float pi = 3.141592654;

void setup() {
  attach_motors();

}

void loop() {
  // put your main code here, to run repeatedly:
  x=0;
  y=150;
  z=0;
  angles();
  delay(300);
  x=20;
  y=60;
  z=20;
  angles();
  delay(300);
  
  

}

void attach_motors(){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].attach(pin_motors[i][j]);
    }
  }
}

void angles(){

   float a,b;
  b = (x >=0 ? 1 : -1) * (sqrt(pow(x,2) + pow(y,2)));

  a = b - hip_length;
  alpha1  = atan2(z,a) + acos((pow(thigh_length,2) - pow(tibia_length,2) + pow(a,2) + pow(z,2) /(2 *thigh_length *sqrt(pow(a,2) + pow(z,2)))));
  alpha2 = acos((pow(thigh_length,2) + pow(tibia_length,2) - pow(a,2) - pow(z,2))/(2 *thigh_length *tibia_length));

  //calculate x-y-z degree
  alpha3 = (b >= 0) ? atan2(y, x) : atan2(-y, -x);
  //trans degree pi->180
  alpha1 = alpha1 / pi * 180;
  alpha2 = alpha2 / pi * 180;
  alpha3 = alpha3 / pi * 180;

  alpha1 = 90 + alpha1;
    alpha2 = alpha2;
    alpha3 -= 90;

  myservo[0][0].write(alpha1);
  myservo[0][1].write(alpha2);
  myservo[0][2].write(alpha3);
  
}







/*//calcul base on the kinematic inverse
void polar_angles(float &alpha1, float &alpha2, float &alpha3, float x, float y; float z){

  float a,b;
  b = (x >=0 ? 1 : -1) * (sqrt(pow(x,2) + pow(y,2)));

  a = b - hip_length;
  alpha1  = atan2(z,a) + acos((pow(thigh_length,2) - pow(tibia_length,2) + pow(a,2) + pow(z,2) /(2 *thigh_length *sqrt(pow(a,2) + pow(z,2)))));
  alpha2 = acos((pow(thigh_length,2) + pow(tibia_length,2) - pow(a,2) - pow(z,2))/(2 *thigh_length *tibia_length));

  //calculate x-y-z degree
  alpha3 = (b >= 0) ? atan2(y, x) : atan2(-y, -x);
  //trans degree pi->180
  alphaa = alphaa / pi * 180;
  alpha2 = alpha2 / pi * 180;
  alpha3 = alpha3 / pi * 180;
  
}

void servo_angles(int nb_leg, float alpha1, float alpha2, float alpha3)
{
  if (nb_leg == 0)
  {
    alpha1 = 90 - alpha1;
    alpha2 = alpha2;
    alpha3 += 90;
  }
  else if (leg == 1)
  {
    alpha1 += 90;
    alpha2 = 180 - alpha2;
    alpha3 = 90 - alpha3;
  }
  else if (leg == 2)
  {
    alpha1 += 90;
    alpha2 = 180 - alpha2;
    alpha3 = 90 - alpha3;
  }
  else if (leg == 3)
  {
    alpha1 = 90 - alpha1;
    alpha2 = alpha2;
    alpha3 += 90;
  }

  servo[nb_leg][0].write(alpha1);
  servo[nb_leg][1].write(alpha2);
  servo[nb_leg][2].write(alpha3);
}

*/


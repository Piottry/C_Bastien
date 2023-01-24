#include <Servo.h>
#include <math.h>

Servo myservo[4][3];
Servo servo;
int angle[4][3];
float x,y, z;
//float initial_coordinate[3]= {x=90, y=180, z=0 };
float current_pos[4][3];
float final_pos[4][3];
int i=0;
float alpha1, beta1, gamma1;

const int pin_motors[4][3] = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 }, { 11, 12, 13 } };  //define ports



//robot's size ► voir s'il ne faut pas prendre les longueurs entre les pivots

const float hip_length = 35;  
const float thigh_length = 82;
const float tibia_length = 94;
int test=1;





void setup() {
  attach_motors();
  Serial.begin(9600);
  //servo.attach(3);
}

void loop() {
  
  static float alpha, beta, gamma;
  int num_leg=0;
  forward();    
  angles(alpha,beta,gamma);
  servo_angle(num_leg,alpha,beta,gamma); 

/*for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].write(0);
    }
  }
  Serial.println("0");
  delay(2000);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].write(90);
    }
  }
Serial.println("90");  
delay(2000);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].write(180);
    }
  }
Serial.println("180");  
delay(2000);*/

 
}

void attach_motors(){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].attach(pin_motors[i][j]);
    }
  }
  /*for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      myservo[i][j].write(0);
    }
  }*/
  
  

  
}





void forward(){
        
  //num_leg 1 && num_leg 3 movement
  
 

  x=0; y=0; z=0;
  delay(300);  

}


void set_pos(int num_leg, float x, float y, float z){
  
}



void angles(volatile float &alpha,volatile float &beta,volatile float &gamma){

  float a,b;
  b = (x >=0 ? 1 : -1) * (sqrt(pow(x,2) + pow(y,2)));

  a = b - hip_length;
  alpha  = atan2(z,a) + acos( ( pow(thigh_length,2) - pow(tibia_length,2) + pow(a,2) + pow(z,2) ) / ( 2 * thigh_length * sqrt(pow(a,2) + pow(z,2) ) ) );
  beta = acos((pow(thigh_length,2) + pow(tibia_length,2) - pow(a,2) - pow(z,2))/(2 *thigh_length *tibia_length));

  //calculate x-y-z degree
  gamma = (b >= 0) ? atan2(y, x) : atan2(-y, -x);
  //trans degree pi->180
  alpha = alpha / PI * 180;
  beta = beta / PI * 180;
  gamma = gamma / PI * 180;


  Serial.println(alpha);
  Serial.println(beta);
  Serial.println(gamma);
  
 // gamma = acos((pow(y,2) + pow(z,2) - pow(thigh_length,2) - pow(tibia_length,2)) / (2 * thigh_length * tibia_length));
 // beta = atan(z / y) + atan((tibia_length * sin(gamma)) / (thigh_length + tibia_length * cos(gamma)));


/*
 //Mael ////////
   theta0= atan2( y / x )
   theta1= acos( ( pow(thigh_length,2) + pow(y,2) + pow(z,2) -pow(tibia_length,2) ) / ( 2 * thigh_length * sqrt( pow(z,2) + pow(y,2) ) ) )
   theta2= acos( ( pow(thigh_length,2) + pow(tibia_length,2) - ( pow(y,2) + pow(z,2) ) ) / ( 2 * tibia_length * thigh_length ) )
*/
}

void servo_angle(int num_leg, float alpha, float beta, float gamma)
{
  if (leg == 0)
  {
    alpha = 90 - alpha;
    beta = beta;
    gamma += 90;
  }
  else if (leg == 1)
  {
    alpha += 90;
    beta = 180 - beta;
    gamma = 90 - gamma;
  }
  else if (leg == 2)
  {
    alpha += 90;
    beta = 180 - beta;
    gamma = 90 - gamma;
  }
  else if (leg == 3)
  {
    alpha = 90 - alpha;
    beta = beta;
    gamma += 90;
  }

  servo[leg][0].write(alpha);
  servo[leg][1].write(beta);
  servo[leg][2].write(gamma);
}




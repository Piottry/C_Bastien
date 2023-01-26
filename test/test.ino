#include <Servo.h>

Servo myservo[4][3];
int myangle[4][3];
int mynewangle[4][3];

bool myvar=true;


void setup() {
  myservo[0][0].attach(8);
  myservo[0][1].attach(A3);
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
  ini();
  delay(3000);

}

void loop() {

if(myvar==true){
  stand();
  delay(5000);
  forward();
  delay(2000);
  myvar=false;
}




}



void ini(){
  for (int i=0;i<4;i++){
  myservo[i][2].write(0);
  myangle[i][2]=0;
  delay(100);
  myservo[i][1].write(90);
  myangle[i][1]=90;
  delay(100);
  myservo[i][0].write(90);
  myangle[i][0]=90;
  delay(100);
  }
}

void stand(){
  for (int i=0;i<4;i++){
    myservo[i][2].write(120);
    myservo[i][1].write(135);
    delay(100);
  }
  for (int i=0;i<4;i++){
    myservo[i][2].write(90);
    myservo[i][1].write(90);
    delay(100);
  }
}

void up(){
  myservo[1][0].write(120);
  delay(2000);
  myservo[2][1].write(120);
  delay(2000);
  myservo[0][2].write(0);
}

void goslowly(int leg,int servo,int newangle){
  if(myangle[leg][servo]-newangle>0){
    for(int t=myangle[leg][servo];t>newangle;t--){
      myservo[leg][servo].write(t);
      delay(10);
    }
  }
  else if(myangle[leg][servo]-newangle<0){
    for(int t=myangle[leg][servo];t<newangle;t++){
      myservo[leg][servo].write(t);
      delay(10);
    }
  }
  else if(myangle[leg][servo]-newangle==0){

  }
  update_angle();
}

void update_angle(){
  for (int i=0;i<4;i++){
    for (int j=0;j<3;j++){
      myangle[i][j]=mynewangle[i][j];
    }
  }

}

void forward() {
//position de depart
  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(120);
  delay(400);
  myservo[0][2].write(90);
  myservo[0][1].write(90);

  //patte 4
  myservo[3][2].write(120);
  myservo[3][1].write(135);
  delay(100);
  myservo[3][0].write(70);
  delay(400);
  myservo[3][2].write(90);
  myservo[3][1].write(90);
  delay(1000);
  //allongement patte1

  myservo[0][2].write(120);
  myservo[0][1].write(135);
  delay(100);
  myservo[0][0].write(65);
  delay(400);
  myservo[0][2].write(20);
  delay(300);
  myservo[0][1].write(50);

  delay(1000);

  //avancement du corps
  
  myservo[2][2].write(20); 
  myservo[2][1].write(50);
 
  myservo[0][2].write(115); 
  myservo[0][1].write(90);

  myservo[1][0].write(110); 
  myservo[3][0].write(130);

  delay(1000);

  //ajustement poids patte 2
  myservo[1][2].write(120);
  myservo[1][1].write(135);

  delay(400);
  myservo[1][2].write(60);
  delay(300);
  myservo[1][1].write(70);
  delay(100);
  
  
 /* myservo[3][2].write(60); 
  myservo[3][1].write(70);
  myservo[1][2].write(90); 
  myservo[1][1].write(90);*/

 
  delay(1000);

  //patte 3

  
  myservo[2][2].write(120);
  myservo[2][1].write(135);
  delay(300);
  myservo[2][0].write(130);
  delay(400);
  myservo[2][2].write(90);
  myservo[2][1].write(90);



  
}


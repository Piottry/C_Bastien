#define CS 10 // CS pin

#include <SPI.h> // call library

void setup()
{
  Serial.begin(9600); // initialization of serial communication
  SPI.begin(); // initialization of SPI port
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  delay(100);
  pinMode(CS, OUTPUT);
}

void loop()
{
  float X, Y; //variables for X axis, Y axis and buttons
  JSTK2_read(X, Y); //read data from pmod (the function modifies the parameters
  delay(250);
  if(X>0.5){
    Serial.println("RIGHT");
  }
  else if(X<-0.5){
    Serial.println("LEFT");
  }
  else if(Y<-0.5){
    Serial.println("DOWN");
  }
  else if(Y>0.5){
    Serial.println("UP");
  }
}

//read X axis, Y axis
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

#include <Servo.h>
 

Servo monservo; //Déclaration de ma classe Servo 


bool etatActuel= false,etatPrecedent = true; //On met l'état précédent en vrai pour éviter la détection de front lors du lancement du programme

int buton_pin=2,myservo_pin=3; //Les différents pins utiles

double angle;


void setup()
{
  Serial.begin(9600);
  //On déclare les modes de fonctionnement de nos composants
  pinMode(buton_pin, INPUT_PULLUP);
  
  //Le servomoteur est relié au port myservo_pin (port 3)
  monservo.attach(myservo_pin);
  
  //L'angle initial est de 90 °
  angle=0;
}

void loop()
{
	etatActuel = digitalRead(buton_pin);
  	bool detecFront=(etatActuel==true)& (etatPrecedent==false);
  
  	if(detecFront){ //Si le bouton est relâché alors on augmente l'angle de 30°
    	angle+=30;
  	}
  	
  	//On envoie au servo-moteur l'angle auquel il doit se déplacer
  	monservo.write(angle);
  
    delay(50);
  	
  	//Si l'angle dépasse 180° on revient à 0 et on ajoute un tour
  	if(angle>180){
    angle=0;
  }

 	etatPrecedent= etatActuel;
}
#include <Servo.h>
Servo servomotor; //definirea obiectului pentru a controla servomotorul

//Primul Senzor Ultrasonic
#define trig1 3 
#define echo1 4

//Al doilea Senzor Ultrasonic
#define trig2 5 
#define echo2 6 

//Definim pinul analogic
double valoareA0; //variabila folosita pentru a citi datele potentiometrului
int unghi; //variabila folosita pentru a converti datele de pe pinul A0 in unghiuri

//Definirea variabilelor
double durata1,durata2; //Variabilele folosite pentru determinarea duratieti undelor de sunet
int distanta1; //Variabilele folosite pentru determinarea distantei
int distanta2;

void setup() {
  pinMode(trig1, OUTPUT); 
  pinMode(echo1, INPUT); 
  pinMode(trig2, OUTPUT); 
  pinMode(echo2, INPUT); 
  Serial.begin(9600); 
  servomotor.attach(9);  //seteaza pinul 9 ca pin de control al motorului
}

void loop() {
  
  valoareA0 = analogRead(A0);
  unghi = map(valoareA0, 0, 1023, -10, 190);
  servomotor.write(unghi);                  
  delay(10);  
  
  digitalWrite(trig1, LOW);
  delayMicroseconds(3);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig1, LOW);

  durata1 = pulseIn(echo1, HIGH);
  distanta1 = durata1 * 0.0343 / 2;
  if(distanta1 > 400) return;

 
  digitalWrite(trig2, LOW);
  delayMicroseconds(3);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig2, LOW);
  durata2 = pulseIn(echo2, HIGH);
  distanta2 = durata2 * 0.0343 / 2;
  if(distanta2 > 400) return;

  //artificiu de calcul pentru a mari precizia potentiometrului
  if(unghi >= -10 && unghi<=-1) {
    unghi = 0;}
  if(unghi > 180  && unghi < 190) {
    unghi = 180;}   
  
  Serial.println (String(unghi)+" "+String(distanta1)+" "+String(distanta2));
  delay(10);   
  
}

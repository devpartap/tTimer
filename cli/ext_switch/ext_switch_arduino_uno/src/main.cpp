#include <Arduino.h>

#define trigPin 12
#define echoPin 13
#define led1 A0
#define led1G A1
#define led2 A2
#define led2G A3
#define led3 A4
#define led3G A5


int distance;
short memo;
bool ledstate = false;
char rd = ' ';

void switchledstate();


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(led1G, INPUT);
  pinMode(led2G, INPUT);
  pinMode(led3G, INPUT);

  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  
  Serial.begin(9600); // Starts the serial communication
}
void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //distance = (pulseIn(echoPin, HIGH) * 0.034) / 2;
  if(((pulseIn(echoPin, HIGH) * 0.034) / 2) <= 10)
  {
    memo++;
  }
  else
  {
    memo = 0;
  }

  if(memo >=3)
  {
    Serial.print('a');
    memo = 0;
    delay(1000);
  }

  rd = Serial.read();
  if(rd == 'b')
  {
    switchledstate();
  } 
}

void switchledstate()
{
  if(ledstate == HIGH)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    
  }
  else
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
  }
  
  ledstate != ledstate;
}
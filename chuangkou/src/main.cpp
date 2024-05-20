#include <Arduino.h>
#include <Stream.h>

int led1 =A2;
int led2 =A3;
int led3 =A4;

char myString;

char Control_LED[]={'1','2','3'};

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available()>=0)
  {
   // Serial.println("aaa");
    myString=Serial.read();
    
    if(myString==Control_LED[0])
    {
      Serial.println("LED1亮");
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
    }
    else if (myString==Control_LED[1])
    {
      Serial.println("LED2亮");
      digitalWrite(led2,HIGH);
      delay(500);
      digitalWrite(led2,LOW);
    }
    else if (myString==Control_LED[2])
    {
      Serial.println("LED3亮");
      digitalWrite(led3,HIGH);
      delay(500);
      digitalWrite(led3,LOW);
      }
  }
}
#include <Servo.h>
Servo myservo;
const int servoPin = 9;
const int buttonPin = 2;
const int posKnob = A0;
const int speedKnob = A1;
int pos = 0;
int spd = 0;
int buttonState = 0;
boolean devRest = false;
void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  pos = analogRead(posKnob);
  spd = analogRead(speedKnob);
  buttonState = digitalRead(buttonPin);
  int pos1 = 100+int((512-pos)*0.04);
  int pos2 = 115+int((512-pos)*0.04);
  int spdNew = 100+int((512-spd)*0.2);

  while(digitalRead(buttonPin) == HIGH){
    delay(10);
    if (digitalRead(buttonPin) == LOW){
      devRest = !devRest;
      if (devRest) {
        Serial.println("resting...");
        myservo.write(pos1);
        delay(100);
        myservo.detach();
        while(digitalRead(buttonPin) == LOW){
          delay(10);
          if(digitalRead(buttonPin) == HIGH){
            myservo.attach(servoPin);
            return;
          }
          
        }
      }
      
    }
  }

  Serial.println("pos pos1 pos2 spd spdNew");
  Serial.print(pos);
  Serial.print("  ");
  Serial.print(pos1);
  Serial.print("  ");
  Serial.print(pos2);
  Serial.print("  ");
  Serial.print(spd);
  Serial.print("  ");
  Serial.println(spdNew);
  myservo.write(pos1);
  delay(spdNew);  
  myservo.write(pos2);
  delay(spdNew);
}

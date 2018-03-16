// Servo akibat sensor ultrasonic 

#include <Servo.h>
#include <NewPing.h> // library included


const int ServoPin = 10; // input pin servo(signal/control)
const int TriggerPin = 3; // Trigger pin HC-SR04
const int EchoPin = 2; // Echo  HC-SR04

// 40 = jarak maks terbaca
NewPing sonar(TriggerPin, EchoPin, 40);
Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(ServoPin);
}

void loop()
{
  int cm = sonar.ping_cm();
  Serial.println(cm); // membaca dalam cm

  int angle = map(cm, 2, 15, 15, 40);
  servo.write(angle);
 
  delay(50); // respon dari servo
}

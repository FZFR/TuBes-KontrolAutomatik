
// Servo akibat sensor ultrasonic 

#include <Servo.h>
#include <NewPing.h> // library included


const int ServoPin = 10; // input pin servo(signal/control)
const int TriggerPin = 3; // Trigger pin HC-SR04
const int EchoPin = 2; // Echo  HC-SR04

// 40 = jarak maks terbaca
NewPing sonar(TriggerPin, EchoPin, 40);

Servo servo;


int sp = null; // setpoint
int cm = sonar.ping_cm(); // jarak dari library

float kp = null;
float ki = null;
float kd = null;

float p,i,d,pid,pidx;
float error,errorx,jumlahe;
long durasi, cm;

void setup() {
  Serial.begin (9600);
  servo.attach(ServoPin);  
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  }

void loop() { 
  error = sp - cm;
  p = error * kp;
  jumlahe = error + errorx;
  i = ki * jumlahe;
  d = error - errorx;
  pid = p + i + d;
  pid = 250.0 - pid;
 
  pidx = sp - pid;
 
  servo.write(pidx);

  if(pidx < 1){
  pidx = 0;
  }
 
  if(pidx > 250){
  pidx = 250;
  }


  digitalWrite(TriggerPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TriggerPin, LOW);
  // durasi = pulseIn(EchoPin, HIGH);
  // jarak = (durasi/2) / 29.1;
  // int cm = sonar.ping_cm();
  Serial.print(cm); 
  Serial.println(" cm");
  Serial.print("PID= ");
  Serial.println(pidx);
  delay(60);

 errorx = error;

}

/*
This is Demonstration the use of Flow Sensor, Ultrasonic, and Servo

The circuit for flow:
Flow Sensor Connections
Yellow(control) --- Pin 6
Red             --- +5V
Black           --- GND     
      
LCD Connections      
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * LCD R/W pin to ground
 * 1K resistor:
 * One end to ground
 * Another end to LCD VO pin (pin 3)
 
 
 The circuit for ultrasonic and servo:
 Yellow(servo)       --- 5
 Trigger(ultrasonic) --- 3
 Echo(ultrasonic)    --- 2
 Red(servo)          --- Vin(depend on what we want, if we want big torque use ±7V)
 Red(ultrasonic)     --- +5V
 Black               --- GND
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>
#include <NewPing.h> // library included


const int ServoPin = 5; // input pin servo(signal/control)
const int TriggerPin = 3; // Trigger pin HC-SR04
const int EchoPin = 2; // Echo  HC-SR04

// 34= jarak maks terbaca
NewPing sonar(TriggerPin, EchoPin, 34);
Servo servo;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

volatile int FlowPulse; //measuring the rising edges of the signal
int Calc;                               
int flowsensor = 6;    //The pin location of the sensor


void setup() {
     Serial.begin(9600);       //This is the setup function where the serial port is initialised,
   servo.attach(ServoPin);
   pinMode(flowsensor, INPUT); //initializes digital pin 2 as an input
   attachInterrupt(0, rpm, RISING); //and the interrupt is attached
   
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("TuBes TF-39-03 Kel. 5");
  
}

void loop() {
    
 {   
 int cm = sonar.ping_cm();
  Serial.println(cm); // membaca dalam cm
  lcd.setCursor(1, 2);
  lcd.print(cm);   // print the Flow Rate
  lcd.print(" cm");
  int angle = map(cm, 34, 17, 17, 2); // can inverse the number row
  servo.write(angle);
  delay(50); // respon dari servo (ms)
}{
 FlowPulse = 0;      //Set NbTops to 0 ready for calculations
 sei();            //Enables interrupts
 delay (1000);      //Wait 1 second
 cli();            //Disable interrupts
 Calc = (FlowPulse * 1 / 7.5); //(Pulse frequency x 1min) / 7.5Q, = flow rate in L/hour 
 Serial.print (Calc, DEC); //Prints the number calculated above
 Serial.print (" L/menit\r\n"); //Prints "L/menit" and returns a  new line
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 2);
  lcd.print(Calc,DEC);   // print the Flow Rate
  lcd.print(" L/menit");
 }
}

void rpm ()     //This is the function that the interupt calls 
{ 
  FlowPulse++;  //This function measures the rising and falling edge of the hall effect sensors signal
} 


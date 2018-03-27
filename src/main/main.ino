/*
Pin: 
Trigger 10
Echo    11
Servo   9
input   5V

*/


#include <Servo.h>
#define trigPin 10
#define echoPin 11

Servo servo;
// int sound = 250;
int q= 50;                                      // aliran
int sp= (0.079*q)+1.63;                         // setpoint aliran dari perhitungan dari mencari persamaan

float kp = 0.022355769;
float ki = 0.000429919;
float kd = 0.290625;

// beberapa parameter penunjang untuk menghitung PID

float p,i,d,pid,pidx;
float error, errorx, jml;
long durasi, jarak, jarak_i;


volatile int sensoralir; //mengukur data naik sinyal sensor alir atau flow meter
int Calc;                               
int hallsensor = 2;    //lokasi pin sensor flowmeter

void rpm ()     //fungsi memanggil interrupts
{ 
 sensoralir++;  //fungsi menghitung data naik dan turun dari hall effect sensor atau sensor aliran


} 
// setup() akan berjalan sekali saja saat awal alat menyala


void setup() {
Serial.begin (9600);
pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
attachInterrupt(0, rpm, RISING); //and the interrupt is attached
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
servo.attach(9);
}


void loop() {
// fungsi PID, KP dan KI sudah diketahui di awal menggunakan rumus Ziegler Nichols ke-1

  error = q - Calc;
  p = error * kp;
  jml = error + errorx;
  i = ki * jml;
  d = error - errorx;
  pid = p + i + d;
  pid = sp - pid;
  pidx = sp - pid;
 
  // myservo.write(pidx);


// menampilkan range error yang di reduksi PID
  if(pidx < 1){
  pidx = 0;
  }
 
  if(pidx > sp){
  pidx = sp;
  }

  
sensoralir = 0;      //Set sensor Flow menajdi 0 untuk perhitungan
 sei();            //mengaktifkan fungsi interrupts
 delay (1000);      //jeda waktu 1 detik
 cli();            //mematikan fungsi interrupts
 Calc = (sensoralir * 60 / 7.5); //(Pulse frequency x 60(menit)) / 7.5Q, = flow rate dalam L/jam 


 Serial.print (Calc, DEC); //mendefinisikan perhitungan untuk ditamplikan di bawah
 Serial.println (" L/hour\r\n"); //Menampilkan "L/jam" dan refresh baris baru
 Serial.print(error);
 Serial.println(" %"); // menampilkan error alat sebenarnya dalam %

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// fungsi untuk menggerakan servo

durasi = pulseIn(echoPin, HIGH);
jarak = (durasi/2) / 29.1;
jarak_i = (17 - jarak); 

        if (jarak_i < sp) {
        servo.write(90);
        }
          else if (jarak_i = sp) {
          servo.write(0);
          }
        
    Serial.print(jarak_i);
    Serial.println(" cm"); // menampilkan data yang didapatkan sensor ultrasonik
    Serial.print("PID= "); // menampilkan error yang direduksi oleh PID
    Serial.println(pidx);
delay(50);  // delay pergerakan servo dalam ms


// tambah kode disini buat kodingan baru
}

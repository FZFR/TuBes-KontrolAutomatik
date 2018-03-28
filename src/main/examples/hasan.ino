/* DISCLAIMER */
// Kodingan ini copy dari https://github.com/Fazzafr/TuBes-KontrolAutomatik

/*
Author: Fazza Fakhri Rabbany (shir0yasha)
GitHub: Fazzafr
*/ 



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
                                     
int sp= 15;                         // setpoint ketinggian dari perhitungan mencari persamaan

float kp = 1;
float ki = 0.1;
float kd = 0.1;

// beberapa parameter penunjang untuk menghitung PID

float p,i,d,pid,pidx;
float error, errorx, jml;
long durasi, jarak;

// setup() akan berjalan sekali saja saat awal alat menyala
void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
servo.attach(9);
}


void loop() {
// fungsi PID, KP dan KI sudah diketahui di awal menggunakan rumus Ziegler Nichols ke-1

  error = sp - jarak;
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

        if (jarak < sp) {
        servo.write(0);
        }
          else if (jarak = sp) {
          servo.write(90);
          }
        
    Serial.print(jarak);
    Serial.println(" cm"); // menampilkan data yang didapatkan sensor ultrasonik
    Serial.print("PID= "); // menampilkan error yang direduksi oleh PID
    Serial.println(pidx);
    delay(60);  // delay pergerakan servo dalam ms


// tambah kode disini buat kodingan baru
}



// Thanks to Fazzafr

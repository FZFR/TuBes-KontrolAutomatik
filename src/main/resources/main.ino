/*
Pin: 
Trigger 4
Echo    5
Servo   7
Flow    2
input   5V
*/


#include <LiquidCrystal.h>
#include <Servo.h>
#define trigPin 4
#define echoPin 5

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

Servo servo;
// int sound = 250;
int q= 50;                                      // aliran, ini parameter yang diubah
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
servo.attach(7);
 
  lcd.begin(16, 2);
  lcd.print("KontrolAutomatik");
  lcd.setCursor(0, 1);
  lcd.print("   Kelompok 5");
  delay(3000);
  lcd.clear();
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
    Serial.println(" cm "); // menampilkan data yang didapatkan sensor ultrasonik
    Serial.print("PID= "); // menampilkan error yang direduksi oleh PID
    Serial.println(pidx);
    lcd.setCursor(0, 0);
    lcd.print("Tinggi: ");   
    lcd.print(jarak_i);
    lcd.print("cm               ");            
    lcd.setCursor(0, 2);
    lcd.print("Flow: ");       
    lcd.print(Calc,DEC);    
    lcd.print("L/jam           ");       


// tambah kode disini buat kodingan baru
}

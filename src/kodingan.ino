
// Kelompok TuBes Kontrol Automatik



#include <Servo.h>

Servo myservo; // obyek servo

const int trigPin = 2;

const int echoPin = 4;

void setup() {
Serial.begin(9600);

myservo.attach(9); // lokasi pin

}

void loop() {

// jaraknya jadi cm

long duration, cm;

pinMode(trigPin, OUTPUT);

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(20);

digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);

duration = pulseIn(echoPin, HIGH);

// waktu ke jarak(koversi)

cm = microsecondsToCentimeters(duration);

// kondisi jarak

if ( cm > 7 && cm < 14)

{

myservo.write(140); // bisa digani posisi servo tergantung nilai terukur

delay(4000);

}

else if ( cm < 8)

{

myservo.write(40); // bisa digani posisi servo tergantung nilai terukur

delay(100);

}

else

{

myservo.write(40); // bisa digani posisi servo tergantung nilai terukur

delay(100);

}

Serial.print(cm);

Serial.print("cm");

Serial.println();

delay(100);

}

long microsecondsToCentimeters(long microseconds) {

// kecepatan suara 340 m/s atau 29 microseconds per centimeter.

// si ultrasonic nge-ping bolak-balik(buang-nerima), jadi untuk mencari jarak objek

// kita ambil setengah jarak tempuh(jadi cuma setengah ping)

return microseconds / 29 / 2;

}

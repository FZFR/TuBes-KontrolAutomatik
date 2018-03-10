volatile int flow_frequency; // mengukur frekuensi sensor flow
unsigned int l_hour; // menghitung liter/jam
unsigned char flowsensor = 2; // pin kontrol input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // fungsi interup
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH);
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING);
   sei();
   currentTime = millis();
   cloopTime = currentTime;
}
void loop ()
{
   currentTime = millis();
   // tiap detik, menghitung dan mengubah jadi liter/jam
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime;
      // Pulse frequency (Hz) = 7.5Q, Q --->  L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flow dalam Liter/jam
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour, DEC); // Print liter/jam
      Serial.println(" L/jam");
   }
}

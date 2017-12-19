#include "Gestore_Robottino.h"

#define PIN_B_R 10
#define PIN_B_L 12

#define PIN_F_R 8
#define PIN_F_L 11

#define PIN_EN_R 9
#define PIN_EN_L 13

#define PIN_TRIG_L 6
#define PIN_ECHO_L 7

Gestore_Robottino g_Robottino(8, 11, 10, 12, 9, 13);

bool a = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_TRIG_L, OUTPUT);
  pinMode(PIN_ECHO_L, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(PIN_TRIG_L, LOW);
  digitalWrite(PIN_TRIG_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_L, LOW);

  long durata = pulseIn(PIN_ECHO_L, HIGH);
  
  if (durata < 350) 
  {
    g_Robottino.Stop();
    delay(1000);
  }
  else
  {
    g_Robottino.For(); 
  }
}

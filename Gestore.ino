#include "Gestore_Robottino.h"
#include "Gestore_US.h" 

#define PIN_B_R 10
#define PIN_B_L 12

#define PIN_F_R 8
#define PIN_F_L 11

#define PIN_EN_R 9
#define PIN_EN_L 13

#define PIN_TRIG_L 4
#define PIN_ECHO_L 5

#define PIN_TRIG_R 6
#define PIN_ECHO_R 7

Gestore_Robottino g_Robottino;
Gestore_US g_US;

void setup() 
{
  pinMode(PIN_TRIG_R, OUTPUT);
  pinMode(PIN_ECHO_R, INPUT);
  g_US.Set_Single_Sensor(PIN_TRIG_R, PIN_ECHO_R, Gestore_US::Unita_di_Misura::NC);
  //g_Robottino.Set_Motor(PIN_F_R, PIN_F_L, PIN_B_R, PIN_B_L, PIN_EN_R, PIN_EN_L);
  //g_Robottino.Set_US(PIN_TRIG_R, PIN_TRIG_L, PIN_ECHO_R, PIN_ECHO_L);
  //g_Robottino.InitPin();
  //g_Robottino.For();
  Serial.begin(9600);
}

void loop()
{
  long a = g_US.Calcola();
  Serial.println(a);
//  if (g_Robottino.GetDistance() < 5) 
//  {
//    Serial.print("IF");
//    Serial.println(g_Robottino.GetDistance());
//    g_Robottino.Back();
//  }
//  else  
//  { 
//    Serial.print("ELSE");
//    Serial.println(g_Robottino.GetDistance());
//    g_Robottino.For();
//  }
}

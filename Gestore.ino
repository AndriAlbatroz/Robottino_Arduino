#include "Gestore_Robottino.h"
 
#define PIN_B_R 10
#define PIN_B_L 12

#define PIN_F_R 8
#define PIN_F_L 11

#define PIN_EN_R 9
#define PIN_EN_L 13

#define PIN_TRIG_R 0
#define PIN_ECHO_R 0

#define PIN_TRIG_L 6
#define PIN_ECHO_L 7

Gestore_Robottino g_Robottino;

void setup() 
{
  g_Robottino.Set_Motor(PIN_F_R, PIN_F_L, PIN_B_R, PIN_B_L, PIN_EN_R, PIN_EN_L);
  g_Robottino.Set_US(PIN_TRIG_R, PIN_ECHO_R,PIN_TRIG_L, PIN_ECHO_L);
  g_Robottino.InitPin();
}

void loop()
{
  long dist = g_Robottino.GetDistance();
}

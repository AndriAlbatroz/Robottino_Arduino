/*********************************************************
 * 
 * Powered by: AndriAlbatroz
 * 
 * A simple library for controll two DC motors linked to a 
 * L298N motor driver (2 h bridge) and read the values of
 * the 2 HC-SR04 sensors
 * 
 * FileName: Source Code of the library
 * 
*********************************************************/

// Inclued all the lib's that i need
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "Gestore_Robottino.h"

// Constructor
Gestore_Robottino::Gestore_Robottino()
{ 
  offset = 200;
  SetState(_Stato::Init_);
}

// Function return the state value
Gestore_Robottino::_Stato Gestore_Robottino::GetState()
{
  return _stato; 
}

// Function set the state value
void Gestore_Robottino::SetState(_Stato stato)
{
  _stato = stato;
}

// Function for sett the pins of the 2 motors
void Gestore_Robottino::Set_Motor(int pin_f_r_, int pin_f_l_, int pin_b_r_, int pin_b_l_, int pin_en_r_, int pin_en_l_)
{
  pin_f_r = pin_f_r_;
  pin_f_l = pin_f_l_;
  pin_b_r = pin_b_r_;
  pin_b_l = pin_b_l_;
  pin_en_r = pin_en_r_;
  pin_en_l = pin_en_l_;
}

// Function for set the pins of the 2 sensors
void Gestore_Robottino::Set_US(int pin_us_trig_r_, int pin_us_trig_l_, int pin_us_echo_r_, int pin_us_echo_l_)
{
  pin_us_trig_r = pin_us_trig_r_;
  pin_us_trig_l = pin_us_trig_l_;
  pin_us_echo_r = pin_us_echo_r_;
  pin_us_echo_l = pin_us_echo_l_;
}

// Function for init the pins IN/OUT
void Gestore_Robottino::InitPin() 
{
  pinMode(pin_f_r, OUTPUT);
  pinMode(pin_f_l, OUTPUT);
  pinMode(pin_b_r, OUTPUT);
  pinMode(pin_b_l, OUTPUT);
  pinMode(pin_en_r, OUTPUT);
  pinMode(pin_en_l, OUTPUT);

  pinMode(pin_us_trig_r, OUTPUT);
  pinMode(pin_us_trig_l, OUTPUT);
  pinMode(pin_us_echo_r, INPUT);
  pinMode(pin_us_echo_l, INPUT);

  Reset();

  digitalWrite(pin_en_r, true);
  digitalWrite(pin_en_l, true);

}

// Function for turn left in the forward direction at the n degrees
void Gestore_Robottino::Turn_For_Left(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++) 
  {
    digitalWrite(pin_f_r, true);
    digitalWrite(pin_b_r, false);
  }

  Reset();

  DecicedeDirecetionNextUS();
}

// Function for turn right in the forward direction at the n degrees
void Gestore_Robottino::Turn_For_Right(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_f_l, true);
    digitalWrite(pin_f_r, false);
  }

  DecicedeDirecetionNextUS();
}

// Function for turn left in the back direction at the n degrees
void Gestore_Robottino::Turn_Back_Left(int degree) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_r, true);
    digitalWrite(pin_b_l, false);
  }

 DecicedeDirecetionNextUS();
}

// Function for turn right in the back direction at the n degrees
void Gestore_Robottino::Turn_Back_Right(int degree)
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_l, true);
    digitalWrite(pin_b_r, false);
  }

  DecicedeDirecetionNextUS();
}
  
// Function for start the robot in the back direction
void Gestore_Robottino::Back() 
{
  Reset();

  SetState(_Stato::Back_);
  
  digitalWrite(pin_b_r, true);
  digitalWrite(pin_b_l, true);
}

// Function for start the robot in the forward direction
void Gestore_Robottino::For() 
{
  Reset();

  SetState(_Stato::Forward_);
  
  digitalWrite(pin_f_l, true);
  digitalWrite(pin_f_r, true);
}

// Function for stop the robot
void Gestore_Robottino::Stop()
{
  SetState(_Stato::Stop_);

  Reset();
}

// Function for reset all the pins
void Gestore_Robottino::Reset()
{
  digitalWrite(pin_f_r, false);
  digitalWrite(pin_f_l, false);
  digitalWrite(pin_b_r, false);
  digitalWrite(pin_b_l, false);
}

// Function for get the ditance in centimeter of the rebot to the 2 sensor
long Gestore_Robottino::GetDistance()
{
  digitalWrite(pin_us_trig_r, false);
  digitalWrite(pin_us_trig_r, true);
  delayMicroseconds(10);
  digitalWrite(pin_us_trig_r, false);
  long distanza_r = 0.034 * pulseIn(pin_us_echo_r, true) / 2;
  
  digitalWrite(pin_us_trig_l, false);
  digitalWrite(pin_us_trig_l, true);
  delayMicroseconds(10);
  digitalWrite(pin_us_trig_l, false);
  
  long distanza_l = 0.034 * pulseIn(pin_us_echo_l, true) / 2;

  return (distanza_l + distanza_r) / 2;  // Return average of the 2 values

}

void Gestore_Robottino::DecicedeDirecetionNextUS()
{
  switch(GetState())
  {
    case _Stato::Forward_:
      For();
    break;
    case _Stato::Back_:
      Back();
    break;
  }
}

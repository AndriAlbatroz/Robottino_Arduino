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
#include "Arduino.h"
#include "Gestore_Robottino.h"

enum _Stato
{
  Init_,
  Forward_,
  Back_,
  Turning_,
  Stop_
};

// Constructor
Gestore_Robottino::Gestore_Robottino()
{ 
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
void Gestore_Robottino::Turn_For_Left(int degree, bool use_previus_direction) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++) 
  {
    digitalWrite(pin_f_r, true);
    digitalWrite(pin_b_r, false);
  }
}

// Function for turn right in the forward direction at the n degrees
void Gestore_Robottino::Turn_For_Right(int degree, bool use_previus_direction) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_f_l, true);
    digitalWrite(pin_f_r, false);
  }

}

// Function for turn left in the back direction at the n degrees
void Gestore_Robottino::Turn_Back_Left(int degree, bool use_previus_direction) 
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_r, true);
    digitalWrite(pin_b_l, false);
  }
}

// Function for turn right in the back direction at the n degrees
void Gestore_Robottino::Turn_Back_Right(int degree, bool use_previus_direction)
{
  if (degree == 0) return;

  Reset();

  for (int i = 0; i <= degree; i++)
  {
    digitalWrite(pin_b_l, true);
    digitalWrite(pin_b_r, false);
  }
}

// Function for start the robot in the back direction
void Gestore_Robottino::Back() 
{
  Reset();

  digitalWrite(pin_b_r, true);
  digitalWrite(pin_b_l, true);
}

// Function for start the robot in the forward direction
void Gestore_Robottino::For() 
{
  Reset();

  digitalWrite(pin_f_l, true);
  digitalWrite(pin_f_r, true);
}

// Function for stop the robot
void Gestore_Robottino::Stop()
{
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
  digitalWrite(pin_us_trig_l, false);

  digitalWrite(pin_us_trig_r, true);
  digitalWrite(pin_us_trig_l, true);
  delayMicroseconds(10);
  digitalWrite(pin_us_trig_r, false);
  digitalWrite(pin_us_trig_l, false);

  long distanza_r = 0.034 * pulseIn(pin_us_echo_r, true) / 2;
  long distanza_l = 0.034 * pulseIn(pin_us_echo_l, true) / 2;

  return (distanza_r + distanza_l) / 2;  // Return average of the 2 values

}

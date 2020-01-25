/*
  ControlManager.cpp - Library for Mapping Control Inputs to MIDI messages
  to simulate different bass guitar features (volume, vibrato...)
  Created by SYDE 361 - Group Joni, July 10, 2019.
  Systems Design Engineering - University of Waterloo
*/

#ifndef ControlManager_h
#define ControlManager_h

#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

class ControlManager
{ 
  public:
    ControlManager(int pot, int threshold, int channel, int type); // constructor
    int read(); // reads the state of the pin
    void check(); // checks whether the pin state has changed (it uses _check) and sends the MIDI message
    void update(); // updates the states of the pin, it saves the previous one
    int currPotValue; // current pin readout value
    int prevPotValue; // previous pin readout value
       
  private:
    int _channel; // MIDI channel to send the message
    int _type; // MIDI control type to which the control manager maps to
    int _pot; // Pin value 
    int _threshold; // threshold for the check function, avoids sending too many messages for small input changes
    bool _check(); // checks that the value change is bigger than the threshold
};

#endif

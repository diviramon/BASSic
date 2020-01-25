/*
  ControlManager.cpp - Library for Mapping Control Inputs to MIDI messages
  to simulate different bass guitar features (volume, vibrato...)
  Created by SYDE 361 - Group Joni, July 10, 2019.
  Systems Design Engineering - University of Waterloo
*/
#include "Arduino.h"
#include "ControlManager.h"

// Constructor for the object, parameters specified in the header file
ControlManager::ControlManager(int pot, int threshold, int channel, int type)
{
  _pot = pot; 
  _threshold = threshold;
  _channel = channel; // 2 for most cases
  _type = type;
  currPotValue = 0; 
  prevPotValue = 0;
}

// Reads current state of the assigned pin
int ControlManager :: read(){
    return analogRead(_pot)/8; // divides the input by 8 to map it from 0 to 127
}

// Saves the current state value
void ControlManager :: update(){
    prevPotValue = currPotValue;
    return;
}

// checks that the value has changed between calls, must be bigger than the threshold
bool ControlManager :: _check(){
    return (abs(prevPotValue - currPotValue) >= _threshold);
}

// main function that is called in main loop, reads the new value, compares it to the threshold and sends the MIDI message
void ControlManager :: check(){
    currPotValue = read(); // new value from the pin
    if (_check()){ // if bigger than threshold
        usbMIDI.sendControlChange(_type,currPotValue,_channel); // sends the appropriate MIDI message based on the control type
        update(); // saves the current state before next read action
    }
}

/*
  BassicString.h - Library for Mapping Capacitive touch board states to MIDI
  messages to simulate a guitar string
  Created by SYDE 361 - Group Joni, July 10, 2019.
  Systems Design Engineering - University of Waterloo
*/

#ifndef BassicString_h
#define BassicString_h

#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

class BassicString
{ 
  public:
    int (&notes) [12]; // MIDI notes for the string
    BassicString(uint8_t i2cAddr, int (&_notes) [12]); // constructor
    void init(); // initialization function, points the I2C bus to the right address and starts it
    void check(); // function to check for any change in the string state
    void update(); // update function for the string states, saves the previous state and reads the new one 
    int vel; // velocity value to measure how hard the sensors are touched
    uint16_t curr_state; // current state of the string
    uint16_t prev_state; // placeholder to save the previous state of the string
       
  private:
    int findMax(); // function to find the highest note that has been touched in the string
    bool isSlide(int n); // function to detect a slide input, also detects hammer on and pull up
    int getSlideDirection(int n); // detects whether the slide is in increasing or decreasing directions
    uint8_t _i2c_addr; // I2C address that points to the correct MPR121 capacitive touch sensor
    Adafruit_MPR121 _capBoard; // MPR121 object
    int32_t _pb_inc; // pitch bend increment for the slide
    int32_t _target_pb; // target pitch bend for when a slide is triggered
    int pb_note; // pitch bend note, the note which initiated the slide
    int32_t pb_value; // current pitch bend value
    bool is_pb; // boolean to specify that the pitch bend has or hasn't terminated
    int maxx; // current max note being played
    int slideDirection; // output from the getSlideDirection function, either 1 or -1
};

#endif

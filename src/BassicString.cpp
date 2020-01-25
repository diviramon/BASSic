/*
  BassicString.cpp - Library for Mapping Capacitive touch board states to MIDI
  messages to simulate a guitar string
  Created by SYDE 361 - Group Joni, July 10, 2019.
  Systems Design Engineering - University of Waterloo
*/

#include "Arduino.h"
#include "BassicString.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

// constructor, input parameteres specified in header file
BassicString::BassicString(uint8_t i2cAddr, int (&_notes) [12]) : notes(_notes)
{
  _i2c_addr = i2cAddr; // Address of the MPR121
  is_pb = false; // no pitch bend to begin with
  pb_note = -1; // notes go from 0 to 11, -1 means no note has sent a pitch bend yet
  slideDirection = 0; // either -1 or 1, zero means no slide is happening
  _target_pb = 0; // no target pitch bend
  pb_value = 0; // no pitch bend initially
  _pb_inc = 11; // pitch bend increment to reach the target, always 11 

  curr_state = 0;
  prev_state = 0;

  _capBoard = Adafruit_MPR121(); // MPR121 object initialization
  vel = 120; // velocity fixed at 120 as no means to measure how hard they were touched
}

// Initialization of the string, starts the I2C bus
void BassicString::init()
{
  _capBoard.begin(_i2c_addr); // begins reading from the MPR121 sensor
  if (!_capBoard.begin(_i2c_addr)) {
    Serial.println("MPR121 not found, check wiring?"); // safe check for wiring failure
    while (1); // infinity loop to halt the execution, needs to reset to load again
  }
}

// Looks for the highest note that is currently touched
int BassicString :: findMax(){
  for (int i = 11; i > -1; i--){ // 12 notes, begin from the highest one
    if (bitRead(curr_state, i)){ // highest note played equals the highest non zero bit in the state
      return i;
    }
  }
  return 0;
}

// Slide check function, it is based on the fact that when a slide gets triggered two consecutive 
// notes are touched.
bool BassicString :: isSlide(int n){
  return (curr_state / prev_state == 3) || (prev_state / curr_state == 3); // any state with two consecutive notes touched will have a 
  // common divisor of 3 or 1/3 (direction dependant) with its previous state
}

// Slide direction change, uses the same logic as above. Common divisor of 3 or 1/3.
int BassicString :: getSlideDirection(int n){
  if(curr_state / prev_state == 3){
    return 1;
  }
  else if (prev_state / curr_state == 3){
    return -1;
  }
  else{
    Serial.println("getSlideDirection Exception! (should not have been called when not in slide)"); // mal function check
    return 0;
  }
}

// saves previous state and reads new one
void BassicString::update()
{
  prev_state = curr_state;
  curr_state = _capBoard.touched();
}

// main function to be called from the main loop
void BassicString::check()
{
     int noteToPlay = 0; // place holder for the mapping of the input to the correct note
     if (curr_state == 0 && is_pb){ // state of zero means nothing has been touched, resets all the parameters
            is_pb = false; 
            slideDirection = 0;
            usbMIDI.sendNoteOff(notes[pb_note],0,2);
            usbMIDI.sendPitchBend(0, 2);
            pb_note = -1;
            _target_pb = 0;
            pb_value = 0;
            maxx = 0;
     }
     
    // Loop through the 12 touch points on the board
    for(int n = 11; n >-1; n--){ // always check higher notes first, since this is a bass string
      if(bitRead(curr_state,n) != bitRead(prev_state,n)){ // checks for a change in the note
        if(n!=0 && isSlide(n)){ // open note cannot slide, otherwise check if a slide was triggered
          is_pb = true; // if slide, pitch bend must be true then
          slideDirection = getSlideDirection(n); // slide direction
          if (_target_pb == 0){ // if the pitch bend has not started:
            if (slideDirection == 1){ // sliding up
              pb_note = n - 1; // save the note that triggered the slide 
            }
            else { // sliding down
              pb_note = n; // save the note that triggered the slide
            }
          }
          _target_pb += (682 * slideDirection); // set the target pitch bend, either 682 or -682 
          maxx = n; // save the max note played
        }
        else if (n >= maxx && bitRead(curr_state, n)){ // new note change detected and it is bigger than the current max
          usbMIDI.sendNoteOff(notes[maxx],0,2); // turn off current note
          maxx = n; // update the max
          usbMIDI.sendNoteOn(notes[n],vel,2); // send MIDI message
        }
        else if (n == maxx && !(is_pb) && !(bitRead(curr_state, n))){ // if no change in any higher than the current max is
          // detected and the current max has turned off:
          usbMIDI.sendNoteOff(notes[n],0,2); // turn off the current note played
          maxx = findMax(); // look for new max
        }    
      }
      else if (is_pb && pb_value != _target_pb){ // if pitch bend is detected
          usbMIDI.sendPitchBend(pb_value, 2); // send the pitch bend MIDI message
          pb_value += (_pb_inc * slideDirection); // increase or decrease (depends on the direction) the current pitch bend value 
      }
  }
}

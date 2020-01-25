/* 
 *  This is the main program for the BASSic guitar created by group Joni
 *  for SYDE 361 - Engineering Design at the University of Waterloo
 */

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "src/BassicString.h"
#include "src/ControlManager.h"

// The following are the MIDI notes mapped from each pin on the capacitive touch sensor boards
// These correspond to pins :
              // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11
int notesG[] = {55,56,57,58,59,60,61,62,63,64,65,66};

// These correspond to pins:
              // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11
int notesD[] = {50,51,52,53,54,55,56,57,58,59,60,61};

// These correspond to pins:
              // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11
int notesA[] = {45,46,47,48,49,50,51,52,53,54,55,56};

// These correspond to pins:
              // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11
int notesE[] = {40,41,42,43,44,45,46,47,48,49,50,51};

// Initialization of string objects used to encapsulate the logic for mapping user input to MIDI messages defined in BassicString.cpp
BassicString E_string(0x5A, notesE);
BassicString A_string(0x5D, notesA);
BassicString G_string(0x5B, notesG);
BassicString D_string(0x5C, notesD);

// Initialization of control objects used to encapsulate the logic for mapping control changes to MIDI control messages defined in ControlManager.cpp
ControlManager volumeControl(A1, 3, 2, 7); // volume control modifier, this is the pedal in our current prototype
ControlManager modControl(A0, 10, 2, 1); // vibrato control modifier, this is the potentiometer in the ideal final design

// Start the I2C bus, each string has its own address
void setup() {
  E_string.init();
  A_string.init();
  G_string.init();
  D_string.init();
}

// Main loop, continuous check for changes in states on any string, or for any input from the control objects
void loop() {
  E_string.update();
  E_string.check();
  A_string.update();
  A_string.check();
  D_string.update();
  D_string.check();
  G_string.update();
  G_string.check();
  volumeControl.check();
  modControl.check();

}

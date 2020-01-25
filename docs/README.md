# BASSic

The BASSic is an accesible bass guitar for people with osteoarthritis. Musical instruments are often recommended as a good therapy treatment for people with arthritis. However, as the disease advances, current instruments become too painful to play. One of the main causes is the weight of the instruments and the required range of motion. Additionally, musical instruments are often expensive. The BASSic aims to solve all these problems!

The BASSic is ergonomic and meets the user needs of people with osteoarthritis. It is very lightweight and it does not require complicating and painful string plucking. Instead, a touch sensitive interface replaces the common strings. Additionally, it uses the power of Teensy and the MIDI communication protocol to simulate the bass music sounds, making it extremely affordable!

## Design

The BASSic can be divided into three main components: neck, body, and control managers. The control managers are external components that can be connected to the body of the prototype to increase its capabilities. The neck of the instrument is the main user interface and it contains 48 touch-sensitive pads. It resembles the strings of a bass guitar by including four rows of 12 pads.  

![BASSic - Top View](/final_design_top.PNG)

The body of the instrument has two main purposes: hold the circuitry and make the playing experience more intuitive. The BASSic uses three 12-key capacitive touch sensros as well as a Teensy 3.5 microcontroller unit. Additionally, the body comes with an adjustable stand. This allows users to change the height of the instrument and to rest their arms while playing.

![BASSic - Side View](/final_design_side.PNG)


## How it works?

Below there is an image of a full working prototype of the BASSic. It comes with a pedal to adjust the volume while playing:

![BASSic - Prototype](/prototype.jpg)

Additionally, an user manual is included to understand better how to interact with it, and how the different notes can be played:

![User - Manual](/User-Manual.pdf)

## Schematics

Here is a full schematic of the circuitry for those interested:

![BASSic - Schematic](/schematic.PNG)

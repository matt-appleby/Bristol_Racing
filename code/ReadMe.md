# Bristol Racing Code Repository

This code repository contains the code base of the Bristol Racing team.

Each folder contains a subproject

## Sub-projects:
***
## PWM
This script is used to generate a 1KHz PWM signal from arduino that outputs to the gate driver
***
## Dyno
Programs to run the dynamometer

Arduino program measures torque and speed.
***
## Variable_signal_generator

This sub-project uses vhdl code to take an input from an arduino and output a variable frequency square wave for use in driving resonanat converters.

It should be implemented by an fpga.

## BatteryTestRig
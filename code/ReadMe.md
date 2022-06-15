<<<<<<< HEAD
# Bristol Racing Code Repository

This code repository contains the code base of the Bristol Racing team.

Each folder contains a subproject

## Sub-projects:
***
## PWM
This script is used to generate a 1KHz PWM signal from arduino that outputs to the gate driver
***
## Tachometer
This script is being developed to measure the rotor speed of the the motor for the test bed and subsequent vehicle. A magnet is attatched to the rotor which induces a voltage in a sensing coil. The code aims to sample the voltage and apply a FFT to the sample to find the oscillation frequency and hence the speed.
***
## Variable_signal_generator
=======
# Bristol Racing Code Repository

This code repository contains the code base of the Bristol Racing team.

Each folder contains a subproject

## Sub-projects:
***
## PWM
This script is used to generate a 1KHz PWM signal from arduino that outputs to the gate driver
***
## Tachometer
This script is being developed to measure the rotor speed of the the motor for the test bed and subsequent vehicle. A magnet is attatched to the rotor which induces a voltage in a sensing coil. The code aims to sample the voltage and apply a FFT to the sample to find the oscillation frequency and hence the speed.
***
## Variable_signal_generator
>>>>>>> 1734ce8afffe917321e1490fada3328602840fea
This sub-project uses vhdl code to take an input from an arduino and output a variable frequency square wave for use in driving resonanat converters.
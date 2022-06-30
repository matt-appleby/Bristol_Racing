# Back of envelope calcs

CarMassKg=100#kg
DriverMassKg=70
g=9.81

MotorOutputSprocket = 12 #Estimate
AxelSprocket = 40 #Estimate
WheelRadius = 0.2 #m estimate
RollingResistance = 0.013 #estimate from https://www.physicsforums.com/threads/go-kart-resistance-force.963450/
#Force From Rolling Resistance F=C*N where N is the normal force 

#MechanicalAdvantage=Forcein/ForceOut
#MechanicalAvantage=AxelSprocket/(MotorOutputSprocket*WheelRadius) #Looks sensible but not sure
MechanicalAdvantage=MotorOutputSprocket/(AxelSprocket*WheelRadius)

AirDensity=1.225
Area = 0.6*0.6 #Very very rough estimate
DragCoeff= 0.295 #This should be experimentally calculated !! Very important!!
#Estimated from shape of bullet, flat plate =1.28, Airfoil 0.045
#Drag equation: F_d= \frac{1}{2} \rho v^2C_DA

#Battery (Would ideally implement a lookup table)
ConstantRaceCurrentCap=20#AHr
Voltage=24#

#Motor (Would ideally implement a lookup table)


#Going to get a graph of speed vs energy
RollingResistanceForce=RollingResistance*g*(CarMassKg+DriverMassKg)

v=[]
F=[]
for v in range(50):
    Drag=Area*AirDensity*DragCoeff*0.5*v^2
    TotalForce=Drag+RollingResistanceForce
    F[x]=TotalForce

#Matplotlib plot F vs v



print()
%% Battery plotting

% the csv file being analysed should be in the format
%   0   |   Seconds     |       Amps    |   Volts     
% the only pre processing should be to remove the data points before and after the battery
% has been disconnected.

RunName= "FreeSpin.csv"
%RunName= "BatteryDischargeTestA15 08 06 2022.csv"



Data = readmatrix(RunName);
[Time, Speed, Torque] = extractData(Data)

%% Discharge characteristic vs time
figure
plot(Time/1000,Speed)
ylabel("Speed")
%hold on
xlabel("Time s")
%yyaxis right
%plot(Time, I)
%ylabel("Current A")
%legend("V","I")
%% Voltage amp hour characteristic
%figure
AmpHrs=(Time.*I/(60^2))
plot(AmpHrs(10:end-25),V(10:end-25))

%hold on
%plot(AmpHrs(10:end-25),movmean(V(10:end-25),100))


xlabel("AHr")
ylabel("V")
title("Battery Discharge Characteristic")
%%
function [Time,Speed, Torque]=extractData(Data)
    Time=Data(3:end, [2]);
    Time=Time-Time(1)
    Speed=Data(3:end, [3]);
    Torque=Data(3:end, [4]);
    
end
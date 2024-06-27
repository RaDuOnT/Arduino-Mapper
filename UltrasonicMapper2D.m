clear all;
clc;

%% Initializare variabile
theta = zeros(1);
rho1 = zeros(1);
rho2 = zeros(1);
i = 1;


%% Setam portul serial
Arduino = serialport('COM8', 9600);  % serial port


%% Setam graficul
%Creare si afisare axe polare
px = polaraxes;
title('Map of the Environment');
px.Color = [0.3010 0.7450 0.9330];
hold on;

%Initializare
plotF = polarplot(px, theta(i)*pi/180, rho1(i), 'w.');
plotB = polarplot(px, (180+theta(i))*pi/180, rho2(i), 'w.');


%% Loop
while(1)
    
    data = readline(Arduino);
    data = regexp(data,'\d*','Match');
    display(data)
    theta(i)= str2double(data(1));
    rho1(i) = str2double(data(2));
    rho2(i) = str2double(data(3));
    

%   theta(i) = 180*rand(1);
%   rho1(i) = 400;
%   rho2(i) = 200;
    
    
    plotF.ThetaData = theta*pi/180;
    plotF.RData = rho1;
    
    plotB.ThetaData = (180+theta)*pi/180;
    plotB.RData = rho2;
    
    
    plotFdir = polarplot(px, [0 theta(i)*pi/180], [0 rho1(i)], '- k');
    plotBdir = polarplot(px, [0 (180+theta(i))*pi/180], [0 rho2(i)], '- k');
    
    refreshdata(plotF);
    refreshdata(plotB);
    drawnow;
    hold on;
    
    delete(plotFdir);
    delete(plotBdir);
    
    i = i + 1;
    %pause(0.1);
end;
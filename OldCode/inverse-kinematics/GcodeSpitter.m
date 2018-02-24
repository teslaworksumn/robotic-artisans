% Implement by initializing in `rArmSimulator.m` before you run you paths in
% matlab, add in this bit of code to DroboticArmSim.m at the end before the
%'draw now' function:
 
%     controlAngle3 = atand(endpt(3,1)/endpt(3,2));
%     lengthCarm1 = sqrt(endpt(3,1)^2+endpt(3,2)^2);
%     controlAngle1 = atand(endpt(3,3)/lengthCarm1);
% 
%     lengthCarm2 = sqrt(endpt(5,1)^2+endpt(5,2)^2);
%     controlAngle2 = atand(endpt(5,3)/lengthCarm2);
% 
%     
%     outputAngles = [controlAngle1, controlAngle2, controlAngle3];
%     
%     GcodeSpitter(outputAngles,0); 

% finally, add in one more line to rArmSimulator.m at the very end: 

%     GcodeSpitter([0 0 0],1);

% this will tell GcodeSpitter to stop looking for incoming lines of data and
% to print out the matrix its been generating in Gcode format. the heading
% can be edited down below.


% What Is Flag variable?
% What is the if statement?
% 

function GcodeSpitter(outputAngles,flag)

persistent finalOutput 


    %initialization, there's gotta be something there to increment 
    if nargin < 1 
        finalOutput = [0 0 0];    
    else
        % concatenates new line to the end of the old array, updates array
        finalOutput = [finalOutput; outputAngles]; 
    
        %this bit is the flag that is called for at the end of the
        %rArmSimulator, it triggers GcodeSpitter to spit out the Gcode! 
        if flag == 1
            
            %open the file for writing, change it from .txt to .Gcode before use 
            %you can change the file name here, eventually this will probably
            %be made into a call to the user to enter a name 
            fid = fopen('mygcode.txt','w');
            
            %add in the header cuz you gotta give credit where credit is due ;)
            fprintf(fid,'; this Gcode was produced by rArmSimulator\n');
            fprintf(fid,'; written by: Michael Rosplock on february 18, 2017\n');
            fprintf(fid,'; X is actually motor angle 1, Y is motor angle 2, and\n');
            fprintf(fid,'; Z is motor angle 3 on a 3 axis parallelogram robotic arm\n'); 
            fprintf(fid,'; designed by Nathan Aswege and Michael Rosplock\n');
          
            %this is the line that actually writes the Gcode 
            fprintf(fid,'G1 X%f  Y%f Z%f \n',finalOutput);
            
            %close the file so nothing else can access it, 
            fclose(fid);
        end
  
    end
  
end 

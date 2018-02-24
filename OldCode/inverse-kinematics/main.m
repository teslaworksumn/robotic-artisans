%rArmSimulator 
% this is the where we're going to start simulating and calculating things
%so now we can pass individual points (plural is the important par%inverseRobotic, which will solve for the control angles, and then passt) to
%them to roboticArmSim to draw the arm in the new position 

%so now we need to carry variables into each program -__-
groundLink = 114.3;
L1=261.5;
L5= 285.75; 
L6 = 50.8; % this is the start of the 3rd box, 114.3
angle6 =45; %need to set its angle too 
L8 = 25; % this is the length of the bottom part of the end effector 
b = L5-groundLink; 

%start working from here, just include all the parameters after x and y in
%the call to inverseRobotics, modify x and y accordingly. 

% draw a lower resolution box resolution is 10mm
% for i=1:100
%     x = 100+i; 
%     y = 100;
%     z = 0;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:100
%     x = 200; 
%     y = 100-i; 
%    z = 0;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:100
%     x = 200-i; 
%     y = 0; 
%     z = 0;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:100
%     x = 100; 
%     y = 0+i; 
%     z = 0;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% 
% %draw a circle? oh ya!! XD
% 
% for i=1:360
%     x = 75+25*cosd(i);
%     y =  100+25*sind(i);
%     z = 0;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% 
% end 

%draw a cube in 3d bitches 

%draw a lower resolution box resolution is 10mm



% @TODO: change these calls to drawLine function.
y = 50;
for i=1:50
    x = 100+i; 
    z = 100;
    InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
end
% One function call.

for i=1:50
    x = 150; 
    z = 100-i; 
  
    InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
end
% for i=1:50
%     x = 150-i; 
%     z = 50; 
%    
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 100; 
%     z = 50+i; 
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 100; 
%     z=100; 
%     y = 50-i;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 100+i; 
%     z = 100;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 150; 
%     z = 100-i; 
%   
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 150-i; 
%     z = 50; 
%    
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 100; 
%     z = 50+i; 
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end
% for i=1:50
%     x = 100; 
%     z=100; 
%     y = 0+i;
%     InverseKinematicSolver(x,y,L1,b,groundLink,L5,L6,angle6,L8,z);
% end

% Reading in from a file
% file_name = 'xyz.txt';
% file_in = fopen(file_name);
% tline = fgetl(file_in);
% while ischar(tline)
%     disp(line);
%     line = strsplit(tline);
%     InverseKinematicSolver(str2double(line{3})*25.4, str2double(line{7})*25.4, L1, b, ...
%                           groundLink, L5, L6, ...
%                           angle6, L8, str2double(line{5})*25.4);
%     tline = fgetl(file_in);
% end
% fclose(file_in);

% finally, add in one more line to rArmSimulator.m at the very end: 
GcodeSpitter([0 0 0],1);


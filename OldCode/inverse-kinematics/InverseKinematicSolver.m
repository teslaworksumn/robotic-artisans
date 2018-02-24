% This program will solve the inverse kinematics on the parallelagram
% robot. It then passes values to roboticArmSim which
% actually calculates stuff and draws the picture. 

% Basically, all we do is:
% 1. Pick a point in space with respect to the zero
%    point, which is defined through the z axis of the motor shafts for angle1
%    and angle3. 
% 2. Draw a vector between ground and that point. I then know that
%    length and angle with respect to the horizontal plane. Then I have link1
%    and part of the control link that is the same angle as link3, this forms a
%    triangle, and I can 
% 3. use law of consines and sines to find the required
%    angles to hit that point. 
%
% I think each point in cartesian space should have a single set of angles to achieve that location. 
%

function InverseKinematicSolver(x,y,a,b,Gset1,thatOneLink,L6,angle6,L8,z)

vLength = sqrt(x^2+y^2+z^2); 

vAngle = atand(y/x);
vAngle2 = atand(z/x);

% We dont know any angles inside the triangle so law of consines.

c = vLength ;

angleCc = acosd((c^2-a^2-b^2)/(-2*a*b));

% Now we can do law of sines to find the control angles 1 and 3. 

angleAa=asind(a*sind(angleCc)/c);

angleBb=180-angleAa-angleCc; 

% The control angles are: 
controlAngle1 = vAngle+angleBb; 
controlAngle2 = 180-angleAa+vAngle;
ArmGraphics(controlAngle1,controlAngle2,a,Gset1,thatOneLink,L6,angle6,L8,vAngle2);

% I might try to add file output for the motor control angles from this
% function, otherwise i could just make a copy of this function that handles that.

end 




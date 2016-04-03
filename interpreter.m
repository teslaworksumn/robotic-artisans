%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Gcode Interpreter
% C3-P0 and R2-D2
% Developed by Sam Finnegan
% March 2016
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function interpreter
    xyzId = fopen('xyz.gcode');
    xyz = textscan(xyzId, '%*s %*s %f %*s %f %*s %f');
    angleID = fopen('angle.gcode','w');
    formatSpec = 'G1 T1 %3.3f T2 %3.3f T3 %3.3f\r\n';
    for n=1:length(xyz{1})
        [t1,t2,t3]=interpreter_123(xyz{1}(n),xyz{2}(n),xyz{3}(n),0);
        fprintf(angleID,formatSpec,t1,t2,t3);
    end
    fclose(xyzId);
    fclose(angleID);
end

function [T1,T2,T3] = interpreter_123(x,y,z,Theta)
    xmax=8; ymax=10;
    A0x=-5; A0y=ymax/2; A0z=3;
    x0=x-A0x; y0=y-A0y; z0=z-A0z;
    R=sqrt((x0)^2+(y0)^2);
    [T1,T2]=interpreter_12(R+z0*1i,Theta);
    T3=atan2(x0,y0)*180/pi;
end

function [Theta1,Theta2]= interpreter_12(P,Theta)
%Parameter Constants
A0=0+0i; B0=-2+1i;
a1=2.1; b1=2.3; c1=1.9; %ternary 1
a2=3.2; b2=6.1; c2=3.2; %ternary 2
a3=2.2; b3=2.1; c3=1.9; %ternary 3
r1=4.2; r2=4.4; r3=3.1; r4=3.3; r5=2.6;
Theta1_max = 90*pi/180; Theta1_min = 45*pi/180;
Theta2_max = 135*pi/180; Theta2_min = 100*pi/180;
Theta = Theta*pi/180;

p3=P+b3*exp(1i*(Theta+pi));
tp4 = acos((c3^2-a3^2-b3^2)/(-2*a3*b3));
p4=P+a3*exp(1i*(Theta+pi-tp4));

[p1(1),p1(2)] = isect(A0,r1,p3,a2);
Theta1 = angle(p1(2),A0)*180/pi;
[p2(1),p2(2)] = isect(p1(1),a1,p4,r3);
[p2(3),p2(4)] = isect(p1(2),a1,p4,r3);

[q1(1),q1(2)]= isect(p1(1),c1,B0,r2);
[q1(3),q1(4)]= isect(p1(2),c1,B0,r2);

[q3(1),q3(2)] = isect(p3,b2,p1(2),c2);

[q2(1),q2(2)] = isect(q3(1),r5,A0,r4);
[q2(3),q2(4)] = isect(q3(2),r5,A0,r4);
Theta2 = angle(q2(1),A0)*180/pi;

hold off;
iplot(A0,p1(2));
axis([-3 10 0 7]);
hold on;
itriangle(p1(2),p3,q3(1),'b');
itriangle(p2(4),q1(3),p1(2),'r');
iplot(p2(4),p4);
iplot(q1(3),B0);
iplot(q3(1),q2(1));
iplot(q2(1),A0);
itriangle(P,p3,p4,'g');
end

function [ans1,ans2] = isect(comp1,r1,comp2,r2)
x1=real(comp1); y1=imag(comp1);
x2=real(comp2); y2=imag(comp2);

d=sqrt((x1-x2)^2+(y1-y2)^2);
l=(r1^2-r2^2+d^2)/(2*d);
h=sqrt(r1^2-l^2);

ans1=l/d*(x2-x1)+h/d*(y2-y1)+x1 +(l/d*(y2-y1)-h/d*(x2-x1)+y1)*1i;
ans2=l/d*(x2-x1)-h/d*(y2-y1)+x1 +(l/d*(y2-y1)+h/d*(x2-x1)+y1)*1i;
end

function d = dist(comp1,comp2)
d = sqrt((real(comp1)-real(comp2))^2+(imag(comp1)-imag(comp2))^2);
end

function a = angle(comp1,comp2)
a=atan2((imag(comp1)-imag(comp2)),(real(comp1)-real(comp2)));
end

function iplot(comp1,comp2)
plot([real(comp1),real(comp2)],[imag(comp1),imag(comp2)]);
end

function itriangle(comp1,comp2,comp3,color)
fill([real(comp1),real(comp2),real(comp3)],[imag(comp1),imag(comp2),imag(comp3)],color);
end
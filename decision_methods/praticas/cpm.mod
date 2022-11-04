var x1 >=0;
var x2 >=0;
var x3 >=0;
var x4 >=0;
var x5 >=0;
var x6 >=0;

minimize z: x6 - x1;

A: x3 >= x1 + 6;
B: x2 >= x1 + 9;
fict1: x3 >= x2;
C: x5 >= x3 + 8;
D: x4 >= x3 + 7;
E: x5 >= x4 + 10;
F: x6 >= x5 + 12;

solve;
display x1,x2,x3,x4,x5,x6,z;
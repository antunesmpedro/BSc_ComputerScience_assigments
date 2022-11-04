var y1 >=0;
var y2 >=0;
var y3 >=0;
var y4 >=0;
var y5 >=0;
var y6 >=0;
var y7 >=0;
var y8 >=0;

maximize z: 6*y6 + 9*y2 + 8*y4 + 7*y5 + 10*y6 + 12*y8;

no1: -1*y1 -1*y2 <= -1;
no2: y1 -1*y3 <= 0;
no3: y2 + y3 -1*y4 -1*y5 <= 0;
no4: y4 -1*y7 <= 0;
no5: y5 -1*y6 <= 0;
no6: y6 + y7 -1*y8 <= 0;
no7: y8 <= 1;

solve;
display y1,y2,y3,y4,y5,y6,y7,y8,z;
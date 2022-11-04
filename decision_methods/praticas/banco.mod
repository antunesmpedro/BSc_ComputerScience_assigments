set N:= {1..5};

var x{i in N} >= 0;

maximize z: 13*x[1] + 16*x[2] + 16*x[3] + 14*x[4] + 39*x[5];

subject to
	rest1 : 11*x[1] + 53*x[2] + 5*x[3] + 5*x[4] + 29*x[5] <= 40;
	rest2 : 3*x[1] + 6*x[2] + 5*x[3] + x[4] + 34*x[5] <= 20;
	rest3 : x[1] <= 1;
	rest4 : x[2] <= 1;
	rest5 : x[3] <= 1;
	rest61 :x[4] <= 1;
	rest62 :x[5] <= 1;

solve;

display z, x;
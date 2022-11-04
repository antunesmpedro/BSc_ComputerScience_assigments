var x1 >= 0 <= 1;
var x2 >= 0 <= 1;
var x3 >= 0 <= 1;
var x4 >= 0 <= 1;
var x5 >= 0 <= 1;

maximize z: 5*x1 + 3*x2 + 6*x3 + 6*x4 + 2*x5;
subject to
	r1: 5*x1 + 4*x2 + 7*x3 + 6*x4 + 2*x5 <= 15;

solve; 

display z, x1, x2, x3, x4, x5;
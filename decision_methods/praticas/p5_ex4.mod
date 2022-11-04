var x1 >=0;
var x2 >=0;
var x3 >=0;

subject to rest1: 3*x1 + 2*x2+ x3 <= 7;
	       rest2:2*x1 + x2 + 2*x3 <= 11;
	       rest_int1: x2 <=3;
	       rest_int2: x1 <= 0;
maximize z: 4*x1 + 3*x2 + x3;

solve;

display x1,x2,x3,z;

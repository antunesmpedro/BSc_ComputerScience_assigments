set V;
set E within {V,V};

param n := card(V);

var x{V} binary;
var y{E} binary;

minimize z: sum{(i,j) in E} y[i,j];

subject to cardinL: sum{i in V} x[i] = n/2;
		   rest1{(i,j) in E}: x[i] - x[j] <= y[i,j];
		   rest2{(i,j) in E}: x[j] - x[i] <= y[i,j];

solve;

display z,x,y;
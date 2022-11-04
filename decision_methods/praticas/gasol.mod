set N;

param venda{i in N};
param compra{i in N};
param min_octanas{i in N};
param max_enxofre{i in N};
param octanas{i in N};
param enxofre{i in N};


var x{i in N} >= 0;
var y{i in N, j in N} >= 0;

var p{i in N} >=0;

maximize z: (sum{i in N} x[i]*venda[i]) - (sum{i in N, j in N} y[i,j]*compra[j]) - (sum{i in N} x[i]*4) - (sum{i in N} p[i]);

subject to
	rest1 : sum {i in N} x[i] <= 14000;
	rest2 : x[1] + 10*p[1] >= 3000;
	rest3 : x[2] + 10*p[2] >= 2000;
	rest4 : x[3] + 10*p[3] >= 1000;
	rest5 {j in N}: sum {i in N} y[i,j] <= 5000;
	rest61 :y[1,1] * 0.005 + y[1,2] * 0.02 + y[1,3] * 0.03 <= x[1] * 0.01;
	rest62 :y[1,1] * 0.005 + y[1,2] * 0.02 + y[1,3] * 0.03 <= 10 * x[1];
	rest71 :y[2,1] * 0.005 + y[2,2] * 0.02 + y[2,3] * 0.03 <= 0.02 * x[2];
	rest72 :y[2,1] * 0.005 + y[2,2] * 0.02 + y[2,3] * 0.03 <= 8 * x[2];
	rest81 :y[3,1] * 0.005 + y[3,2] * 0.02 + y[3,3] * 0.03 <= x[3] * 0.01;
	rest82 :y[3,1] * 0.005 + y[3,2] * 0.02 + y[3,3] * 0.03 <= 6 * x[3];

solve;

display z, x, y, p;
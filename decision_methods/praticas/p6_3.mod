set N;
param custo_const{i in N};
param custo_ton{i in N};
param tone_remov_1{i in N};
param tone_remov_2{i in N};
param k1 := 80000; 
param k2 := 50000;

var dc{i in N} binary;
var c{i in N} >= 0;

minimize z: sum{i in N} dc[i]*custo_const[i] + sum{i in N} custo_ton[i]*c[i];

subject to
	r2{i in N}: c[i] <= 99999999*dc[i];
	r4: sum{i in N} tone_remov_1[i] *c[i] >= k1;
	r5: sum{i in N} tone_remov_2[i] *c[i] >= k2;

solve;

display z, dc, c;
set N;

param cc{N};
param ca{N};
param pr1{N};
param pr2{N};
param limite1 := 80000;
param limite2 := 50000;

var centro{i in N} binary;
var toneladas{i in N};
var y1 binary;

minimize z: sum{i in N} centro[i]*cc[i] + sum{j in N} centro[j]*ca[j]*toneladas[j];

subject to maxcentro: sum{i in N} centro[i] <= 3;
		   remocao1: sum{i in N} centro[i] * pr1[i] * toneladas[i] <= limite1;
		   remocao2: sum{i in N} centro[i] * pr2[i] * toneladas[i] <= limite2;
		   tratamento1{i in N}: -centro[i] <= y1;
		   tratamento2{i in N}: toneladas[i] >= 1-y1;
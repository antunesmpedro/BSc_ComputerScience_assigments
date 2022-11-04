set Trabalhos;

param duracao{Trabalhos};
param data_entrega{Trabalhos};
param penalizacao{Trabalhos};

#############################################

var y{i in Trabalhos,j in Trabalhos: i!=j} binary;
var l{Trabalhos}>=0;
var c{Trabalhos};

#############################################

minimize z: sum{i in Trabalhos} l[i] * penalizacao[i];

subject to atrasos1{i in Trabalhos}: l[i] >= c[i] - data_entrega[i];
		   atrasos2{i in Trabalhos}: l[i] >= 0;
		   tempos{i in Trabalhos}: c[i] = duracao[i] + sum{j in Trabalhos: j != i} y[j,i] * duracao[j];
		   ordena1{i in Trabalhos, j in Trabalhos: i != j}: y[i,j] + y[j,i] = 1;
		   ordena2{i in Trabalhos, j in Trabalhos, k in Trabalhos: i != j && j != k && k != i}: y[i,j] + y[j,k] + y[k,i] <= 2; 

solve;

display z, y, l;
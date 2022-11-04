set input dimen 2; #input tem 2 valores para distinguir locais com o mesmo nome

param lat{(a,b) in input}; #latitude para cada cidade
param long{(a,b) in input}; #longitude para cada cidade

var x; #latitude do local ideal
var y; #longitude do local ideal
var difflat{(a,b) in input}; #diferenca de latitude entre local ideal e uma dada cidade;
var difflong{(a,b) in input};#diferenca de longitude entre local ideal e uma dada cidade;

table data IN "CSV" "PopulationContPT-2020.csv": input <- [asciiname,population], lat ~ latitude, long ~ longitude; #ler ficheiro e guardar valores em lat e long

#restricoes: a diferenca ser maior do que zero
subject to 	r1 {(a,b) in  input}: difflat[a,b]-lat[a,b]+x >= 0;
			r2 {(a,b) in  input}: difflat[a,b]+lat[a,b]-x >= 0;
			r3 {(a,b) in  input}: difflong[a,b]-long[a,b]+y >= 0;
			r4 {(a,b) in  input}: difflong[a,b]+long[a,b]-y >= 0;

minimize cost: sum{(a,b) in input} ((2*3.14*6371.009))* (3*b/1000) * (difflat[a,b]/360+difflong[a,b]/360);


solve;

display x,y, cost;

param minDistance := min{(a,b) in input} (difflat[a,b]+difflong[a,b]);#guardar em minDistance o menor valor
for{ (i,j) in input } {
   for {{0}: (difflat[i,j]+difflong[i,j]) == minDistance}{
      printf "A cidade mais perto do DC é : %s.\n", i;
   }
}

param maxLargestCost := max{(a,b) in input} (((2*3.14*6371.009))* (3*b/1000) * (difflat[a,b]/360+difflong[a,b]/360)); #guardar em maxLargestCost o valor de custo máximo


for{ (i,j) in input} {
	for {{0}: ((2*3.14*6371.009)* ceil (3*j/1000) * (difflat[i,j]/360+difflong[i,j]/360)) == maxLargestCost}{
		printf "A cidade mais dispendiosa do DC é : %s.\n", i;
	}
}

end;

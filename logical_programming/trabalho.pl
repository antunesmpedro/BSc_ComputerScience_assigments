text2poly(X,P):-
	atom_string(X,S),
	atomic_list_concat(L," ",S),
	command(P,L,[]), !.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% entry point !

% simple command
command([B]) --> bye(B).
command([S,M])--> show(S), memory(M).
command([F,M]) --> forget(F), memory(M).

command([S,P]) --> show(S), poly(P).
command([C,P]) --> simplify(C), poly(P).
command([C,P,P2]) --> multiply(C), poly(P), by(_), poly(P2).
command([C,P,P2]) --> add(C), poly(P), with(_), poly(P2).

command([S,P,A]) --> show(S), poly(P), atrib(A).
command([C,P,A]) --> simplify(C), poly(P), atrib(A).
command([C,P,P2,A]) --> multiply(C), poly(P), by(_), poly(P2), atrib(A).
command([C,P,P2,A]) --> add(C), poly(P), with(_), poly(P2), atrib(A).

% storage
memory([S,P]) --> stored(S), polynominals(P).
memory([L,A]) --> local(L), address(A).

atrib([A,V]) --> as(A),address(V).

% tokens 
bye(bye) --> [bye].
forget(forget) --> [forget].
show(show) --> [show].
local(local) --> [local].
simplify(simplify) --> [simplify].
multiply(multiply) --> [multiply].
add(add) --> [add].
by(by) --> [by].
and(and) --> [and].
with(with) --> [with].
stored(stored) --> [stored].
polynominals(polynominals) --> [polynominals].
as(as) --> [as].
% storage vars.
address("P1") --> ["P1"].
address("P2") --> ["P2"].
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  poly 

poly(M) --> mony(M).
poly(M+P) --> mony(M), signal(+), poly(P).
poly(M-P) --> mony(M), signal(-), poly(P).

mony(N) --> number(N).
mony(N^P) --> number(N), exponent(P).
mony(P) --> power(P).
mony(N*P) --> number(N), power(P).

power(X) --> pvar(X).
power(X^P) --> pvar(X), exponent(P).
power(X^Y) --> pvar(X), signal(^), number(Y).

number(N) --> digit(N).
number(N,D,F) --> digit(N),dot(D),digit(F).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  tokens para polinomio converter
%%  dot
dot(.) --> [dot].

%%vars
pvar(x) --> [x].
pvar(y) --> [y].
pvar(z) --> [z].

%%  expoents 
exponent(2) --> [squared].
exponent(3) --> [cubed].
exponent(4) --> [quartic].
exponent(5) --> [quintic].
exponent(6) --> [sextic].
exponent(7) --> [heptic].
exponent(8) --> [octic].

%%  digits
digit(0) --> [zero].
digit(1) --> [one].
digit(2) --> [two].
digit(3) --> [three].
digit(4) --> [four].
digit(5) --> [five].
digit(6) --> [six].
digit(7) --> [seven].
digit(8) --> [eight].
digit(9) --> [nine].

%%  signals
signal(+) --> [plus].
signal(-) --> [minus].
signal(^) --> [raise].
signal(*) --> [times].


%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%    POLYPLAY       %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%

read_string(String) :-
    current_input(Input),
    read_line_to_codes(Input, Codes),
    string_codes(String, Codes).

polyplay :- 
	input(I),
	aux_play(I).

input(I) :- 
	writeln('Input command:'), nl,
 	read_string(S),
	text2poly(S,I).

aux_play([bye]) :- writeln("See ya").
aux_play([show,local,P]) :- data(P,_) ,writeln(P), input(I), aux_play(I).	
aux_play([show,stored,polynominals]) :- data(X,Y), write(X) , write(Y) , input(I), aux_play(I).
aux_play([show,P]) :- writeln(P), input(I), aux_play(I).
aux_play([simplify,P1]) :- closesimpoly(P1,P2), writeln(P2), input(P), aux_play(P).
aux_play([multiply,P1,P2]) :- scalepoly(P1,P2,P3), writeln(P3), input(P), aux_play(P).
aux_play([add,P1,P2]) :- addpoly(P1,P2,P3), writeln(P3), input(P), aux_play(P).


%% com memory use
aux_play([show,P,as,V]) :- writeln(P), assertz(data(V,P)), input(I), aux_play(I,_).
aux_play([simplify,P1,as,V]) :- closesimpoly(P1,P2),assertz(data(V,P2)), writeln(P2), input(P), aux_play(P).
aux_play([multiply,P1,P2,as,V]) :- scalepoly(P1,P2,P3),!, writeln(P3), assertz(data(V,P3)), input(P), aux_play(P).
aux_play([add,P1,P2,as,V]) :- addpoly(P1,P2,P3),assertz(data(V,P3)), writeln(P3), input(P), aux_play(P).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%% TRABALHO 1   %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% DATA STRUCTURE 
%%  ppt 1

pvars([x,y,z]).
pvar(X):-pvars(V),member(X,V).

power(X):-pvar(X),!.
power(X^Y):-pvar(X),integer(Y),Y>1,!.

coefficient(K):-number(K).

monomial(X):-pvar(X),!.
monomial(N):-number(N),!.
monomial(X):-power(X),!.
monomial(K*X):-coefficient(K),power(X),!.

polynomial(M):-monomial(M),!.
polynomial(P+M):-monomial(M),polynomial(P),!.
polynomial(P-M):-monomial(M),polynomial(P),!.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  poly2list 2

poly2list(P, L):- reverse(L, L2), poly2list2(P, L2),!.
poly2list2(M, [M]):- monomial(M),!.
poly2list2(P+M,[M|L]):- monomial(M) , poly2list2(P,L), !. 
poly2list2(P-M,[-M|L]):- monomial(M) , poly2list2(P,L), !.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% simpoly/2
closesimpoly(P,P):- simpoly(P,P2), P==P2,!.
closesimpoly(P,P3):- simpoly(P,P2), closesimpoly(P2,P3),!.

simpoly(M,M2):-monomial(M),simmon(M,M2),!.
simpoly(P+0,P):-!.
simpoly(0+P,P):-monomial(P),!.
simpoly(P+M,P2+M3):- monparts(M,_,XExp), delmonomial(P,XExp,M2,P2),!, addmonomial(M,M2,M3).
simpoly(P+M,P2+M2):-simpoly(P,P2),simmon(M,M2).
simpoly(P,P2):-polynomial(P), simpoly(P,P2),!.

% Simplify monomials
simmon(1*P,P):-power(P),!.
simmon(-1*P, -P):-power(P),!.
simmon(0*_,0):-!.
simmon(M,M).

% monoparts to decompose a monomial in coefficient and variable-exponent
monparts(X^N,1,X^N):-power(X^N),!.
monparts(-X^N,-1,X^N):-power(X^N),!.
monparts(K*P,K,P):-number(K),!.
monparts(K,K,indep):-number(K),!.
monparts(X,1,X):-pvar(X),!.

% deletes the monomial M with variable-exponent XExp yielding polynomial P2.
delmonomial(M,X,M,0):- monomial(M),monparts(M,_,X),!.
delmonomial(M+M2,X,M,M2):- monomial(M2),monomial(M),monparts(M,_,X),!.
delmonomial(P+M,X,M,P):- monomial(M),monparts(M,_,X),!.
delmonomial(P+M2,X,M,P2+M2):- delmonomial(P,X,M,P2).

% addmonomial(M1,M2,M3) adds two monomials. If thery are not summable it fails.
addmonomial(K1,K2,K3):- number(K1),number(K2),!, K3 is K1+K2.
addmonomial(M1,M2,M3):- monparts(M1,K1,XExp), monparts(M2,K2,XExp), K3 is K1+K2, aux_addmonomial(K3,XExp,M3).

% aux addmonomial(M1,M2,M3) builds the result in a simplified form.
aux_addmonomial(K,indep,K):-!.
aux_addmonomial(0,_,0):-!.
aux_addmonomial(1,XExp,XExp):-!.
aux_addmonomial(K,XExp,K*XExp).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% simpoly list/2
simpoly_list([],[]):-!.
simpoly_list(L1,L2):- poly2list(P1,L1), closesimpoly(P1,P2), poly2list(P2,L2),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (ALMOST DONE)
%% scalepoly/3
scalepoly(0,_,0):-!.
scalepoly(N,P1,P2):- number(N), mult(N,P1,P), closesimpoly(P,P2),!.

mult(N,X,P2):- number(X), P2 is N*X, !.
mult(-N,X,P2):- number(X), P2 is -N*X, !.
mult(1,P,P2) :- polynomial(P), simpoly(P, P2),!.
mult(-1,P,P2) :- polynomial(P), simpoly(P, P2),!.
mult(N,M,P2) :- monomial(M), monparts(M,K,XExp), K2 is K*N, monparts(AUX, K2, XExp), simpoly(AUX, P2),!.
mult(N,P+M,P2) :- monomial(M), simpoly(P, P1),mult(N,P1,L1),mult(N,M,L2),!,simpoly(L1+L2,P2).
mult(N,P-M,P2) :- monomial(M), simpoly(P, P1),mult(N,P1,L1),mult(N,-M,L2),!,simpoly(L1+L2,P2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% (NOT WORKING)
%% addpoly/3
addpoly([],P2,P2):-!.
addpoly(P2,[],P2):-!.
addpoly(P1,P2,P3):- poly2list(P1,L1), poly2list(P2,L2), append(L1,L2,L3), poly2list(P4,L3), closesimpoly(P4,P3),!.






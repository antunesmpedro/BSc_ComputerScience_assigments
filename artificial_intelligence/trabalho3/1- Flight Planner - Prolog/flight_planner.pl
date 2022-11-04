
% FLIGHT DATABASE

timetable( edinburgh, london,
 [ 9:40 / 10:50 / ba4733 / alldays,
 13:40 / 14:50 / ba4773 / alldays,
 19:40 / 20:50 / ba4833 / [mo,tu,we,th,fr,su] ] ). 

timetable( london, edinburgh,
 [ 9:40 / 10:50 / ba4732 / alldays,
 11:40 / 12:50 / ba4752 / alldays,
 18:40 / 19:50 / ba4822 / [mo,tu,we,th,fr] ] ). 

timetable( london, ljubljana,
 [ 13:20 / 16:20 / jp212 / [mo,tu,we,fr,su],
 16:30 / 19:30 / ba473 / [mo,we,th,sa] ] ). 

timetable( london, zurich,
 [ 9:10 / 11:45 / ba614 / alldays,
 14:45 / 17:20 / sr805 / alldays ] ). 

timetable( london, milan,
 [ 8:30 / 11:20 / ba510 / alldays,
 11:00 / 13:50 / az459 / alldays ] ). 

timetable( ljubljana, zurich,
 [ 11:30 / 12:40 / jp322 / [tu,th] ] ). 

timetable( ljubljana, london,
 [ 11:10 / 12:20 / jp211 / [mo,tu,we,fr,su],
 20:30 / 21:30 / ba472 / [mo,we,th,sa] ] ). 

timetable( milan, london,
 [ 9:10 / 10:00 / az458 / alldays,
 12:20 / 13:10 / ba511 / alldays ] ). 

timetable( milan, zurich,
 [ 9:25 / 10:15 / sr621 / alldays,
 12:45 / 13:35 / sr623 / alldays ] ). 

timetable( zurich, ljubljana,
 [ 13:30 / 14:40 / jp323 / [tu,th] ] ). 

timetable( zurich, london,
 [ 9:00 / 9:40 / ba613 / [mo,tu,we,th,fr,sa],
 16:10 / 16:55 / sr806 / [mo,tu,we,th,fr,su] ] ). 

timetable( zurich, milan,
 [ 7:55 / 8:45 / sr620 / alldays ] ).


% Operator ':' has lower precedence
:- op( 50, xfy, :).

% HELPER FUNCTIONS

% Recursive member function 
% Checks if item belongs on List
member(X, [X|L]).
member(X, [Y|L]) :- 
	member(X, L).

% MAIN FUNCTIONS 
% Flight Checker
flight( Start, End, Day, FNumber, DepTime, ArrTime) :-
	timetable(Start, End, FlighList),
	member( DepTime / ArrTime / FNumber/ DayList, FlighList),
	flyday( Day , DayList).


%Direct Routes 
route( Start, End, Day, [ Start / End / Fnumber / Deptime]) :- 
	flight( Start, End, Day, Fnumber, Deptime, _).

%Indirect Routes
route( Start, End, Day,[(Start / Mid / FNumber1 / Departure1)| RestRoute] ) :-
	route( Mid, End, Day, RestRoute),
	flight(Start, Mid, Day, FNumber1, Departure1, Arrival1),
	deptime( RestRoute, Departure2),
	transfer( Arrival1 , Departure2).


% Flyday Checker
flyday(Day, DayList)  :-
	member(Day, DayList).

flyday(Day, alldays)  :-
	member(Day, [mo,tu,we,th,fr,sa,su]).

% Departure time
deptime( [ Start/ End / FNumber / Dep | _], Dep).

% Checker if diference between flights is higher than 40
transfer( Hours1:Mins1, Hours2:Mins2)  :-
	60 * (Hours2 - Hours1) + Mins2 - Mins1 >= 40.

% Permutation function 
% Does the permutations of cities
% Only used in last question, 
query3(S,X1,X2,X3,City1,City2,City3,FN1,FN2,FN3,FN4)  :-
  permutation([X1,X2,X3],[City1,City2,City3]),
  flight( S, City1, tu, FN1,_,_),
  flight( City1, City2, we, FN2, _, _),
  flight( City2, City3, th, FN3, _, _),
  flight( City3, S, fr, FN4, _,_).
 
permutation([], []).
 
permutation( L, [X | P])  :-
  del( X, L, L1),
  permutation( L1, P).
  
del( X, [X|L], L).
del( X, [Y|L], [Y|L1])  :-
  del( X, L, L1).
Tested on:
linux ubuntu 16.04 lts
yap-6.2.2

Questions:
--> In which days of the week there is a direct flight from Place1 to Place2?

Answer: flight(place1, place2, Days,_,_,_).

Note that place1 & place2 are inputs and days are returned in 'Days'. 
; for more solutions

Example: flight(london, milan, Days,_,_,_).
  


--> What are the available flights from Place1 to Place2 on Thursday?

Answer: route(place1,place2, th, R).

Note that place1 & place2 are inputs, th is Thursday, R returns routes.

Example: route(london,milan, th, R).

- I need to visit cities C1, C2 and C3, starting my flight in city S on Tuesday and
returning to S on Friday. In which sequence I should visit cities C1, C2 and C3 so
that I don’t need to have more than one flight a day?

Answer: query3(s, c1, c2, c3, CityOrder1, CityOrder2, CityOrder3, Fnumber1, Fnumber2, Fnumber3, Fnumber4).

Example: query3( london, milan, ljubljana, zurich, C1,C2,C3,FN1,FN2,FN3,FN4).

BUGS:
route não está a retornar as próximas opções.
query3 está em loop. 


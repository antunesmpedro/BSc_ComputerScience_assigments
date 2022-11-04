select film.title from film where film_id in (select film_actor.film_id from actor natural join film_actor where actor.first_name ="HARRISON" and actor.last_name ="BALE") and film_id in(select inventory.film_id from inventory natural join rental group by inventory.film_id having count(*) >20) order by 1;  


/*OU                  */

select title from 
       	     film NATURAL JOIN film_actor 
	     	  NATURAL JOIN actor 
		  
		  where first_name='HARRISON' 
		  and last_name='BALE' 
		  and film_id 
		  in(select film_id from inventory NATURAL JOIN rental group by film_id  having count(*)>20);
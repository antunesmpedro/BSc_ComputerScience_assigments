	select distinct title from film, film_actor, actor where
	       film_actor.film_id=film.film_id and 
	       actor.actor_id=film_actor.actor_id and 
	       actor.first_name='Harrison' and actor.last_name='Bale'
	       order by title;


E)

	select distinct first_name, last_name from customer, rental where
	       customer.customer_id=rental.customer_id and
	       rental.return_date=NUll
	       order by 1,2;


F)

	select distinct 
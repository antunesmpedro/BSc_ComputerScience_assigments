select distinct first_name, last_name from actor, film_actor, film 
       where actor.actor_id=film_actor.actor_id and
       	     film_actor.film_id=film.film_id and
	     film.title="WYOMING STORM"
	     order by 1,2;
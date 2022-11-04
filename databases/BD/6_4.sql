select title from 
	film, film_actor, actor where  
		film.film_id=film_actor.film_id and 			film_actor.actor_id=actor.actor_id and 			actor.first_name='HARRISON' and 
		actor.last_name='BALE' 
			order by title;

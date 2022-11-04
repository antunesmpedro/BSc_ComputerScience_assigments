select count(distinct film_actor.actor_id) from film_actor, film, category where 
       film_actor.film_id=film.film_id and 
       film.category_id=category.category_id and
       category.name ="Action";
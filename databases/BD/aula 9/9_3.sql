select first_name, last_name from actor where actor.actor_id in
       (select distinct actor.actor_id from film_actor, actor, film, category where 
       actor.actor_id=film_actor.actor_id and	
       film_actor.film_id=film.film_id and
       film.category_id =category.category_id and 
       category.name="Drama")
       order by 1,2; 
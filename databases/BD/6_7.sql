select distinct 
	first_name, last_name 
	from 
		actor, film_actor, film, category where    			actor.actor_id=film_actor.actor_id and 			film_actor.film_id=film.film_id and 
		film.category_id = category.category_id and 
		category.name="Drama" 
	order by 
	first_name, last_name;





/*select first_name, last_name from actor, film_actor, film, category 
       where actor.actor_id=film_actor.actor_id and
       	     film_actor.film_id=film.film_id  and
	     film.category_id=category.category_id and 
	     category.name="Drama"
		order by 1,2; 

*/
/*

select first_name, last_name from actor where actor_id in
       (select actor_id from film_actor where film_id in
       	       (select film_id from film where category_id in
	       	      (select category_id from category where
		      	     name="Drama")))
				order by 1,2;

igual ao de tras mas feito de outra forma
*/

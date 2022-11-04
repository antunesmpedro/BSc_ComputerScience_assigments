A) select name from category where 
       	   name like 'S%' 
	   	order by name;


B)

	select first_name, last_name from actor 
	       order by 1,2;


C)


	select distinct title from film, inventory, rental where
	       rental.inventory_id=inventory.inventory_id and 
	       inventory.film_id=film.film_id and 
	       rental.customer_id='258'
	       order by title;
	       
d)

	select distinct title from film, film_actor, actor where
	       film_actor.film_id=film.film_id and 
	       actor.actor_id=film_actor.actor_id and 
	       actor.first_name='Harrison' and actor.last_name='Bale'
	       order by title;
e)
	select distinct first_name, last_name from customer, rental
	       where customer.customer_id = rental.customer_id
	       and rental.return_date is NULL
	       order by 1,2


f)
	select A.first_name, A.last_name, B.first_name, B.last_name 
	       from staff as A, staff as B, store where
	       	    A.store_id = store.store_id and
	       	    store.manager = B.staff_id
		    order by 1,2;
	

g) 
   select distinct first_name, last_name from actor, film, film_actor, category
   	  where film.category_id=category.category_id and
	  	category.name='DRAMA'and 
		actor.actor_id=film_actor.actor_id and
		film.film_id=film_actor.film_id
		order by 1,2;
	  	

   	  
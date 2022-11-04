select title from film where film_id in
       (select film_id from inventory) and film_id not in
       	       (select film_id from rental natural join inventory)
	       	       order by 1;
select count(distinct actor_id) from film_actor where film_id in
       (select film_id from film where category_id in
       (select category_id from category where category.name="Action"));





select count(distinct actor_id) as Actores_catg_ACTION 
	from film_actor 
		NATURAL JOIN film NATURAL JOIN category 
	where name="Action";

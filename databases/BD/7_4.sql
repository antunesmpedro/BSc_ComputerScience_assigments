select title from film where not exists (select* from film_actor where 
       film_actor.film_id=film.film_id) order by 1;


/*ou*/ 

select title from film where film_id not in
       (select film_id from film_actor)
       	       order by 1;
       

/*ou*/

select title AS TÍTULO from 
(select title, actor_id from film 
	left join film_actor on film.film_id=film_actor.film_id 
		group by title order by 2 ASC LIMIT 3)T;

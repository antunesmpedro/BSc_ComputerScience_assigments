select distinct first_name , last_name from actor where actor_id in
       (select actor_id from film_actor where film_id in
       (select film_id from film_actor natural join actor where
       actor.first_name="JULIA" AND
       actor.last_name="ZELLWEGER")) AND actor_id NOT IN
       (select actor_id from actor where actor.first_name ="JULIA" AND actor.last_name="ZELLWEGER" )
       order by 1,2;  
























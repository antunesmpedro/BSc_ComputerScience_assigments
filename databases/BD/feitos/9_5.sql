select first_name, last_name from actor where actor_id in 
       (select actor_id from film_actor where film_id in
       (select film_id from film_actor natural join actor where 
       first_name ="" and last_name ="")) and actor_id not in
       (select
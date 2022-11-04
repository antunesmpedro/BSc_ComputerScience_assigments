select first_name, last_name from (select distinct first_name, last_name from actor INNER JOIN film_actor on actor.actor_id = film_actor.actor_id where film_actor.film_id in(select distinct film_id from film NATURAL JOIN film_actor NATURAL JOIN actor where actor.first_name="JULIA" and actor.last_name="ZELLWEGER")) as T where first_name <> "JULIA" or last_name <> "ZELLWEGER";








select * from (select distinct first_name, last_name from actor NATURAL JOIN film_actor where film_id in (select film_id from film_actor NATURAL JOIN actor where first_name ='JULIA' and last_name = 'ZELLWEGER') order by 1) as t where first_name<>'JULIA' OR last_name<>'ZELLWEGER';

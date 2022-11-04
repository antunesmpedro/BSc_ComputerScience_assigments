select first_name, last_name, count(film_id) from actor NATURAL JOIN film_actor group by 1,2 having count(film_id)>30 order by 1,2;

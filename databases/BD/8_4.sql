select title from film where film_id in
(select film_id from inventory group by 1 having count(*)=(select count(*) from inventory group by film_id order by count(*) desc limit 1)) order by 1;



/*                                 OU                                                    */




select title from (select title, count(inventory_id) from film LEFT JOIN inventory on film.film_id=inventory.film_id group by film.film_id order by 2 DESC LIMIT 72)T order by 1;

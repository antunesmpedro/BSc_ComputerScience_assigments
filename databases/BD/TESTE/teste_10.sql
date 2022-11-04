select first_name, last_name from(select first_name, last_name, count(rental.inventory_id) from customer INNER JOIN rental on customer.customer_id=rental.customer_id INNER JOIN inventory on rental.inventory_id=inventory.inventory_id INNER JOIN film on inventory.film_id=film.film_id INNER JOIN category on film.category_id=category.category_id where category.name='Drama' group by 1,2 order by 3 DESC LIMIT 30) T;









/*                      OU  2 talvez mais correto                       */



(select film_id, count(inventory_id), rental.customer_id from inventory NATURAL JOIN rental NATURAL JOIN customer NATURAL JOIN film NATURAL JOIN category where name like 'Drama' group by film_id order by 2 DESC LIMIT 2);

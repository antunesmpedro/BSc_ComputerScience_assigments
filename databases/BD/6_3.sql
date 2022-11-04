select title from film, inventory, rental where film.film_id=inventory.film_id and inventory.inventory_id=rental.inventory_id and rental.customer_id=258 order by 1;

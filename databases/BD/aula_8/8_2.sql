select title, count(inventory_id) from film, inventory where film.film_id= inventory.film_id group by title;

select customer.first_name, customer.last_name from customer, rental, film, inventory where 
       film.film_id =inventory.film_id and 
       inventory.inventory_id=rental.inventory_id and
       rental.customer_id =customer.customer_id and
       rental.return_date is not null and
       film.rental_duration <datediff(rental.return_date, rental.rent_date)
        
       order by 1,2;








/*         OU                   */




elect distinct first_name, last_name from customer INNER JOIN rental on customer.customer_id =rental.customer_id INNER JOIN inventory on rental.inventory_id=inventory.inventory_id INNER JOIN film on inventory.film_id=film.film_id where rental.return_date is not NULL and DATEDIFF(return_date,rent_date)>rental_duration;

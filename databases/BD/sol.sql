#Aula 6

#1
SELECT name FROM category WHERE name LIKE 'S%' ORDER BY name ASC; 
#utilizar LIKE para padroes sempre

#2
SELECT first_name, last_name FROM actor ORDER BY first_name, last_name ASC;

#3
SELECT title FROM film WHERE film_id IN 
	(SELECT film_id FROM inventory WHERE inventory_id IN 
		(SELECT inventory_id FROM rental WHERE customer_id = 258))
ORDER BY title ASC;

#ou

SELECT DISTINCT film.title FROM rental NATURAL JOIN inventory NATURAL JOIN film WHERE rental.customer_id=258 ORDER BY film.title ASC;
#natural join junta os campos iguais, por ex rental.inventory_id = inventory.inventory_id

#4
SELECT title FROM film WHERE film_id IN
	(SELECT film_id FROM film_actor WHERE actor_id =
		(SELECT actor_id FROM actor WHERE first_name = 'HARRISON' AND last_name = 'BALE'))
ORDER BY title ASC;

#ou
SELECT film.title FROM actor NATURAL JOIN film_actor NATURAL JOIN film WHERE actor.first_name = 'HARRISON' AND actor.last_name='BALE' ORDER BY film.title ASC;

#5
SELECT first_name, last_name FROM customer WHERE customer_id IN 
	(SELECT customer_id FROM rental WHERE return_date IS NULL)
ORDER BY first_name ASC, last_name ASC;

#ou
SELECT DISTINCT customer.first_name, customer.last_name
FROM rental NATURAL JOIN customer
WHERE rental.return_date IS NULL
ORDER BY customer.first_name ASC, customer.last_name ASC;

#6
SELECT emp.first_name, emp.last_name, ger.first_name, ger.last_name
FROM staff AS emp, store, staff AS ger
WHERE emp.store_id = store.store_id AND store.manager = ger.staff_id
ORDER BY emp.first_name ASC, emp.last_name ASC;

#7
SELECT first_name, last_name FROM actor WHERE actor_id IN
	(SELECT actor_id FROM film_actor WHERE film_id IN 
		(SELECT film_id FROM film WHERE category_id IN
			(SELECT category_id FROM category WHERE name = 'Drama')))
ORDER BY first_name ASC, last_name ASC;

#Aula 7

#1
SELECT * FROM 
	(SELECT first_name, last_name FROM customer UNION ALL SELECT first_name, last_name fROM staff) AS temp 
ORDER BY first_name ASC, last_name ASC;

#2
SELECT title FROM film WHERE length = (SELECT MAX(length) FROM film) ORDER BY title ASC;

#3
SELECT title FROM film WHERE film_id IN (SELECT inventory.film_id FROM inventory NATURAL JOIN rental) AND film_id NOT IN (SELECT inventory.film_id FROM inventory, rental, customer WHERE inventory.inventory_id = rental.inventory_id AND rental.customer_id = customer.customer_id AND customer.first_name = 'LEE' AND customer.last_name = 'DAVIS') ORDER BY title ASC;

#4
SELECT title FROM film WHERE NOT EXISTS (SELECT * FROM film_actor WHERE film_actor.film_id = film.film_id) ORDER BY title ASC;

#ou
SELECT title FROM film WHERE film_id NOT IN (SELECT film_id FROM film_actor) ORDER BY title ASC;

#5
SELECT title FROM film WHERE EXISTS (SELECT * FROM inventory WHERE inventory.film_id = film.film_id) AND NOT EXISTS (SELECT * FROM rental NATURAL JOIN inventory WHERE inventory.film_id = film.film_id) ORDER BY title ASC;

#ou
SELECT title FROM film WHERE film_id IN (SELECT film_id FROM inventory) AND film_id NOT IN (SELECT film_id FROM rental NATURAL JOIN inventory) ORDER BY title ASC;

#6
SELECT first_name, last_name fROM customer WHERE NOT EXISTS (SELECT * FROM category WHERE category_id IN (SELECT category_id FROM film NATURAL JOIN inventory) AND NOT EXISTS (SELECT * FROM rental NATURAL JOIN inventory NATURAL JOIN film WHERE film.category_id = category.category_id AND rental.customer_id = customer.customer_id)) ORDER BY first_name ASC, last_name ASC;

#ou
SELECT first_name, last_name fROM customer WHERE NOT EXISTS (SELECT * FROM category WHERE category_id IN (SELECT category_id FROM film NATURAL JOIN inventory) AND category_id NOT IN (SELECT category_id FROM rental NATURAL JOIN inventory NATURAL JOIN film WHERE rental.customer_id = customer.customer_id)) ORDER BY first_name ASC, last_name ASC;

#ou
SELECT first_name, last_name FROM customer WHERE (SELECT COUNT(*) FROM category WHERE category_id IN (SELECT category_id FROM film NATURAL JOIN inventory)) = (SELECT COUNT(DISTINCT categoryid) FROM rental NATURAL JOIN intenvory NATURAL JOIN film WHERE rentral.customer_id = customer.customer_id) ORDER BY first_name ASC, last_name ASC;

#7
###ver 6

#Aula 8

#1
SELECT country, SUM(num) FROM (SELECT store.country, 1 AS num FROM staff_store WHERE staff.store_id = store.store_id UNION ALL SELECT country, 0 FROM store WHERE store_id NOT IN (SELECT STORE_id FROM staff) AS temp GROUP BY country ORDER BY country ASC;

#2
SELECT title, dvd_count FROM 
	(SELECT film.title, COUNT(*) AS dvd_count FROM inventory NATURAL JOIN film GROUP BY film.film_id UNION ALL SELECT title, 0 FROM film WHERE film_id NOT IN (SELECT film_id FROM inventory)) AS temp ORDER BY title ASC;

#3
SELECT film.title FROM actor NATURAL JOIN film_actor NATURAL JOIN film NATURAL JOIN inventory NATURAL JOIN rental WHERE actor.first_name = 'HARRISON' AND actor.last_name = 'BALE' GROUP BY film.film_id HAVING COUNT(*) > 20 ORDER BY film.title ASC;

#4
SELECT title FROM film WHERE film_id IN (SELECT film_id FROM inventory GROUP BY film_id HAVING COUNT(*) = (SELECT COUNT(*) FROM inventor GROUP BY film_id ORDER BY COUNT(*) DESC LIMIT 1)) ORDER BY title ASC;

#5
SELECT customer.first_name, customer.last_name FROM film, inventory, rental, customer WHERE film.film_id = inventory.film_id AND inventory.inventory_id = rental.inventory_id AND rental.customer_id = customer.customer_id AND rental.return_date IS NOT NULL AND film.rental_duration < DATEDIFF(rental.return_date, rental.rent_date) GROUP BY customer.customer_id ORDER BY customer.first_name ASC; customer.last_name ASC;

#6
SELECT category.name, AVG (actor_count) FROM category NATURAL JOIN (SELECT film.category_id, COUNT(*) AS actor_count FROM film NATURAL JOIN film_actor) GROUP BY film.film_id UNION ALL SELECT category_id, 0 FROM film WHERE film_id NOT IN (SELECT film_id FROM film_actor) UNION ALL SELECT category_id, 0 FROM category WHERE category_id NOT IN (SELECT category_id FROM film) AS temp GROUP BY category.category_id ORDER BY category.name ASC;

#7	
SELECT a1.first_name, a1.last_name, a2.first_name, a2.last_name FROM film_actor AS fa1, film_actor AS fa2, actor AS a1, actor AS a2 WHERE fa1.film_id = fa2.film_id AND fa1.actor_id < fa2.actor_id AND fa1.actor_id = a1.actor_id AND fa2.actor_id = a2.actor_id GROUP BY fa1.actor_id, fa2.actor_id HAVING COUNT(*) = (SELECT COUNT(*) FROM film_actor AS fa1, film_actor AS fa2 HERE fa1.film_id = fa2.film_id AND fa1.actor_id < fa2.actor_id GROUP BY fa1.actor_id, fa2.actor_id ORDER BY COUNT(*) DESC LIMIT 1)ORDER BY a1.first_name ASC, a1.last_name ASC, a2.first_name ASC, a2.last_name ASC;

/* SQL 1 */
/* P1 */

SELECT name FROM category WHERE name LIKE "S%"
    ORDER BY 1;

/* P2 */

SELECT first_name, last_name FROM actor
    ORDER BY 1,2;

/* P3 */

SELECT DISTINCT title FROM (film NATURAL JOIN inventory NATURAL JOIN rental) 
	WHERE customer_id = 258
    ORDER BY 1;

/* P4  */

SELECT title FROM film NATURAL JOIN film_actor NATURAL JOIN actor
    WHERE first_name LIKE 'HARRISON' AND last_name LIKE 'BALE'
    ORDER BY 1;

/* P5  */

SELECT first_name , last_name FROM customer 
	WHERE customer_id IN (SELECT customer_id FROM customer NATURAL JOIN  rental
        WHERE return_date IS NULL)
         ORDER BY 1,2;

/*  P6 */

SELECT A.first_name, A.last_name, B.first_name, B.last_name
    FROM staff AS A, staff AS B, store
        WHERE A.store_id = store.store_id 
            AND  store.manager = B.staff_id
                ORDER BY 1,2;


/*  P7 */

Select first_name, last_name From actor
        Where actor_id in (
        	select distinct actor_id from actor natural join film_actor 
            	Where film_id in (
                	select film_id from film natural join category where name = "Drama"))
            Order by 1,2;
/* //////////////////////////////////////////////////////////////////////////////////
/* SQL 2 */
/*  P1 */

(SELECT first_name, last_name FROM customer)
UNION ALL 
(SELECT first_name, last_name FROM staff)
ORDER BY 1,2;

/*  P2*/

SELECT title FROM film 
	WHERE length IN (SELECT MAX(length) FROM film)
	ORDER BY 1;

/*  P3 */

SELECT title FROM film
        WHERE film_id IN
        (SELECT film_id FROM inventory WHERE inventory_id IN
          (SELECT inventory_id FROM rental))
          AND film_id NOT IN
          (SELECT film_id from inventory WHERE inventory_id IN
            (SELECT inventory_id FROM rental WHERE customer_id IN
              (SELECT customer_id FROM customer WHERE first_name = "LEE" AND last_name = "HAWKS")));

/*  P4 */

select title from film where film_id not in
(select film_id from film_actor) order by title;

/*  P5*/

select title from film natural join inventory where inventory_id not in (
    select inventory_id from rental) order by title;

/*  P6 */
select first_name, last_name from customer
where customer_id in
  (select customer_id from rental natural join inventory natural join film group by customer_id
    having count(distinct category_id) = (select count(distinct category_id) from film))
order by 1,2;

/*  P7 */
select first_name, last_name from film natural join film_actor natural join actor
group by actor_id 
having count(distinct category_id) = (select count(distinct category_id) from film) 
order by 1,2;

/*/////////////////////////////////////////////////////*/
/* SQL 3 */

/*  P1 */

select country, sum(num) from (
  select store.country, 1 as num
    from staff, store
    where staff.store_id=store.store_id
  UNION ALL
select country, 0 from store 
	where store_id not in (select store_id from staff)) as temp 
group by country 
order by country asc;

/*  P2 */

select title, sum(num) from(
  select title, 1 as num from film natural join inventory
   UNION ALL
   select title, 0 as num from film
      where film_id not in (select film_id from inventory)
) as temp group by title order by title asc;


/*  P3 */

select title from film where film_id in
    (select film_id from film natural join
    film_actor natural join actor
    where first_name = 'HARRISON' and last_name = 'BALE')
    and film_id in (
      select film_id from film natural join inventory natural join rental
      group by film_id having count(film_id)>20)
      order by title asc ;

/*  P4 */
/*Selecionar o título dos filmes dos quais há mais DVDs, ordenado alfabeticamente pelo título.
*/

select title from film natural join inventory
  group by 1
  having count(inventory_id) = (select count(inventory_id)
  from inventory
  group by film_id
  order by 1 desc limit 1)
  order by 1;
/*  P5 */
/*
Selecionar o primeiro e último nome dos clientes que já fizeram devoluções tardias, ordenado alfabeticamente pelo primeiro e último nome.
*/

select first_name, last_name from (
  select distinct first_name, last_name, customer_id from customer natural join rental natural join inventory natural join film
    where return_date > rent_date + rental_duration
    or (return_date is null and datediff(now(), rent_date ) > rental_duration)
    order by 1,2) as tmp1;

/*  P6 */
/*
*Selecionar por nome de categoria, o número médio de actores por filme dessa categoria, ordenado alfabeticamente pelo nome.
*/

select name, avg(c) from category natural join (
    select film_id, category_id , count(actor_id) as c from film natural left join film_actor group by 1,2
  union all
    select NUll as film_id, category_id, 0 as c from category where category_id not in (select category_id from film natural left join film_actor)
) as tmp
group by 1 order by 1;



/*******************************************************************************************************************************/
/* SQL 4 */

/*  P1 */
SELECT title FROM film  NATURAL JOIN category
	WHERE category.name LIKE 'Sports'
	ORDER BY 1; 

/*  P2 */

SELECT first_name, last_name FROM actor NATURAL JOIN film_actor NATURAL JOIN film 
	WHERE  title LIKE 'WYOMING STORM'
ORDER BY 1,2;


/*  P3 */

SELECT DISTINCT first_name, last_name FROM actor NATURAL JOIN film_actor NATURAL JOIN film NATURAL JOIN category
	WHERE category.name LIKE 'Drama'
ORDER BY 1,2;

/*  P4 */

SELECT DISTINCT title FROM film NATURAL JOIN inventory 
	WHERE store_id = 1 AND title NOT IN (SELECT title FROM film NATURAL JOIN inventory 
		WHERE store_id <> 1)
	ORDER BY 1;

/*  P5 */


SELECT DISTINCT first_name, last_name FROM actor NATURAL JOIN film_actor NATURAL JOIN film
WHERE film_id IN (SELECT film_id FROM film NATURAL JOIN film_actor NATURAL JOIN actor
	WHERE first_name LIKE 'JULIA' AND last_name LIKE 'ZELLWEGER') AND !(first_name='JULIA' and last_name='ZELLWEGER')
ORDER BY 1,2;

/*  P6 */

SELECT COUNT(*) 
	FROM (SELECT DISTINCT actor_id FROM actor NATURAL JOIN film_actor NATURAL JOIN film NATURAL JOIN category WHERE category.name LIKE 'Action') AS subquery; 

/*  P7 */

SELECT DISTINCT first_name , last_name FROM customer NATURAL JOIN rental NATURAL JOIN inventory , store
	WHERE store.country = customer.country
ORDER BY 1,2;

/*  P8 */

SELECT name , AVG(length) 
	FROM (select name, length from film natural join category
			UNION ALL
			SELECT name, 0 FROM category 
				WHERE category_id NOT IN (SELECT category_id FROM category NATURAL JOIN film)) AS subquery
GROUP BY 1
ORDER BY 1;	

/*  P9 */

select name from category
  where category_id in (select category_id from film natural join category
  group by category_id having count(film_id) = (select max(maxi) from (
    select count(film_id) as maxi
    from category natural join film group by category_id) as tmp1));

/*  P10 */

select first_name, last_name from customer
  where customer_id in (select customer_id from film natural join inventory natural join rental natural left join customer
    group by customer_id 
    having sum(length) = (select max(duracao) from (select sum(length) as duracao
    from film natural join inventory natural join rental natural left join customer group by customer_id) as tmp1)) order by 1, 2;
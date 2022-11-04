select first_name, last_name from customer
where customer_id in
  (select customer_id from rental natural join inventory natural join film group by customer_id
    having count(distinct category_id) = (select count(distinct category_id) from film))
order by 1,2;
/* 
*/
select title, sum(num) from(
  select title, 1 as num from film natural join inventory
   UNION ALL
   select title, 0 as num from film
      where film_id not in (select film_id from inventory)
) as temp group by title order by title asc;
/* 
*/
select title from film where film_id in
    (select film_id from film natural join
    film_actor natural join actor
    where first_name = 'HARRISON' and last_name = 'BALE')
    and film_id in (
      select film_id from film natural join inventory natural join rental
      group by film_id having count(film_id)>20)
      order by title asc ;
/* 
*/

select first_name, last_name from (
  select distinct first_name, last_name, customer_id from customer natural join rental natural join inventory natural join film
    where return_date > rent_date + rental_duration
    or (return_date is null and datediff(now(), rent_date ) > rental_duration)
    order by 1,2) as tmp1;

/*
*/

select name, avg(c) from category natural join (
    select film_id, category_id , count(actor_id) as c from film natural left join film_actor group by 1,2
  union all
    select NUll as film_id, category_id, 0 as c from category where category_id not in (select category_id from film natural left join film_actor)
) as tmp
group by 1 order by 1;


/*
*/

select country, sum(num) from (
  select store.country, 1 as num
    from staff, store
    where staff.store_id=store.store_id
  UNION ALL
select country, 0 from store 
	where store_id not in (select store_id from staff)) as temp 
group by country 
order by country asc;

/*
*/

select name, avg(c) from category natural join (
    select film_id, category_id , count(actor_id) as c from film natural left join film_actor group by 1,2
  union all
    select NUll as film_id, category_id, 0 as c from category where category_id not in (select category_id from film natural left join film_actor)
) as tmp
group by 1 order by 1;

/*
*/

SELECT COUNT(*) 
	FROM (SELECT DISTINCT actor_id FROM actor NATURAL JOIN film_actor NATURAL JOIN film NATURAL JOIN category WHERE category.name LIKE 'Action') AS subquery; 

/*
*/
select name from category
  where category_id in (select category_id from film natural join category
  group by category_id having count(film_id) = (select max(maxi) from (
    select count(film_id) as maxi
    from category natural join film group by category_id) as tmp1));
 
 /*
 */
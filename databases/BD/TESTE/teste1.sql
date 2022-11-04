--Teste 1
--Tudo com Accepted

1. select title from film where film_id in (select film_id from film where category_id in (select category_id from category where name like "drama")) order by length desc, title;

2. select title from film where film_id in (select film_id from film where length = (select max(length) from film) and rating like 'G') order by 1; 

3. select first_name, last_name from actor where actor_id in (select actor_id from (select actor_id, count(film_id)  as F from film_actor group by actor_id) as A where F >30) order by 1,2;


4. Select A from (select A.actor_id as A, B.actor_id as B from actor as A, actor as B where A.first_name = B.first_name and A.last_name = B.last_name) as C where A <> B order by 1;

5. select first_name, last_name from customer where customer_id in (select customer_id from rental where inventory_id in (select inventory_id from inventory where film_id in (select film_id from film where title like "C%S"))) order by 1,2;

6.

7.

8.

9. select title from film where length < (select length from film where title = "zhivago core") order by title;

10.

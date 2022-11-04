SELECT category.name, count(film.length) FROM category LEFT JOIN film ON category.category_id=film.category_id GROUP BY category.category_id 
ORDER BY count(*) DESC LIMIT 2;




SELECT name AS CATEGORIA from (select category.name, count(film_id) from film right join category on film.category_id=category.category_id group by category.name order by 2 DESC LIMIT 2) T;


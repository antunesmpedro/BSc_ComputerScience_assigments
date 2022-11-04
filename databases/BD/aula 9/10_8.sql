SELECT category.name, IFNULL(AVG(film.length),0) FROM category LEFT JOIN film ON category.category_id=film.category_id GROUP BY category.category_id ORDER BY category.name;

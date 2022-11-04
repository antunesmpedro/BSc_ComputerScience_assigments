select title from film, category where
       film.category_id=category.category_id and
       category.name="Sports"
	order by 1;
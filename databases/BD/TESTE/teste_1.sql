select title from film inner join category on film.category_id=category.category_id where category.name="Drama" order by film.length DESC, title;

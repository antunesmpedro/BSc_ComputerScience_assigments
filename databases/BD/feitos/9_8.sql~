select category.name,AVG(film.length) from 
       category left outer join film on category.category_id=film.category_id
        group by category.category_id 
	order by 1;
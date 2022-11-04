/*select* from(select category.name, avg(film.length) from film, category 
	where film.category_id =category.category_id) 
	order by 1;
*/





/*


select category.name,AVG(film.length) from 
       category left outer join film on category.category_id=film.category_id
        group by 1 
	order by category.name;*/
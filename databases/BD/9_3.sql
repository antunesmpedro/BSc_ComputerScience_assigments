select title from film where
        film_id in( select film_id from inventory where store_id =1) and
	 film_id not in(select distinct film_id from inventory where film_id<>1)
	 order by 1;
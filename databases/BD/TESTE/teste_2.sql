select title from(select title, length from film where rating like 'G' group by title order by 2 DESC LIMIT 3) T order by 1;

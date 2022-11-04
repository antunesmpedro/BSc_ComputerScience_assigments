select first_name, last_name from(select count(*), first_name, last_name from actor group by 2,3 order by 1 DESC LIMIT 1) T;

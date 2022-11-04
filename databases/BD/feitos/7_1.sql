select* from(select first_name , last_name from customer union all
       select first_name, last_name from staff) as T
       	      order by 1,2; 
       	
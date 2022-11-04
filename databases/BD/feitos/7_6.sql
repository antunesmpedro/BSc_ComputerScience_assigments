select first_name, last_name from customer where not exists(
select * from category where category_id in(select category_id from
film natural join inventory) and category_id not in ( select category_id from
rental natural join inventory natural join film where 
rental.customer_id=customer.customer_id))
	order by 1,2;
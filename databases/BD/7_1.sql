(select first_name, last_name from customer)

	UNION

(select first_name, last_name from staff);

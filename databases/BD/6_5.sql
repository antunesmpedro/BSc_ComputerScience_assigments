select distinct customer.first_name, customer.last_name from customer, rental where customer.customer_id=rental.customer_id and rental.return_date is NULL order by 1,2;

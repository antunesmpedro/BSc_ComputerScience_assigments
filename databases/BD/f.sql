select A.first_name, A.last_name, B.first_name, B.last_name 
from staff as A, staff as B, store where
	A.store_id = store.store_id and
	store.manager = B.staff_id
	order by 1,2;
	


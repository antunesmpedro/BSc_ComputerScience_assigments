select store.country , count(distinct staff.staff_id) from store left outer join staff 
       on store.country =staff.country
       	  group by 1  order by 1; 
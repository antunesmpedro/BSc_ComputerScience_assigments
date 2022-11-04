select store.country, count(distinct staff.staff_id) from

       store left outer join staff on store.store_id=staff.store_id
       
       group by 1 order by 1,2;
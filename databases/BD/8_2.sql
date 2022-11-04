select title, count(distinct inventory_id) 
       from film left outer join inventory	
       	    on film.film_id=inventory.film_id
	    	  group by 1 order by 1;

// SE O PEDIDO FOR O NUMERO TOTAL DE FILMES LEFT JOIN otherwise
					INNER JOIN

5-Resolução 1
select
    actor.first_name,
    actor.last_name
from
    actor
inner join
    film_actor
on
    actor.actor_id=film_actor.actor_id
inner join
    (select
        actor.actor_id,
        film_actor.film_id
    from
        actor
    INNER JOIN
        film_actor on actor.actor_id = film_actor.actor_id and actor.first_name = 'JULIA' and actor.last_name='ZELLWEGER') film_julia on film_julia.film_id = film_actor.film_id where actor.actor_id <> film_julia.actor_id group by actor.first_name, actor.last_name




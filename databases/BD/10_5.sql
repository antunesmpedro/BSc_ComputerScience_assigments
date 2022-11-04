5-
select
    actor.first_name,
    actor.last_name
from
    actor
inner join
    film_actor
on
    actor.actor_id = film_actor.actor_id
inner join
    film_actor f
on
    film_actor.film_id = f.film_id and f.actor_id <> actor.actor_id
INNER join
    actor a
on
    f.actor_id = a.actor_id and a.actor_id <> actor.actor_id
where
    a.first_name = 'JULIA' and a.last_name = 'ZELLWEGER '
group by actor.actor_id

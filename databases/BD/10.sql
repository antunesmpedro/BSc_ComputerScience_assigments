10-
SELECT
    domain.first_name,
    domain.last_name
FROM
    (
    SELECT
       customer.first_name,
        customer.last_name,
        TIMESTAMPDIFF(MINUTE, rental.rent_date, rental.return_date) as M
    FROM
       customer
    INNER JOIN
        rental
    ON
        rental.customer_id = customer.customer_id
    GROUP BY
        customer.customer_id
    ) domain
ORDER BY
   domain.M DESC, domain.first_name ASC, domain.last_name ASC
LIMIT 20








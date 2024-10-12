SELECT u.username, s.ticker, t.price, p.quantity_left
FROM portfolio AS p
JOIN transactions AS t ON t.id = p.transactions_id
JOIN stocks AS s ON s.id = t.stocks_id
JOIN users AS u ON u.id = t.users_id
WHERE username='new';

/*
The query above yields something like this:
+----------+--------+-------+---------------+
| username | ticker | price | quantity_left |
+----------+--------+-------+---------------+
| new      | FFWM   | 5.95  | 2             |
| new      | FFWM   | 6.75  | 3             |
| new      | FFWM   | 6.75  | 3             |
| new      | KO     | 70.73 | 50            |
| new      | KO     | 70.68 | 1             |
+----------+--------+-------+---------------+
*/

-- Now I group by ticker and calculate weighted average price, as well as total quantities:
 SELECT ticker,
        SUM(price * quantity_left) AS position_value,
        SUM(quantity_left) AS quantity,
        SUM(price * quantity_left) / SUM(quantity_left) AS weighted_average_price
   FROM (
        SELECT u.username, s.ticker, t.price, p.quantity_left
        FROM portfolio AS p
        JOIN transactions AS t ON t.id = p.transactions_id
        JOIN stocks AS s ON s.id = t.stocks_id
        JOIN users AS u ON u.id = t.users_id
        WHERE username='new'
 )
 GROUP BY ticker;
-- The query above is useful for debugging, but I don't really need to join the users table, since I have the user id in the session.
SELECT ticker,
        SUM(price * quantity_left) AS position_value,
        SUM(quantity_left) AS quantity,
        SUM(price * quantity_left) / SUM(quantity_left) AS weighted_average_price
   FROM (
        SELECT s.ticker, t.price, p.quantity_left
        FROM portfolio AS p
        JOIN transactions AS t ON t.id = p.transactions_id
        JOIN stocks AS s ON s.id = t.stocks_id
        WHERE t.users_id = 2 -- REPLACE 2 WITH ? IN THE PYTHON CODE
 )
 GROUP BY ticker;


-- DEPRECATED: Show transaction history
SELECT ticker,
       price,
       ABS(quantity) as quantity,
       ABS(price*quantity) as total,
       CASE
          WHEN quantity > 0 THEN 'buy'
          WHEN quantity < 0 THEN 'sell'
          ELSE 'unknown'
       END AS transaction_type
FROM transactions
JOIN stocks AS s ON s.id = transactions.stocks_id
WHERE users_id = 2;

-- Show transaction history
SELECT ticker,
       price,
       quantity,
       ABS(price*quantity) as total,
       tt.type AS type
FROM transactions AS t
JOIN stocks AS s ON s.id = t.stocks_id
JOIN transaction_types as tt ON tt.id = t.type
WHERE users_id = 2
ORDER BY t.datetime DESC;

SELECT date(t.datetime, 'unixepoch') AS 'date',
                       time(t.datetime, 'unixepoch') AS 'time',
                       ticker AS symbol,
                       tt.type AS type,
                       quantity as 'shares',
                       price AS 'share price',
                       price*quantity as total
                FROM transactions AS t
                JOIN stocks AS s ON s.id = t.stocks_id
                JOIN transaction_types as tt ON tt.id = t.type
                WHERE users_id  = 2
                ORDER BY t.datetime DESC;

-- Show transaction history with datetime
SELECT datetime(t.datetime, 'unixepoch') AS 'datetime',
       ticker,
       price,
       ABS(quantity) as quantity,
       ABS(price*quantity) as total,
       CASE
          WHEN quantity > 0 THEN 'buy'
          WHEN quantity < 0 THEN 'sell'
          ELSE 'unknown'
       END AS transaction_type
FROM transactions AS t
JOIN stocks AS s ON s.id = t.stocks_id
WHERE users_id = 2
LIMIT 5;

-- Show transaction history with date and time in separate columns
SELECT datetime(t.datetime, 'unixepoch') AS 'date',
       time(t.datetime, 'unixepoch') AS 'time',
       ticker,
       price,
       ABS(quantity) as quantity,
       ABS(price*quantity) as total,
       CASE
          WHEN quantity > 0 THEN 'buy'
          WHEN quantity < 0 THEN 'sell'
          ELSE 'unknown'
       END AS transaction_type
FROM transactions AS t
JOIN stocks AS s ON s.id = t.stocks_id
WHERE users_id = 2
LIMIT 5;

-- Fetch cash amount for a specific user:
SELECT id, username, cash FROM users;

SELECT cash FROM users
WHERE id = 2;


WITH vars AS (SELECT 2 AS user_id, -3000 AS cash_added)
UPDATE users
SET cash = (SELECT cash FROM users WHERE id = (SELECT user_id FROM vars)) + (SELECT cash_added FROM vars)
WHERE id = (SELECT user_id FROM vars);

-- Fetch transaction history (After having implemented cash add)
SELECT
       date(t.datetime, 'unixepoch') AS 'date',
       time(t.datetime, 'unixepoch') AS 'time',
       CASE
              WHEN ticker IS NULL THEN '-'
              ELSE ticker
       END AS symbol,
       tt.type AS type,
       quantity AS 'shares',
       price AS 'share price',
       CASE
              WHEN t.stocks_id NOT NULL THEN price * quantity
              ELSE t.price
       END AS total
FROM transactions AS t
LEFT JOIN stocks AS s ON s.id = t.stocks_id
JOIN transaction_types AS tt ON tt.id = t.type
WHERE users_id  = 2
ORDER BY t.datetime DESC
LIMIT 5;


-- Fetch transaction history after implementing both add and withdraw

SELECT
date(t.datetime, 'unixepoch') AS 'date',
time(t.datetime, 'unixepoch') AS 'time',
CASE
       WHEN ticker IS NULL THEN '-'
       ELSE ticker
END AS symbol,
tt.type AS type,
quantity AS 'shares',
price AS 'share price',
CASE
       WHEN t.stocks_id NOT NULL THEN price * quantity
       ELSE
       CASE
              WHEN t.type = 3 THEN price
              WHEN t.type = 4 THEN price * (-1)
       END
END AS total
FROM transactions AS t
LEFT JOIN stocks AS s ON s.id = t.stocks_id
JOIN transaction_types AS tt ON tt.id = t.type
WHERE users_id  = 2
ORDER BY t.datetime DESC
LIMIT 5;

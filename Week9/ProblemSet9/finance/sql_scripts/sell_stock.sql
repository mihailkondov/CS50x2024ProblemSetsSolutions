 SELECT ticker,
        SUM(quantity_left) AS quantity
FROM (
        SELECT s.ticker, t.price, p.quantity_left
        FROM portfolio AS p
        JOIN transactions AS t ON t.id = p.transactions_id
        JOIN stocks AS s ON s.id = t.stocks_id
        WHERE t.users_id = 2
)
GROUP BY ticker;

-- Fetch quantity of given stock owned by a given user
SELECT ticker, SUM(quantity_left) AS shares_available
FROM (
        SELECT s.ticker, quantity_left
        FROM portfolio as p
        JOIN transactions as t ON t.id = p.transactions_id
        JOIN stocks as s ON s.id = t.stocks_id
        WHERE t.users_id = 1
        AND s.ticker = 'KO'
)
GROUP BY ticker;

-- fetch a list of all transactions from the shares owned
SELECT s.id, s.ticker, quantity_left, t.datetime, t.id
FROM portfolio as p
JOIN transactions as t ON t.id = p.transactions_id
JOIN stocks as s ON s.id = t.stocks_id
WHERE quantity_left > 0
AND t.users_id = 2
AND s.ticker = 'AMD'
ORDER BY t.datetime ASC;

-- alter the transactions in portfolio with the sold stocks
-- +--------+---------------+------------+----+
-- | ticker | quantity_left |  datetime  | id |
-- +--------+---------------+------------+----+
-- | AMD    | 2             | 1728416372 | 11 |
-- | AMD    | 1             | 1728416505 | 12 |
-- | AMD    | 1             | 1728416614 | 13 |
-- | AMD    | 1             | 1728416704 | 14 |
-- | AMD    | 2             | 1728416717 | 15 |
-- | AMD    | 1             | 1728417773 | 18 |
-- +--------+---------------+------------+----+
BEGIN TRANSACTION;


        CREATE TEMPORARY TABLE IF NOT EXISTS temp_sold (id INTEGER, t_quantity_left INTEGER);
        DELETE FROM temp_sold;



        INSERT INTO temp_sold(id, t_quantity_left)
        VALUES (11, 0), (12, 0)

        GO

        UPDATE portfolio
        SET quantity_left = (
                SELECT quantity_left
                FROM temp_sold
                WHERE temp_sold.id = portfolio.transactions_id
        )
        WHERE portfolio.transactions_id IN (SELECT id FROM temp_sold);

ROLLBACK;

-- Current stock reserve query
SELECT s.id AS stock_id, s.ticker, quantity_left, t.datetime, t.id
FROM portfolio as p
JOIN transactions as t ON t.id = p.transactions_id
JOIN stocks as s ON s.id = t.stocks_id
WHERE quantity_left > 0
AND t.users_id = 2
AND s.ticker = 'BAC'
ORDER BY t.datetime ASC;

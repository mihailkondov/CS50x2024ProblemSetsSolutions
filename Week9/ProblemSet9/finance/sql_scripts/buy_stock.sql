
-- Look for stock
SELECT id FROM stocks WHERE ticker='KO';

-- Insert new stock
INSERT INTO stocks (ticker, company_name) VALUES ('KO', 'Coca-Cola Company (The) Common Stock');

BEGIN TRANSACTION
-- Insert transaction
    INSERT INTO transactions (price, quantity, stocks_id, users_id)
    VALUES (5.95, 2, 2, 2);

    SELECT id, quantity
    FROM transactions
    WHERE id = last_insert_rowid();

    INSERT INTO portfolio (transactions_id, quantity_left)
    SELECT id, quantity
    FROM transactions
    WHERE id = last_insert_rowid();


    UPDATE users
    SET cash = 1000
    WHERE id ='1';

-- Take money
END TRANSACTION


    SELECT id FROM stocks WHERE ticker='BAC';



    SELECT id FROM stocks WHERE ticker='BAC';

BEGIN TRANSACTION;
    INSERT INTO stocks (ticker, company_name) VALUES ('BAC', 'Bank of America Corporation Common Stock');
    INSERT INTO transactions (price, 'type', quantity, stocks_id, users_id) VALUES (38.73, 1, 3, 11, 2);
    INSERT INTO portfolio (transactions_id, quantity_left)
                            SELECT t.id, t.quantity
                            FROM transactions AS t
                            WHERE id = last_insert_rowid();
ROLLBACK TRANSACTION;

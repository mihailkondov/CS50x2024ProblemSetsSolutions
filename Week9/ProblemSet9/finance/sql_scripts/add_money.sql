-- Fetch cash amount for a specific user:
SELECT id, username, cash FROM users;

SELECT cash FROM users
WHERE id = 2;


-- OPERATION: user adds cash:
BEGIN TRANSACTION;

    -- Change the cash of specific user by specific amount
    WITH vars AS (SELECT 2 AS user_id, 1000 AS cash_added) -- Set user and amount on this row
    UPDATE users
    SET cash = (SELECT cash FROM users WHERE id = (SELECT user_id FROM vars)) + (SELECT cash_added FROM vars)
    WHERE id = (SELECT user_id FROM vars);

    -- Record transaction
    INSERT INTO transactions (price, type, quantity, users_id)
    VALUES (1000, 3, 0, 2);

ROLLBACK;

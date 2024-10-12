CREATE TABLE stocks (
    'id'        INTEGER PRIMARY KEY AUTOINCREMENT,
    'ticker'    TEXT    UNIQUE      NOT NULL,
    'company_name'      TEXT
);
CREATE UNIQUE INDEX ticker ON stocks (ticker);
INSERT INTO sqite_sequence VALUES('stocks', 0);

-- Here is a link that explains unix epoch time
-- https://www.sqlite.org/lang_datefunc.html#:~:text=The%20unixepoch()%20function%20normally,specified%20as%20the%20first%20argument.
-- look for
-- unixepoch(...)
-- CAST(strftime('%s', ...) as INT)
CREATE TABLE transactions (
    'id'        INTEGER     PRIMARY KEY AUTOINCREMENT,
    'datetime'  INTEGER     NOT NULL    DEFAULT (unixepoch(CURRENT_TIMESTAMP)),
    'price'     NUMERIC     NOT NULL, --This being numeric seems kinda troll, but since cash is already declared as numeric I will keep it like this for consistency
    'quantity'  INTEGER     NOT NULL,
    'stocks_id' INTEGER     NOT NULL,
    'users_id'  INTEGER     NOT NULL,
    FOREIGN KEY (stocks_id) REFERENCES stocks(id),
    FOREIGN KEY (users_id) REFERENCES users(id)
);
CREATE UNIQUE INDEX id ON transactions(id);
CREATE INDEX transactons_stocks ON transactions(stocks_id);
INSERT INTO sqite_sequence VALUES('transactions', 0);


-- PORTFOLIO <- tracks unsold stock quantities from each purchase transaction
CREATE TABLE portfolio (
    'id'                INTEGER     PRIMARY KEY AUTOINCREMENT,
    'transactions_id'   INTEGER     NOT NULL,
    'quantity_left'     INTEGER     NOT NULL,
    FOREIGN KEY (transactions_id) REFERENCES transactions(id)
);
CREATE INDEX portfolio_transactions_id_index ON portfolio(transactions_id)

-- This command populates the portfolio table assuming no sales have taken place:
INSERT INTO portfolio (transactions_id, quantity_left)
SELECT id, quantity
  FROM transactions
 WHERE quantity > 0;

-- Create table transaction types
CREATE TABLE transaction_types(
       'id'     INTEGER PRIMARY KEY AUTOINCREMENT,
       'type'   INTEGER NOT NULL
);

INSERT INTO transaction_types ('type')
VALUES
       ('buy'),
       ('sell'),
       ('cash_add'),
       ('cash_withdraw');

SELECT * FROM transaction_types;
-- Alter the type column in transactions to be a number instead of text
-- First I will create a new table to make sure every thing works, and then I will try to change the existing transactions table


-- This fetches the data that I want to insert into the new transactions table
SELECT id,
       datetime,
       price,
       CASE
          WHEN quantity > 0 THEN 1
          WHEN quantity < 0 THEN 2
          ELSE 'error: quantity value of 0'
       END AS 'type',             -- Save transaction type
       ABS(quantity) as quantity, -- No more negative quantities
       stocks_id,
       users_id
FROM transactions;

CREATE TABLE transactions2 (
    'id'        INTEGER     PRIMARY KEY AUTOINCREMENT,
    'datetime'  INTEGER     NOT NULL    DEFAULT (unixepoch(CURRENT_TIMESTAMP)),
    'price'     NUMERIC     NOT NULL,
    'type'      INTEGER     NOT NULL,
    'quantity'  INTEGER     NOT NULL,
    'stocks_id' INTEGER,
    'users_id'  INTEGER     NOT NULL,
    FOREIGN KEY (stocks_id) REFERENCES stocks(id),
    FOREIGN KEY (type) REFERENCES transaction_types(id),
    FOREIGN KEY (users_id) REFERENCES users(id)
);
-- CREATE UNIQUE INDEX id ON transactions(id);
-- CREATE INDEX transactons_stocks ON transactions(stocks_id);

INSERT INTO transactions2 (id, datetime, price, type, quantity, stocks_id, users_id)
SELECT id,
       datetime,
       price,
       CASE
          WHEN quantity > 0 THEN 1
          WHEN quantity < 0 THEN 2
          ELSE 'error: quantity value of 0'
       END AS 'type',             -- Save transaction type
       ABS(quantity) as quantity, -- No more negative quantities
       stocks_id,
       users_id
FROM transactions;

SELECT * FROM transactions2;

ALTER TABLE transactions
RENAME TO transactions_old;

ALTER TABLE transactions2
RENAME TO transactions;

-- Changing the foreign key of portfolio.transactions_id to reference the newly created table transactions instead of transactions_old

ALTER TABLE portfolio
RENAME TO portfolio_old;

CREATE TABLE portfolio (
    'id'                INTEGER     PRIMARY KEY AUTOINCREMENT,
    'transactions_id'   INTEGER     NOT NULL,
    'quantity_left'     INTEGER     NOT NULL,
    FOREIGN KEY (transactions_id) REFERENCES "transactions"(id)
);
CREATE INDEX portfolio_transactions_id_index ON portfolio(transactions_id);

INSERT INTO portfolio
SELECT * FROM portfolio_old;



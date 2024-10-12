-- In 5.sql, write a SQL query that returns the average energy of all the songs.
-- Your query should output a table with a single column and a single row containing the average energy.

-- SELECT AVG(SELECT energy FROM songs); -- Cannot pass subqueries to AVG(). Pass only columns like AVG(energy)
SELECT AVG(energy) FROM songs;

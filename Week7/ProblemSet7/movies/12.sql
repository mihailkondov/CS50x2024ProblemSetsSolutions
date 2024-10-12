--  In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
--    Your query should output a table with a single column for the title of each movie.
--    You may assume that there is only one person in the database with the name Bradley Cooper.
--    You may assume that there is only one person in the database with the name Jennifer Lawrence.


-- This is my original solution
-- 5.050 seconds runtime
SELECT title
  FROM (
       SELECT movies.id, movies.title
         FROM movies
         JOIN stars ON movies.id = stars.movie_id
         JOIN people ON people.id = stars.person_id
        WHERE name = 'Bradley Cooper'
  ) as movies
  JOIN stars ON movies.id = stars.movie_id
  JOIN people ON people.id = stars.person_id
 WHERE name = 'Jennifer Lawrence';


-- -- This is the first optimisation Chat GPT suggested, but it runs in the same time
-- -- 5.084 seconds

-- SELECT DISTINCT m.title
-- FROM movies m
-- JOIN stars s1 ON m.id = s1.movie_id
-- JOIN people p1 ON p1.id = s1.person_id
-- JOIN stars s2 ON m.id = s2.movie_id
-- JOIN people p2 ON p2.id = s2.person_id
-- WHERE p1.name = 'Bradley Cooper'
--   AND p2.name = 'Jennifer Lawrence';


-- -- Once I typed that the suggestion above is too slow I got these optimizations as further suggestions

-- -- 1) use EXISTS: <- this is terribly slow (50+ seconds runtime and I terminated it after that)

-- SELECT DISTINCT m.title
-- FROM movies m
-- WHERE EXISTS (
--     SELECT 1
--     FROM stars s1
--     JOIN people p1 ON p1.id = s1.person_id
--     WHERE s1.movie_id = m.id
--     AND p1.name = 'Bradley Cooper'
-- )
-- AND EXISTS (
--     SELECT 1
--     FROM stars s2
--     JOIN people p2 ON p2.id = s2.person_id
--     WHERE s2.movie_id = m.id
--     AND p2.name = 'Jennifer Lawrence'
-- );


-- -- 2) filter people first then do the join
-- -- 5.405 <- slightly slower than my original solution

-- WITH filtered_people AS (
--     SELECT id, name
--     FROM people
--     WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
-- )
-- SELECT DISTINCT m.title
-- FROM movies m
-- JOIN stars s1 ON m.id = s1.movie_id
-- JOIN filtered_people p1 ON p1.id = s1.person_id
-- JOIN stars s2 ON m.id = s2.movie_id
-- JOIN filtered_people p2 ON p2.id = s2.person_id
-- WHERE p1.name = 'Bradley Cooper'
--   AND p2.name = 'Jennifer Lawrence';

-- -- 3) simplify filtering
-- -- 3.403 sec <- this one actually worked

-- SELECT m.title
-- FROM movies m
-- JOIN stars s ON m.id = s.movie_id
-- JOIN people p ON p.id = s.person_id
-- WHERE p.name IN ('Bradley Cooper', 'Jennifer Lawrence')
-- GROUP BY m.title
-- HAVING COUNT(DISTINCT p.name) = 2;


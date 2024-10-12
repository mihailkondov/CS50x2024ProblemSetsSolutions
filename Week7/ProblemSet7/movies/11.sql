--  In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman
--  starred in, starting with the highest rated.
--    Your query should output a table with a single column for the title of each movie.

SELECT title
  FROM movies
  JOIN ratings ON movies.id = ratings.movie_id
  JOIN stars ON stars.movie_id = movies.id
  JOIN people ON people.id = stars.person_id
 WHERE people.name = 'Chadwick Boseman'
 ORDER BY rating DESC
 LIMIT 5;

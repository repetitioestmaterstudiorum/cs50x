# load csv file data directly with sqlite

`sqlite3 favorites.db`
`.mode csv`
`.import favorites.csv favorites`

## open the db with sqlite3

`sqlite3 favorites.db`

## print out the automatically assumed schema

`.schema`

CREATE TABLE IF NOT EXISTS "favorites"(
"Timestamp" TEXT,
"title" TEXT,
"genres" TEXT
);

# useful sqlite commands

`.timer on` -> prints query times

## create an index

`CREATE INDEX "title_index" ON "shows" ("title");`

# interesting lecture queries

`SELECT * FROM shows WHERE title = "The Office" AND year = 2005;`

`SELECT DISTINCT(title) FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = "Comedy");`

`SELECT id FROM people WHERE name = "Steve Carell";`
`SELECT show_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Steve Carell");`
`SELECT title FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Steve Carell"));`
`SELECT title FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Steve Carell")) ORDER BY title;`
-> 0.94s, searching on name in people, and on person_id in stars (and id in shows) -> create index
`CREATE INDEX person_index ON stars (person_id)`
`CREATE INDEX show_index ON stars (show_id)`
`CREATE INDEX name_index ON people (name)`
-> 0.001s (no indexes on id fields)
-> same query with two JOINs:
`SELECT title FROM people JOIN stars ON people.id = stars.person_id JOIN shows ON stars.show_id = shows.id WHERE name = "Steve Carell";`
`SELECT title FROM people, stars, shows WHERE people.id = stars.person_id AND stars.show_id = shows.id AND name = "Steve Carell";`

# SQL CHEAT SHEET

## selectors

CREATE -> table
INSERT
SELECT
UPDATE
DELETE
DROP -> table

## functions

AVG
COUNT
DISTINCT
LOWER
MAX
MIN
UPPER

## filtering

WHERE
LIKE
ORDER BY
LIMIT
GROUP BY

# SELECT

## print all titles

`SELECT title FROM favorites;`

Breaking Bad
How i met your mother
Friday Night Lights
New Girl
The Office
The 100
The Office
Cobra Kai
New Girl
breaking bad
Avatar: something
Avatar
office

## print all titles and genres

`SELECT title, genres FROM favorites;`

Breaking Bad|Crime, Drama
How i met your mother|Comedy
Friday Night Lights|Drama, Family, Sport
New Girl|Comedy
The Office|Comedy
The 100|Action, Sci-Fi
The Office|Comedy
Cobra Kai|Action, Sport
New Girl|Comedy
breaking bad|Crime, Drama
Avatar: something|Crime, Drama
Avatar|Crime, Drama
office|Comedy

## print distinct (unique) titles

`SELECT DISTINCT(title) FROM favorites;`

Breaking Bad
How i met your mother
Friday Night Lights
New Girl
The Office
The 100
Cobra Kai
breaking bad
Avatar: something
Avatar
office

## print distinct (unique) titles and force them to uppercase

`SELECT DISTINCT(UPPER(title)) FROM favorites;`

BREAKING BAD
HOW I MET YOUR MOTHER
FRIDAY NIGHT LIGHTS
NEW GIRL
THE OFFICE
THE 100
COBRA KAI
AVATAR: SOMETHING
AVATAR
OFFICE

## count titles

`SELECT COUNT(title) FROM favorites;`

13

## get only 5 results

`SELECT title FROM favorites LIMIT 5;`

Breaking Bad
How i met your mother
Friday Night Lights
New Girl
The Office

## search for titles (ci/s = case insensitive/sensitive)

`SELECT title FROM favorites WHERE title LIKE "office";` -> exact, ci

office

`SELECT title FROM favorites WHERE title = "Office";` -> exact, cs

-

`SELECT title FROM favorites WHERE title LIKE "%office%";` -> pattern matching, ci

The Office
The Office
office

## search and count

`SELECT COUNT(title) FROM favorites WHERE title LIKE "%office%";`

3

# DELETE

## check how many titles with /new.girl/ there are and delete them

`SELECT COUNT(title) FROM favorites WHERE title LIKE "%new%girl%";`

2

`DELETE FROM favorites WHERE title LIKE "%new%girl%";`
`SELECT COUNT(title) FROM favorites WHERE title LIKE "%new%girl%";`

0

# UPDATE

## unify avatar titles: rename occurrences of /avatar.something/ to avatar

`SELECT title FROM favorites WHERE title LIKE "%avatar%";`

Avatar: something
Avatar

`UPDATE favorites SET title = "Avatar" WHERE title LIKE "%avatar%something%";`
`SELECT title FROM favorites WHERE title LIKE "%avatar%";`

Avatar
Avatar

## update all of avatar's genre entries to just "Crime"

`SELECT title, genres FROM favorites WHERE title LIKE "%avatar%";`

Avatar|Crime, Drama
Avatar|Crime, Drama

`UPDATE favorites SET genres = "Crime" WHERE title LIKE "%avatar%";`
`SELECT title, genres FROM favorites WHERE title LIKE "%avatar%";`

Avatar|Crime
Avatar|Crime

EXEC gen_countries;
EXEC gen_cities;
EXEC gen_relationships;
EXEC gen_localizations(200);
EXEC gen_events(200);
EXEC gen_contacts;
EXEC gen_people(500);
EXEC gen_companies;
EXEC gen_projects(1000);

SELECT * FROM countries;
SELECT * FROM cities;
SELECT * FROM relationships;
SELECT * FROM localizations;
SELECT * FROM events;
SELECT * FROM contacts;
SELECT * FROM people;
SELECT * FROM companies;
SELECT * FROM projects;
SELECT * FROM incomes;
SELECT * FROM expenses;
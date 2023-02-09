-- selects sum of all contacts in group of contacts
SELECT r.relationship_name, COUNT(p.relationship_id) AS number_of_people
FROM relationships r LEFT JOIN people p ON p.relationship_id = r.relationship_id
GROUP BY r.relationship_name ;
    

--prints id of projects which sum of incomes is >5000
SELECT project_id
FROM incomes
GROUP BY project_id
HAVING SUM(income)>5000;

-- same as above but with project_name
SELECT p.project_name, SUM(i.income)
FROM projects p LEFT JOIN incomes i ON p.project_id = i.project_id
GROUP BY p.project_name
HAVING SUM(i.income)>5000;


-- selects projects names, company_name and income
--for those projects thanks to which we earned more than 5000
--sorted in descending way
SELECT c.company_name, p.project_name, i.income
FROM companies c, projects p, incomes i
WHERE c.company_id = p.company_principal_id
    AND p.project_id = i.project_id
    AND i.income > 5000
ORDER BY i.income DESC;

-- selects how much money we earned thanks to which company
SELECT c.company_name, SUM(i.income)
FROM companies c, projects p, incomes i
WHERE c.company_id = p.company_principal_id
    AND p.project_id = i.project_id
GROUP BY c.company_name
ORDER BY SUM(i.income) ASC;

--SELECTS PEOPLE FROM FAMILY WHO WERE BORN AFTER FIRST FANUARY OF 2000
SELECT p.first_name, p.last_name, p.birthdate
FROM people p LEFT JOIN relationships r ON p.relationship_id = r.relationship_id
WHERE p.relationship_id = r.relationship_id
    AND r.relationship_name = 'Family'
    AND p.birthdate > TO_DATE('2000/01/01', 'YYYY/MM/DD');
    
--selects all events that that place in Poland
SELECT e.event_name, e.event_date, l.city
FROM events e, localizations l, countries co, cities ci
WHERE e.localization_id = l.localization_id
    AND l.city = ci.city
    AND ci.country = co.country
    AND co.country = 'Poland';



--select projects that are not finished and their deadline has passed
SELECT c.company_name, p.project_name, p.deadline
FROM projects p, companies c
WHERE p.deadline < CURRENT_DATE
    AND p.company_principal_id = c.company_id
    AND p.is_finished = 0;
    




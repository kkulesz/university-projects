EXECUTE DBMS_STATS.GATHER_TABLE_STATS('kkulesza', 'people');
EXECUTE DBMS_STATS.GATHER_TABLE_STATS('kkulesza', 'contacts');
EXECUTE DBMS_STATS.GATHER_TABLE_STATS('kkulesza', 'companies');
EXECUTE DBMS_STATS.GATHER_TABLE_STATS('kkulesza', 'projects');
EXECUTE DBMS_STATS.GATHER_TABLE_STATS('kkulesza', 'incomes');


CREATE INDEX people_fullname_idx ON people(first_name, last_name);
CREATE INDEX people_lastname_idx ON people(last_name);

CREATE INDEX projects_index ON projects(project_name, deadline ,remuneration);

CREATE INDEX comapnies_idx ON companies(company_name, contact_id);
CREATE INDEX contacts_idx ON contacts(contact_id, telephone_number);





ALTER INDEX people_fullname_idx VISIBLE;
ALTER INDEX people_lastname_idx VISIBLE;


--jedna kolumna i wyznaczamy tylko kolumne indeksowana
--index range scan | people_LASTname_idx
EXPLAIN PLAN FOR
SELECT last_name FROM people 
WHERE last_name LIKE 'D%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--jedna kolumna i wyznaczamy wszystko
--table access full
EXPLAIN PLAN FOR
SELECT * FROM people 
WHERE last_name LIKE 'D%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);



--dwie kolumny
--index range scan | people_FULLname_idx
EXPLAIN PLAN FOR
SELECT first_name, last_name, birthdate FROM people 
WHERE first_name LIKE 'K%' AND last_name LIKE 'K%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);



--identyczne zapytanie jak poprzednie, ale indexujemy tylko jedna kolumne w klauzluli WHERE
--table access full
ALTER INDEX people_fullname_idx INVISIBLE;
ALTER INDEX people_lastname_idx VISIBLE;

EXPLAIN PLAN FOR
SELECT first_name, last_name, birthdate FROM people 
WHERE first_name LIKE 'K%' AND last_name LIKE 'K%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);



--indexujemy dwie kolumny, ale wyszukujemy dodatkowo po jeszcze innym parametrze
--table access by index rowid
--index range scan | people_FULLname_idx
ALTER INDEX people_fullname_idx VISIBLE;
ALTER INDEX people_lastname_idx VISIBLE;

EXPLAIN PLAN FOR
SELECT first_name, last_name, birthdate FROM people 
WHERE first_name LIKE 'K%' AND last_name LIKE 'K%' AND birthdate > TO_DATE('2000/01/01', 'YYYY/MM/DD');
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);




/*
====================== index 3kolumnowy
*/




ALTER INDEX projects_index VISIBLE;


--uzywamy tylko jednej kolumny z indexu
-- wyszukujemy wzgl?dnie malo krotek
--index range scan
EXPLAIN PLAN FOR
SELECT project_name FROM projects 
WHERE project_name LIKE 'pr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);


--to samo co wyzej, ale wyszukujemy prawie wszystkie krotki
--table access full
EXPLAIN PLAN FOR
SELECT project_name FROM projects 
WHERE project_name NOT LIKE 'pr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--wypisujemy i wypisujemy dwie inexowane kolumny
--index range scan
EXPLAIN PLAN FOR
SELECT project_name, deadline FROM projects 
WHERE project_name LIKE 'pr%' AND DEADLINE > TO_DATE('2020/01/01', 'YYYY/MM/DD');
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);


--wypisujemy i wypisujemy wszsytkie inexowane kolumny
--index range scan
EXPLAIN PLAN FOR
SELECT project_name, deadline, remuneration FROM projects 
WHERE project_name LIKE 'pr%' AND DEADLINE > TO_DATE('2020/01/01', 'YYYY/MM/DD') AND remuneration > 1000;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--wypisujemy i wypisujemy wszsytkie inexowane kolumny PLUS wyszukujemy po dodatkowej kolumnie
--utable access by index rowid
--index range scan
EXPLAIN PLAN FOR
SELECT project_name, deadline, remuneration FROM projects 
WHERE project_name LIKE 'pr%' AND DEADLINE > TO_DATE('2020/01/01', 'YYYY/MM/DD') AND remuneration > 1000 AND is_finished = 0;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);


--wypisujemy wszystko we wzgl?dnie wielu krotkach
--table access full
EXPLAIN PLAN FOR
SELECT * FROM projects 
WHERE project_name NOT LIKE 'pr%' AND DEADLINE > TO_DATE('2020/01/01', 'YYYY/MM/DD') AND remuneration > 1000 AND is_finished = 0;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);





/*
============================================HINTY
*/

ALTER INDEX people_fullname_idx VISIBLE;
ALTER INDEX people_lastname_idx VISIBLE;
ALTER INDEX projects_index VISIBLE;
ALTER INDEX comapnies_idx VISIBLE;
ALTER INDEX contacts_idx VISIBLE;


--domyslnie jest 
--index range scan | people_LASTname_idx
EXPLAIN PLAN FOR
SELECT last_name FROM people 
WHERE last_name LIKE 'Kr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--table full scan
EXPLAIN PLAN FOR
SELECT /*+ FULL(people) */ last_name FROM people 
WHERE last_name LIKE 'Kr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--wymuszamy nie u?ywanie PEOPLE_LASTNAME_IDX
--index range scan | people_FULLname_idx
EXPLAIN PLAN FOR
SELECT /*+ no_index(people, people_lastname_idx) */ last_name FROM people 
WHERE last_name LIKE 'Kr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--wymuszamu uzywanie PEOPLE_FULLNAME_IDX
--index range scan | people_FULLname_idx
EXPLAIN PLAN FOR
SELECT /*+ index(people, people_fullname_idx) */ last_name FROM people 
WHERE last_name LIKE 'Kr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);





--DOMYSLE JEST HASH JOIN
EXPLAIN PLAN FOR
SELECT comp.company_name, cont.telephone_number
FROM companies comp, contacts cont
WHERE comp.contact_id = cont.contact_id
    AND comp.company_name LIKE 'G%'
    AND cont.contact_id BETWEEN 1 AND 10;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZENIE NA MERGE JOIN
EXPLAIN PLAN FOR
SELECT/*+ USE_MERGE(comp,cont) */ comp.company_name, cont.telephone_number
FROM companies comp, contacts cont
WHERE comp.contact_id = cont.contact_id
    AND comp.company_name LIKE 'G%'
    AND cont.contact_id BETWEEN 1 AND 10;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZENIE NA NESTED_LOOPS JOIN
EXPLAIN PLAN FOR
SELECT/*+ USE_NL(comp,cont) */ comp.company_name, cont.telephone_number
FROM companies comp, contacts cont
WHERE comp.contact_id = cont.contact_id
    AND comp.company_name LIKE 'G%'
    AND cont.contact_id BETWEEN 1 AND 10;
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);


--MERGE DOMYSLNIE
EXPLAIN PLAN FOR
SELECT p.project_name, i.income
FROM projects p LEFT JOIN incomes i ON p.project_id > i.project_id
WHERE p.project_id BETWEEN 1 AND 100
    AND p.project_name LIKE 'pr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZONE NA NESTED LOOPS
EXPLAIN PLAN FOR
SELECT/*+ USE_NL(p, i)*/ p.project_name, i.income
FROM projects p LEFT JOIN incomes i ON p.project_id > i.project_id
WHERE p.project_id BETWEEN 1 AND 100
    AND p.project_name LIKE 'pr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZONE NA HASH
EXPLAIN PLAN FOR
SELECT/*+ USE_HASH(p, i)*/ p.project_name, i.income
FROM projects p LEFT JOIN incomes i ON p.project_id > i.project_id
WHERE p.project_id BETWEEN 1 AND 100
    AND p.project_name LIKE 'pr%';
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);




--DOMYSLNIE JEST NESTE_LOOPS
EXPLAIN PLAN FOR
SELECT p.first_name, p.last_name, p.birthdate
FROM people p LEFT JOIN relationships r ON p.relationship_id = r.relationship_id
WHERE p.relationship_id = r.relationship_id
    AND r.relationship_name = 'Family'
    AND p.birthdate > TO_DATE('2000/01/01', 'YYYY/MM/DD');
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZENIE NA MERGE
EXPLAIN PLAN FOR
SELECT/*+ USE_MERGE(p,r)*/ p.first_name, p.last_name, p.birthdate
FROM people p LEFT JOIN relationships r ON p.relationship_id = r.relationship_id
WHERE p.relationship_id = r.relationship_id
    AND r.relationship_name = 'Family'
    AND p.birthdate > TO_DATE('2000/01/01', 'YYYY/MM/DD');
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);

--WYMUSZENIE NA HASH
EXPLAIN PLAN FOR
SELECT/*+ USE_HASH(p,r)*/ p.first_name, p.last_name, p.birthdate
FROM people p LEFT JOIN relationships r ON p.relationship_id = r.relationship_id
WHERE p.relationship_id = r.relationship_id
    AND r.relationship_name = 'Family'
    AND p.birthdate > TO_DATE('2000/01/01', 'YYYY/MM/DD');
SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);







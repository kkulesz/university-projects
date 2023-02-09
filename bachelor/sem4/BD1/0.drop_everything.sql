--sequences
DROP SEQUENCE loc_id_seq;
--DROP SEQUENCE event_group_id_seq;
DROP SEQUENCE event_id_seq;
DROP SEQUENCE contact_id_seq;
DROP SEQUENCE relationship_id_seq;
DROP SEQUENCE person_id_seq;
DROP SEQUENCE company_id_seq;
DROP SEQUENCE project_id_seq;
--DROP SEQUENCE task_id_seq;

--tables
DROP TABLE countries CASCADE CONSTRAINTS;
DROP TABLE cities CASCADE CONSTRAINTS;
DROP TABLE localizations CASCADE CONSTRAINTS;
--DROP TABLE event_groups CASCADE CONSTRAINTS;
DROP TABLE events CASCADE CONSTRAINTS;
DROP TABLE contacts CASCADE CONSTRAINTS;
DROP TABLE relationships CASCADE CONSTRAINTS;
DROP TABLE people CASCADE CONSTRAINTS;
DROP TABLE companies CASCADE CONSTRAINTS;
DROP TABLE projects CASCADE CONSTRAINTS;
--DROP TABLE tasks CASCADE CONSTRAINTS;
DROP TABLE incomes CASCADE CONSTRAINTS;
DROP TABLE expenses CASCADE CONSTRAINTS;


DROP PROCEDURE gen_countries;
DROP PROCEDURE gen_cities;
DROP PROCEDURE gen_relationships;
DROP PROCEDURE gen_localizations;
DROP PROCEDURE gen_events;
DROP PROCEDURE gen_contacts;
DROP PROCEDURE gen_people;
DROP PROCEDURE gen_companies;
DROP PROCEDURE gen_projects;

--triggers
/* no need to drop since DROP CASCADE?
DROP TRIGGER loc_trg;
DROP TRIGGER event_group_trg;
DROP TRIGGER event_trg;
DROP TRIGGER contact_trg;
DROP TRIGGER relationship_trg;
DROP TRIGGER person_trg;
DROP TRIGGER company_trg;
DROP TRIGGER project_id_trg;
DROP TRIGGER task_id_trg;
*/



--indexy
/*
DROP INDEX people_fullname_idx;
DROP INDEX people_lastname_idx;
DROP INDEX projects_index
*/
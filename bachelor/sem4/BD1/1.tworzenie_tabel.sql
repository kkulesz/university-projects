--=======================countries
CREATE TABLE countries(
country VARCHAR(40),
CONSTRAINT country_pk PRIMARY KEY (country)
);



--=======================cities
CREATE TABLE cities(
city VARCHAR(40) NOT NULL,
country VARCHAR(40) NOT NULL,
CONSTRAINT city_pk PRIMARY KEY (city),
CONSTRAINT country_fk FOREIGN KEY (country) REFERENCES countries(country)
);


--=======================localizations
CREATE SEQUENCE loc_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;

CREATE TABLE localizations(
localization_id NUMBER NOT NULL,
city VARCHAR(20) NOT NULL,
street VARCHAR(40) NOT NULL,
house_number NUMBER,

CONSTRAINT localization_pk PRIMARY KEY (localization_id),
CONSTRAINT localization_unique UNIQUE (city, street, house_number),
CONSTRAINT city_fk FOREIGN KEY (city) REFERENCES cities(city)
);


CREATE OR REPLACE TRIGGER loc_trg
BEFORE INSERT ON localizations
FOR EACH ROW
BEGIN
    SELECT loc_id_seq.NEXTVAL
    INTO :new.localization_id
    FROM dual;
END;
/


--========================event_group
/*
CREATE SEQUENCE event_group_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;


CREATE TABLE event_groups(
event_group_id NUMBER NOT NULL,
event_group_name VARCHAR(20) NOT NULL,

CONSTRAINT event_group_pk PRIMARY KEY (event_group_id),
CONSTRAINT event_group_unique UNIQUE (event_group_name)
);



CREATE OR REPLACE TRIGGER event_group_trg
BEFORE INSERT ON event_groups
FOR EACH ROW
BEGIN
    SELECT event_group_id_seq.NEXTVAL
    INTO :new.event_group_id
    FROM dual;
END;
/
*/
--======================EVENTS

CREATE SEQUENCE event_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;


CREATE TABLE events(
event_id NUMBER NOT NULL,
event_name VARCHAR(50) NOT NULL,
event_date DATE NOT NULL,
--event_group_id NUMBER NOT NULL,
localization_id NUMBER NOT NULL,

CONSTRAINT event_pk PRIMARY KEY (event_id),
CONSTRAINT event_unique UNIQUE (localization_id, event_name, event_date),

CONSTRAINT fk_event_localization 
FOREIGN KEY (localization_id) 
REFERENCES localizations(localization_id)
ON DELETE CASCADE
/*
CONSTRAINT fk_event_group 
FOREIGN KEY (event_group_id) 
REFERENCES event_groups(event_group_id)
ON DELETE CASCADE
*/
);


CREATE OR REPLACE TRIGGER event_trg
BEFORE INSERT ON events
FOR EACH ROW
BEGIN
    SELECT event_id_seq.NEXTVAL
    INTO :new.event_id
    FROM dual;
END;
/

--============================CONTACTS

CREATE SEQUENCE contact_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;


CREATE TABLE contacts(
contact_id NUMBER NOT NULL,
telephone_number VARCHAR(20) NOT NULL,
email VARCHAR(50) NOT NULL,
website VARCHAR(50),
facebook_link VARCHAR(50),

CONSTRAINT contact_pk               PRIMARY KEY (contact_id),
CONSTRAINT contact_telephone_unique UNIQUE (telephone_number),
CONSTRAINT contact_email_unique     UNIQUE (email),
CONSTRAINT contact_website_unique   UNIQUE (website),
CONSTRAINT contact_facebook_unique  UNIQUE (facebook_link)
);


CREATE OR REPLACE TRIGGER contact_trg
BEFORE INSERT ON contacts
FOR EACH ROW
BEGIN
    SELECT contact_id_seq.NEXTVAL
    INTO :new.contact_id
    FROM dual;
END;
/


--=================relationships

CREATE SEQUENCE relationship_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;



CREATE TABLE relationships(
relationship_id NUMBER NOT NULL,
relationship_name VARCHAR(20) NOT NULL,

CONSTRAINT relationship_pk PRIMARY KEY (relationship_id),
CONSTRAINT relationship_unique UNIQUE (relationship_name)
);


CREATE OR REPLACE TRIGGER relationship_trg
BEFORE INSERT ON relationships
FOR EACH ROW
BEGIN
    SELECT relationship_id_seq.NEXTVAL
    INTO :new.relationship_id
    FROM dual;
END;
/

--========================PEOPLE

CREATE SEQUENCE person_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;



CREATE TABLE people(
person_id NUMBER NOT NULL,
first_name VARCHAR(30) NOT NULL,
last_name VARCHAR(30) NOT NULL,
birthdate DATE,
contact_id NUMBER,
address_id NUMBER,
relationship_id NUMBER,

CONSTRAINT person_pk PRIMARY KEY (person_id),
CONSTRAINT person_contact_fk FOREIGN KEY (contact_id) REFERENCES contacts(contact_id) ON DELETE CASCADE,
CONSTRAINT person_address_fk FOREIGN KEY (address_id) REFERENCES localizations(localization_id) ON DELETE CASCADE,
CONSTRAINT relationship_fk FOREIGN KEY (relationship_id) REFERENCES relationships(relationship_id) ON DELETE CASCADE
);



CREATE OR REPLACE TRIGGER person_trg
BEFORE INSERT ON people
FOR EACH ROW
BEGIN
    SELECT person_id_seq.NEXTVAL
    INTO :new.person_id
    FROM dual;
END;
/



--companies
CREATE SEQUENCE company_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;

CREATE TABLE companies(
company_id NUMBER NOT NULL,
company_name VARCHAR(100) NOT NULL,
contact_id NUMBER NOT NULL,
localization_id NUMBER NOT NULL,

CONSTRAINT comapnies_pk PRIMARY KEY (company_id),
CONSTRAINT company_contact_fk FOREIGN KEY (contact_id) REFERENCES contacts(contact_id) ON DELETE CASCADE,
CONSTRAINT company_localization_fk FOREIGN KEY (localization_id) REFERENCES localizations(localization_id) ON DELETE CASCADE,
CONSTRAINT company_name_unique UNIQUE (company_name)
);

CREATE OR REPLACE TRIGGER company_trg
BEFORE INSERT ON companies
FOR EACH ROW
BEGIN
    SELECT company_id_seq.NEXTVAL
    INTO :new.company_id
    FROM dual;
END;
/


--projects
CREATE SEQUENCE project_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;

CREATE TABLE projects(
project_id NUMBER NOT NULL,
project_name VARCHAR(50) NOT NULL,
company_principal_id NUMBER NOT NULL,
deadline DATE NOT NULL,
remuneration NUMBER NOT NULL, --how much money we will get when project is finished
is_finished NUMBER(1,0) DEFAULT 0 NOT NULL,

CONSTRAINT project_pk PRIMARY KEY (project_id),
CONSTRAINT company_principal_fk FOREIGN KEY (company_principal_id) REFERENCES companies(company_id) ON DELETE CASCADE/*,
CONSTRAINT remuneration_not_negative CHECK (remuneration >= 0)*/
);

CREATE OR REPLACE TRIGGER project_id_trg
BEFORE INSERT ON projects
FOR EACH ROW
BEGIN
    SELECT project_id_seq.NEXTVAL
    INTO :new.project_id
    FROM dual;
END;
/



--incomes
CREATE TABLE incomes(
income NUMBER NOT NULL,
project_id NUMBER NOT NULL,

CONSTRAINT project_id_incomes_fk FOREIGN KEY (project_id) REFERENCES projects(project_id)
);

--expenses
CREATE TABLE expenses(
expense NUMBER NOT NULL,
project_id NUMBER NOT NULL,

CONSTRAINT project_id_expenses_fk FOREIGN KEY (project_id) REFERENCES projects(project_id)
);



--tasks
/*
CREATE SEQUENCE task_id_seq
START WITH 1
INCREMENT BY 1
NOCYCLE;

CREATE TABLE tasks(
task_id NUMBER NOT NULL,
task_name VARCHAR(20) NOT NULL,
is_started NUMBER(1, 0) DEFAULT 0 NOT NULL,
is_finished NUMBER(1,0) DEFAULT 0 NOT NULL,
expense NUMBER NOT NULL, --how much it will cost when the task is started
project_id NUMBER NOT NULL, -- which project the task is part of

CONSTRAINT task_pk PRIMARY KEY (task_id),
CONSTRAINT project_id_fk FOREIGN KEY (project_id) REFERENCES projects(project_id) ON DELETE CASCADE,
CONSTRAINT expense_not_negative CHECK (expense>0)
);


CREATE OR REPLACE TRIGGER task_id_trg
BEFORE INSERT ON tasks
FOR EACH ROW
BEGIN
    SELECT task_id_seq.NEXTVAL
    INTO :new.task_id
    FROM dual;
END;
/
*/













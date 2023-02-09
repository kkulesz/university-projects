CREATE OR REPLACE PROCEDURE gen_countries
IS
    TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    countries STRING_ARRAY;
    how_many NUMBER(5);
BEGIN
    countries := STRING_ARRAY ('Poland', 'England', 'France', 'Brazil', 'China', 'USA', 'Germany', 'Spain', 'Czech Republic');
    how_many := countries.COUNT;
    FOR i IN 1..how_many LOOP
        INSERT INTO countries VALUES ( countries(i) );
    END LOOP;
END;
/


--po trzy miasta do kazdego kraju
--before it there should be 'exec gen_countries'
CREATE OR REPLACE PROCEDURE gen_cities
IS
    TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    countries STRING_ARRAY;
    cities STRING_ARRAY;
    how_many NUMBER(5);
BEGIN
    countries := STRING_ARRAY ('Poland', 'England', 'France', 'Brazil', 'China', 'USA', 'Germany', 'Spain', 'Czech Republic');
    cities := STRING_ARRAY ('Warsaw', 'Cracov', 'Pozna?',
                            'Manchester', 'London', 'Liverpool',
                            'Paris', 'Lyon', 'Marseile',
                            'Brasilia', 'Sao Paulo', 'Rio de Janeiro',
                            'Wuhan', 'Pekin', 'Shanghai',
                            'New York', 'Los Angeles', 'Chicago',
                            'Munchen', 'Dortmund', 'Hamburg',
                            'Barcelona', 'Madrid', 'Valencia',
                            'Prague', 'Brno','Pilsen');
    how_many := countries.COUNT;
    <<outer_loop>>
    FOR i IN 1..how_many LOOP
        <<inner_loop>>
        FOR j IN 1..3 LOOP
            INSERT INTO cities(city, country) VALUES (cities(j+(i-1)*3), countries(i));
        END LOOP inner_loop;
    END LOOP outer_loop;
END;
/


CREATE OR REPLACE PROCEDURE gen_relationships
IS
    TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    relationships STRING_ARRAY;
    how_many NUMBER(5);
BEGIN
    relationships := STRING_ARRAY ('Family' , 'Friends', 'Work', 'Other');
    how_many := relationships.COUNT;
    FOR i IN 1..how_many LOOP
        INSERT INTO relationships(relationship_name) VALUES ( relationships(i) );
    END LOOP;
END;
/


--before it there should be 'exec gen_cities'
CREATE OR REPLACE PROCEDURE gen_localizations(how_many INTEGER)
IS
	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    cities STRING_ARRAY;
    streets STRING_ARRAY;
    house_number NUMBER(5);
    
    number_of_streets NUMBER(5);
    number_of_cities NUMBER(5);
    
    which_city VARCHAR2(250);
    which_street VARCHAR2(250);
    
    
BEGIN
        cities := STRING_ARRAY ('Warsaw', 'Cracov', 'Pozna?', 'Manchester', 'London', 'Liverpool', 'Paris', 'Lyon', 'Marseile', 'Brasilia', 'Sao Paulo', 'Rio de Janeiro', 'Wuhan', 'Pekin', 'Shanghai', 'New York', 'Los Angeles', 'Chicago', 'Munchen', 'Dortmund', 'Hamburg', 'Barcelona', 'Madrid', 'Valencia', 'Prague', 'Brno','Pilsen');
        streets := STRING_ARRAY ('Dluga', 'Mickiewicza', 'Lazienkowska', 'Pilsudskiego', 'Short', 'Long', 'Jana Pawla', 'Dmowskiego', 'Kochanowskiego');
        number_of_cities := cities.COUNT;
        number_of_streets := streets.COUNT;
    FOR i IN 1..how_many LOOP
        house_number := DBMS_RANDOM.VALUE(1, 500);
        which_city := DBMS_RANDOM.VALUE(1, number_of_cities);
        which_street := DBMS_RANDOM.VALUE(1, number_of_streets);
		INSERT INTO localizations(city, street, house_number) 
        VALUES (cities(which_city), streets(which_street), house_number);
            
	END LOOP;	
END;
/



CREATE OR REPLACE PROCEDURE gen_events(how_many INTEGER)
IS
	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    event_names STRING_ARRAY;
    number_of_event_names NUMBER(5);
    which_event_name NUMBER(5);
    year NUMBER(5);
    day NUMBER(3);
    event_date VARCHAR2(50);
    localization_id NUMBER(5);
    number_of_localizations NUMBER(5);    
BEGIN
    --number_of_localizations := SELECT COUNT(*) FROM localizations;
    event_names := STRING_ARRAY ('Film: Boze Cialo', 'Mecz: Legia-Jagielonia', 'Urodziny mamy', 'Imieniny tesciowej', 'Pogrzeb kota', 'Balet mocny', 'Spotkanie z szefem', 'Kolokwium z BD', 'Urodziny kota', 'Koncert Kazika', 'Koncert Dody', 'Obiad', 'Kolacja', 'Costam', 'Prezentacja z angielskiego', 'dzien matki', 'urodziny dziewczyny', 'film', 'mecz', 'spotkanie ze zajomymi', 'podelawanie kwaitow', 'zakupy dla kota', 'zakupy', 'remont', 'gotowanie', 'sprzatanie', 'lody', 'kupno plecaka', 'zabawa z kotem', 'krzeslo', 'budowa domu', 'posadzenie drzewa', 'splodzenie syna', 'burzenie domu', 'wyrwanie chwasta', 'koszenie trway', 'ognisko', 'zbieranie truskawek', 'nie wiem co jeszcze');
    number_of_event_names := event_names.COUNT;
    SELECT COUNT(*) INTO number_of_localizations FROM localizations;
    FOR i IN 1..how_many LOOP
        which_event_name := DBMS_RANDOM.VALUE(1,number_of_event_names);
        year := DBMS_RANDOM.VALUE(1999,2025);
        day := DBMS_RANDOM.VALUE(1,365);
        event_date := TO_CHAR(year) || TO_CHAR(day);
        localization_id := DBMS_RANDOM.VALUE( 1, number_of_localizations);
        INSERT INTO events(event_name, event_date, localization_id) VALUES ( event_names(which_event_name), TO_DATE(event_date,'yyyyddd'), localization_id);
    END LOOP;	
END;
/



CREATE OR REPLACE PROCEDURE gen_contacts
IS
	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    telephone NUMBER(10);
    emails STRING_ARRAY;
    websites STRING_ARRAY;
    facebook_links STRING_ARRAY;
    
    how_many NUMBER;
    
    
BEGIN
    emails := STRING_ARRAY('123@o2.pl', 'esssa@zxc.com', 'malpa@gmail.com', 'emailzkosmosu@protonmail.com', 'juzmisiekonczapomysly@wp.pl', 'gasa@adsads.sda', 'eldo@prezidento', 'uje@ow', 'malpa@malpa.pl', 'awolczeku@wp.pl', 'asdsadsal.ad.adsa', 'adas,asdpad.qw.qwe', 'niewiem', 'lgsldlsd' ,'asdsadas', 'vfddf', 'cosjeszcze');
    websites := STRING_ARRAY('www.asdsad.pl', 'www.internetwave.com', 'www.xd.pl', 'www.pilkanozna.pl', 'www.niewiem.nig', 'jakitest', 'lalalala', 'adsdadsa', 'urghrgs', 'teskieniezatokjo', 'zabrudnaantanariva', 'zajazdanastopapuustynia', 'ujarani.pl', 'demotywatory.pl', 'kontakt_do_kozaka.pl', 'xD/pl', 'asda.we', 'juzmisienieche.wp');
    facebook_links := STRING_ARRAY('www.facebook.pl/1','www.facebook.pl/2','www.facebook.pl/3','www.facebook.pl/4','www.facebook.pl/5','www.facebook.pl/6','www.facebook.pl/7','www.facebook.pl/8','www.facebook.pl/9','www.facebook.pl/10','www.facebook.pl/11','www.facebook.pl/12','www.facebook.pl/13','www.facebook.pl/14','www.facebook.pl/15','www.facebook.pl/16','www.facebook.pl/17','www.facebook.pl/18','www.facebook.pl/19','www.facebook.pl/20','www.facebook.pl/21','www.facebook.pl/2','www.facebook.pl/3','www.facebook.pl/4','www.facebook.pl/5','www.facebook.pl/6','www.facebook.pl/7','www.facebook.pl/8','www.facebook.pl/9','www.facebook.pl/10','www.facebook.pl/11','www.facebook.pl/12','www.facebook.pl/13','www.facebook.pl/14','www.facebook.pl/15','www.facebook.pl/16','www.facebook.pl/17');
    
    how_many := emails.COUNT;
    
    FOR i IN 1..how_many LOOP
        telephone := DBMS_RANDOM.VALUE(100000000, 999999999);
        INSERT INTO contacts(telephone_number, email, website, facebook_link) 
        VALUES ( TO_CHAR(telephone), emails(i), websites(i), facebook_links(i));
END LOOP;	
END;
/



CREATE OR REPLACE PROCEDURE gen_people(how_many INTEGER)
IS

	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    names STRING_ARRAY;
    surnames STRING_ARRAY;
    year NUMBER(10);
    day NUMBER(10);
    birthdate VARCHAR2(20);
    how_many_names NUMBER(10);
    how_many_surnames NUMBER(10);
    how_many_contacts NUMBER(10);
    how_many_localizations NUMBER(10);
    how_many_relationships NUMBER(10);
    which_name NUMBER(10);
    which_surname NUMBER(10);
    which_contact NUMBER(10);
    which_localization NUMBER(10);
    which_relationship NUMBER(10);
BEGIN
    names := STRING_ARRAY('Janek', 'Jakub', 'Quebo', 'Kazimierz', 'Kasia', 'Igor', 'Bartek', 'Bartlomiej', 'Bartosz', 'Szymon', 'Szymek', 'Rafal', 'Ania', 'Ola', 'Kinga', 'Lucja', 'Iza', 'Magda', 'Milena', 'Lala', 'Lena', 'Kacper', 'Damian', 'Daniel', 'Lukasz', 'Misiek', 'Smoku', 'Imie', 'Imiona', 'Weronika', 'Katarzyna', 'Jakub', 'Pawel', 'Marta', 'Natalia', 'Alicja', 'Krzeslo', 'Wincent', 'Wincenty', 'Slawek', 'Slawomir', 'Zdzisiek', 'Zbyszek', 'Eldo', 'Prezidento', 'Jaro', 'Jaroslaw', 'Kaziu', 'Folia', 'Foliarz', 'Karton', 'Dzesika', 'Natan', 'Oliwier', 'Oliver', 'Dawid', 'Wejn', 'Wejni', 'Wini', 'Widi', 'Wici');
    surnames := STRING_ARRAY('Nowak', 'Grabowski', 'Miasto', 'Lysy', 'Komor', 'Smiesze', 'Mieszko', 'Nazwisko', 'XDD', 'EsterEgg', 'Hehe', 'Eldo', 'Zaba', 'Yo', 'PODA_TO_FAJNY_PRZEDMIOT', 'SKM_TAK_SAMO', 'nazwisko', 'Grzejnik', 'Gumka', 'Mata', 'Wesolowska', 'Kazimierczak', 'Olber', 'Galat', 'Piornik', 'Kurnik', 'Kulus', 'Sielala', 'Wanna', 'Wanienka', 'Panienika', 'Olenka', 'Malenka', 'Ulenka', 'Karate', 'Kwiatek', 'Zlotymedal', 'Kremik', 'Ksiazeczka', 'Globus', 'Glabas', 'Domek', 'Farma', 'Mis', 'Zigzak', 'Prosiaczek', 'Klapouchy', 'Kondziczek', 'Dzik', 'Swieczka', 'Zoo', 'Pudelko', 'Szklo', 'puzzle', 'Album', 'Szafka', 'Drewno');
    
    how_many_names := names.COUNT;
    how_many_surnames := surnames.COUNT;
    SELECT COUNT(*) INTO how_many_contacts FROM contacts;
    SELECT COUNT(*) INTO how_many_localizations FROM localizations;
    SELECT COUNT(*) INTO how_many_relationships FROM relationships;
    FOR i IN 1..how_many LOOP
        year := DBMS_RANDOM.VALUE(1945,2010);
        day := DBMS_RANDOM.VALUE(1,365);
        birthdate := TO_CHAR(year) || TO_CHAR(day);
        which_name := DBMS_RANDOM.VALUE(1, how_many_names);
        which_surname := DBMS_RANDOM.VALUE(1, how_many_surnames);
        which_contact := DBMS_RANDOM.VALUE(1, how_many_contacts);
        which_localization := DBMS_RANDOM.VALUE(1, how_many_localizations);
        which_relationship := DBMS_RANDOM.VALUE(1, how_many_relationships);
        INSERT INTO PEOPLE(first_name, last_name, birthdate, contact_id, address_id, relationship_id) 
        VALUES( names(which_name), surnames(which_surname),TO_DATE(birthdate, 'yyyyddd'), which_contact,which_localization,which_relationship);
    END LOOP;	
END;
/


SET DEFINE OFF;

CREATE OR REPLACE PROCEDURE gen_companies
IS
	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    company_names STRING_ARRAY;
    how_many_contacts NUMBER(10);
    how_many_localizations NUMBER(10);
    which_contact NUMBER(10);
    which_localization NUMBER(10);
    
    how_many NUMBER;
BEGIN
--companies copied from jednatabelagenerator.sql
    company_names := STRING_ARRAY('Spolka zooooooo','UGI', 'AES', 'Telephone & Data Systems', 'Paccar', 'Philip Morris International', 'Avon Products', 'Parker Hannifin', 'Freeport-McMoRan Copper & Gold', 'Great Atlantic & Pacific Tea', 'General Motors', 'Staples', 'UnitedHealth Group', 'MetLife', 'National Oilwell Varco', 'NCR', 'Safeway', 'KBR', 'TravelCenters of America', 'Tesoro', 'Goodyear Tire & Rubber', 'Bemis', 'Time Warner Cable', 'HCA Holdings', 'J.M. Smucker', 'Owens & Minor', 'Owens-Illinois', 'Qwest Communications', 'Automatic Data Processing', 'Calpine', 'PNC Financial Services Group', 'J.P. Morgan Chase & Co.', 'NextEra Energy', 'Delta Air Lines', 'Avnet', 'First Data', 'Western Union', 'Chesapeake Energy', 'Best Buy', 'PG&E Corp.', 'Sonic Automotive', 'Qualcomm', 'International Business Machines', 'Universal Health Services', 'Ameren', 'General Electric', 'Texas Instruments', 'NII Holdings', 'Merck', 'Travelers Cos.', 'Community Health Systems', 'Entergy', 'WellPoint', 'Phillips-Van Heusen', 'Whole Foods Market', 'Autoliv', 'Thermo Fisher Scientific', 'Avery Dennison', 'Dr Pepper Snapple Group', 'Plains All American Pipeline', 'Aramark', 'Universal American', 'Virgin Media', 'Loews', 'Union Pacific', 'McGraw-Hill', 'Dover', 'Amazon.com', 'Reinsurance Group of America', 'Mattel', 'ITT', 'Comcast', 'Nike', 'General Cable', 'Enterprise Products Partners', 'Office Depot', 'Dollar General', 'Apple', 'Expeditors International of Washington', 'Micron Technology', 'Bank of New York Mellon Corp.', 'Alcoa', 'Applied Materials', 'BB&T Corp.', 'Williams', 'Aflac', 'Procter & Gamble', 'Harris', 'Citigroup', 'CB Richard Ellis Group', 'New York Life Insurance', 'EMC', 'Gannett', 'PPL', 'Tech Data', 'Verizon Communications', 'Costco Wholesale', 'Jabil Circuit', 'Broadcom', 'Home Depot', 'Starwood Hotels & Resorts', 'Cisco Systems', 'Progress Energy', 'Northrop Grumman', 'Corning', 'Unum Group', 'AutoZone', 'Icahn Enterprises', 'Dell', 'Prudential Financial', 'Kimberly-Clark', 'Public Service Enterprise Group', 'Henry Schein', 'Arrow Electronics', 'Host Hotels & Resorts', 'General Mills', 'Ryder System', 'Kellogg', 'Ashland', 'PetSmart', 'CenterPoint Energy', 'SAIC', 'OfficeMax', 'Mohawk Industries', 'Masco', 'Wal-Mart Stores', 'Express Scripts', 'Stryker', 'Xcel Energy', 'BJ''s Wholesale Club', 'FirstEnergy', 'Supervalu', 'Ball', 'Newmont Mining', 'Pitney Bowes', 'Eaton', 'Apollo Group', 'St. Jude Medical', 'Oneok', 'Nucor', 'Cameron International', 'Amgen', 'SPX', 'United Services Automobile Assn.', 'INTL FCStone', 'Regions Financial', 'Avaya', 'Southwest Airlines', 'State Farm Insurance Cos.', 'Omnicare', 'KeyCorp');
    SELECT COUNT(*) INTO how_many_contacts FROM contacts;
    SELECT COUNT(*) INTO how_many_localizations FROM localizations;    
    
    how_many := company_names.COUNT;
    FOR i IN 1..how_many LOOP
        which_contact := DBMS_RANDOM.VALUE(1, how_many_contacts);
        which_localization := DBMS_RANDOM.VALUE(1, how_many_localizations);
        
        INSERT INTO companies(company_name, contact_id, localization_id) 
        VALUES( company_names(i), which_contact, which_localization);
    END LOOP;	
END;
/

CREATE OR REPLACE PROCEDURE gen_projects(how_many INTEGER)
IS
	TYPE STRING_ARRAY IS TABLE OF VARCHAR2(250);
    project_names STRING_ARRAY;
    how_many_companies NUMBER(10);
    which_company NUMBER(10);
    year NUMBER(4);
    day NUMBER(3);
    deadline VARCHAR2(10);
    is_finished NUMBER(1);
    remuneration NUMBER(10);
    which_project NUMBER(10);
    how_many_projects NUMBER(10);
    --how_many NUMBER;
BEGIN
    project_names := STRING_ARRAY('eldo', 'koszenie trawy', 'strona dla Huawei', 'Komunikator projekt', 'jakisstring', 'okej', 'ciekawy projekt', 'napisac donos na kolegow', 'ulozyc puzzle', 'przeczytac ksiazke', 'bazgrac', 'jezdzic samochodem', 'ulozyc pociag', 'bawic sie z koniem', 'posprzatac po kotku', 'posadzic kwiaty', 'podlac baklazana', 'przesadzic baklazana', 'wyrzucic baklazana', 'ubrac sie', 'wstac', 'rozpakowac prezenty', 'obejrzec album', 'nagrac piosenke na h16ch2', 'zrobic playliste', 'nie wiem co jeszcze');
    SELECT COUNT(*) INTO how_many_companies FROM companies;
    
    how_many_projects := project_names.COUNT;
    FOR i IN 1..how_many LOOP
        which_company := DBMS_RANDOM.VALUE(1,how_many_companies);
        which_project := DBMS_RANDOM.VALUE(1,how_many_projects);
        year := DBMS_RANDOM.VALUE(2010, 2025);
        day := DBMS_RANDOM.VALUE(1, 365);
        deadline := TO_CHAR(year) || TO_CHAR(day);
        is_finished := DBMS_RANDOM.VALUE(0, 1);
        remuneration := DBMS_RANDOM.VALUE(1000, 20000);
        INSERT INTO projects(project_name, company_principal_id, deadline, remuneration, is_finished)
        VALUES(project_names(which_project), which_company, TO_DATE(deadline, 'yyyyddd'),remuneration, is_finished);
    END LOOP;	
END;
/
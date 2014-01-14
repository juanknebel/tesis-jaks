USE tesis;
#Creo un campo más donde contiene el costo del paper que será siempre 1
ALTER TABLE ARTICLES 
ADD COLUMN Cost DOUBLE NOT NULL DEFAULT 1 AFTER topicProfile_identifier;

#Creo la tabla de similaridad
CREATE TABLE SIMILARITY (
  Item INT NOT NULL,
  Item2 INT NOT NULL,
  Similarity FLOAT NOT NULL,
  PRIMARY KEY (Item, Item2));

#Creo la tabla donde hago el mapeo del id de los articulos con uno secuencial
CREATE TABLE ARTICLE_ITEM (
  Item INT NOT NULL,
  ArticleId INT NOT NULL,
  PRIMARY KEY (Item));

#Procedimiento que completa la tabla para tener ids consecutivos
DROP procedure IF EXISTS fillARTICLE_ITEM;

DELIMITER $$
CREATE PROCEDURE fillARTICLE_ITEM ()
BEGIN
DECLARE done INT DEFAULT 0;
DECLARE article_id INT;
DECLARE item INT;
DECLARE cursor_i CURSOR FOR SELECT ArticleId FROM ARTICLES;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

SET SQL_SAFE_UPDATES=0;
DELETE FROM ARTICLE_ITEM;
set item = 0;
OPEN cursor_i;
	read_loop: 
	LOOP FETCH cursor_i INTO article_id;
		IF done = 1 THEN
			LEAVE read_loop;
		END IF;
		INSERT INTO ARTICLE_ITEM values(item, article_id);
		set item = item + 1;
	END LOOP;
CLOSE cursor_i;
SET SQL_SAFE_UPDATES=1;
END$$

DELIMITER ;
CALL fillARTICLE_ITEM();

#--------Para hacer test---------------#
USE test;
DROP TABLE ARTICLES;
CREATE TABLE ARTICLES (
  ArticleId bigint(20) NOT NULL AUTO_INCREMENT,
  DOI varchar(255) DEFAULT NULL,
  articleAbstract longtext,
  digitalLibraryLink varchar(255) DEFAULT NULL,
  title varchar(255) DEFAULT NULL,
  year int(11) NOT NULL,
  fullTextPDF_identifier bigint(20) DEFAULT NULL,
  venue_VenueId bigint(20) DEFAULT NULL,
  topicProfile_identifier bigint(20) DEFAULT NULL,
  Cost double NOT NULL DEFAULT '1',
  PRIMARY KEY (ArticleId));

DROP TABLE TopicProfile_distribution;
CREATE TABLE TopicProfile_distribution (
  TopicProfile_identifier bigint(20) NOT NULL,
  distribution double DEFAULT NULL,
  distribution_KEY varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (TopicProfile_identifier,distribution_KEY));
  
DROP TABLE SIMILARITY;
CREATE TABLE SIMILARITY (
  Item INT NOT NULL,
  Item2 INT NOT NULL,
  Similarity FLOAT NOT NULL,
  PRIMARY KEY (Item, Item2));

DROP TABLE ARTICLE_ITEM;
CREATE TABLE ARTICLE_ITEM (
  Item INT NOT NULL,
  ArticleId INT NOT NULL,
  PRIMARY KEY (Item));

DROP procedure IF EXISTS fillARTICLE_ITEM;

DELIMITER $$
CREATE PROCEDURE fillARTICLE_ITEM ()
BEGIN
DECLARE done INT DEFAULT 0;
DECLARE article_id INT;
DECLARE item INT;
DECLARE cursor_i CURSOR FOR SELECT ArticleId FROM ARTICLES;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

SET SQL_SAFE_UPDATES=0;
DELETE FROM ARTICLE_ITEM;
set item = 0;
OPEN cursor_i;
	read_loop: 
	LOOP FETCH cursor_i INTO article_id;
		IF done = 1 THEN
			LEAVE read_loop;
		END IF;
		INSERT INTO ARTICLE_ITEM values(item, article_id);
		set item = item + 1;
	END LOOP;
CLOSE cursor_i;
SET SQL_SAFE_UPDATES=1;
END$$

DELIMITER ;
CALL test.fillARTICLE_ITEM();

SET SQL_SAFE_UPDATES=0;
delete from test.ARTICLES;
delete from test.TopicProfile_distribution;
delete from test.SIMILARITY;
delete from test.ARTICLE_ITEM;
SET SQL_SAFE_UPDATES=1;

insert into test.ARTICLES SELECT *
FROM tesis.ARTICLES where topicProfile_identifier is not null and venue_VenueId=1 limit 0,70;
insert into test.ARTICLES SELECT *
FROM tesis.ARTICLES where topicProfile_identifier is not null and venue_VenueId=2 limit 0,70;
insert into test.ARTICLES SELECT *
FROM tesis.ARTICLES where topicProfile_identifier is not null and venue_VenueId=3 limit 0,70;
insert into test.ARTICLES SELECT *
FROM tesis.ARTICLES where topicProfile_identifier is not null and venue_VenueId=4 limit 0,70;
insert into test.ARTICLES SELECT *
FROM tesis.ARTICLES where topicProfile_identifier is not null and venue_VenueId=5 limit 0,70;

insert into test.TopicProfile_distribution (select * from tesis.TopicProfile_distribution 
where topicProfile_identifier in (
SELECT topicProfile_identifier FROM test.ARTICLES
));

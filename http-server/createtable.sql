

CREATE TABLE baidu 
(ID int NOT NULL auto_increment,
url varchar(100), 
name varchar(100),
description varchar(200),
PRIMARY KEY (ID));

CREATE UNIQUE INDEX baidu_id
ON baidu (ID);

CREATE INDEX baidu_name
ON baidu (name);



drop database if exists hierarchy;
create database hierarchy;


use hierarchy

create table contenttype
(
  ID int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  Name varchar(20)
);

create table tree
( ID int NOT NULL AUTO_INCREMENT, 
  TagName varchar(20),
  ParentID int,
  ContentType int,
  ContentID int,
  PRIMARY KEY(ID),
  FOREIGN KEY (ParentID) REFERENCES tree(ID),
  FOREIGN KEY (ContentID) REFERENCES contenttype(ID)
);

create table contenthierarchy
( ContentID int NOT NULL AUTO_INCREMENT Primary Key,
  ShortDescription varchar(40),
  Description varchar(100)
);
  

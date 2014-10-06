
drop database if exists hierarchy;
create database hierarchy;

use hierarchy;

create table contenttype
(
  ID int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  Name varchar(20),
  TableName varchar(40)
);

create table tree
( ID int NOT NULL AUTO_INCREMENT, 
  TagName varchar(80),
  TreeID int,
  ParentID int,
  #leftNode int,
  #rightNode int,
  ContentType int,
  ContentID int,
  PRIMARY KEY(ID),
  FOREIGN KEY (TreeID) REFERENCES tree(ID),
  FOREIGN KEY (ContentType) REFERENCES contenttype(ID)
);

create table contenthierarchy
( ContentID int NOT NULL AUTO_INCREMENT Primary Key,
  ShortDescription varchar(40),
  Description varchar(200)
);

create table tvshow
( ContentID int NOT NULL AUTO_INCREMENT Primary Key,
  ShortDescription varchar(40),
  Description varchar(100)
);

create table actor
( ContentID int NOT NULL AUTO_INCREMENT Primary Key,
  ShortDescription varchar(40),
  FirstName varchar(40),
  LastName varchar(40),
  Description varchar(100)
);

create table country
( ContentID int NOT NULL AUTO_INCREMENT Primary Key,
  Name varchar(40),
  Description varchar(100)
);
  

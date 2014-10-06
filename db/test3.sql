use hierarchy;

INSERT INTO contenthierarchy
  (ShortDescription, Description)
  VALUES
  ('All Hierarchies','A content hierarchy of all hierarchies'),
  ('All Shows','A content hierarchy of all TV Shows');


INSERT INTO tree
 (TagName, TreeID, ParentID, ContentType, ContentID)
 VALUES
 ('ALL', 4,  NULL,  1, 4),
 ('CREF', 4,    15, 5, 7),
 ('SREF', 4,    15, 5, 1),
 ('DREF', 4,    15, 5, 2),
 ('ATV' , 5,  NULL, 1, 5);

INSERT INTO tree
 (TagName, TreeID, ParentID, ContentType, ContentID)
 SELECT CONCAT('T', ID), 5, 19, 5, ID from tree where ContentType = 2
 
 
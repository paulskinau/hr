use hierarchy;

INSERT INTO contenthierarchy
  (ShortDescription, Description)
  VALUES
  ('Recursive Tree','A recursive tree');


INSERT INTO tree
 (TagName, TreeID, ParentID, ContentType, ContentID)
 VALUES
 ('REC', 5,   NULL, 1, 6),
 ('BBT', 5,     35, 2, 5),
 ('JG',  3,     36, 3, 1),
 ('SD',  5,     36, 3, 2),
 ('ROS', 5,     37, 2, 9),
 ('JG',  5,     38, 5, 36);

 
use hierarchy

DELETE FROM contenthierarchy;
ALTER TABLE contenthierarchy AUTO_INCREMENT = 1;
DELETE FROM tree;


INSERT INTO contenthierarchy
  (ShortDescription, Description)
  VALUES
  ('Science Fiction Shows','A content hierarchy of science fiction shows'),
  ('Documentary Shows', 'A content hierarchy of documentary shows');


INSERT INTO tree
 (TagName, ParentID, ContentType, ContentID)
 VALUES
 ('Scifi', NULL, 1, 1),
 ('Doco', NULL, 1,2);

use hierarchy;

DELETE FROM contenthierarchy;
ALTER TABLE contenthierarchy AUTO_INCREMENT = 1;
UPDATE tree set TreeID = null;
TRUNCATE tree;

INSERT INTO contenthierarchy
  (ShortDescription, Description)
  VALUES
  ('Science Fiction Shows','A content hierarchy of science fiction shows'),
  ('Documentary Shows', 'A content hierarchy of documentary shows');


truncate tvshow;
INSERT into tvshow
 (ShortDescription, Description)
  VALUES
  ('Game of Thrones', 'Seven noble families fight for control of the mythical land of Westeros.'),
  ('Planet Earth', 'Emmy Award winning, 11-episodes, 5-years in the making, the most expensive nature documentary series ever commissioned by the BBC, and the first to be filmed in high definition.'),
  ('Last Man on Earth', 'The survival of the human race depends on two strangers forced to come together despite their differences.'),
  ('Mythbusters', 'A weekly documentary in which two Hollywood special effects experts attempt to debunk urban legends by directly testing them.');

INSERT INTO tree
 (TagName, TreeID, ParentID, ContentType, ContentID)
 VALUES
 ('Scifi', 1, NULL, 1, 1),
 ('Doco', 2, NULL, 1,2),
 ('GOT', 1, 1, 2, 1 ),
 ('PE', 2, 2, 2,2),
 ('LME', 1,1, 2,3),
 ('MYT', 2, 2, 2,4);
 
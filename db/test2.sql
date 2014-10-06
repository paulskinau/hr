use hierarchy;

INSERT INTO contenthierarchy
  (ShortDescription, Description)
  VALUES
  ('Comedy Shows','A content hierarchy of comedy shows');

INSERT into tvshow
 (ShortDescription, Description)
  VALUES
  ('The Big Bang Theory', 'A woman who moves into an apartment across the hall from two brilliant but socially awkward physicists shows them how little they know about life outside of the laboratory.'),
  ('Orange Is the New Black', 'The story of Piper Chapman, a woman in her thirties who is sentenced to fifteen months in prison after being convicted of a decade-old crime of transporting money for her drug-dealing girlfriend.'),
  ('Modern Family', 'Three different, but related families face trials and tribulations in their own uniquely comedic ways.'),
  ('New Girl', 'After a bad break-up, Jess, an offbeat young woman, moves into an apartment loft with three single men. Although they find her behavior very unusual, the men support her - most of the time.'),
  ('Rosanne', 'Roseanne is an American sitcom that was broadcast on ABC from October 18, 1988, to May 20, 1997.');

truncate actor;
INSERT into actor
 ( FullName, ShortDescription, Description)
 VALUES
 ('Johnny Galecki', 'Johnny Galecki', 'Plays Lenard on the Big Bang Theory'),
 ('Jim Parsons', 'Jim Parsons','Most famous for playing Sheldon on BBT');

INSERT INTO tree
 (TagName, TreeID, ParentID, ContentType, ContentID)
 VALUES
 ('Com', 3,  NULL, 1, 3),
 ('BBT', 3,     7, 2, 5),
 ('OINB',3,     7, 2, 6),
 ('MF',  3,     7, 2, 7),
 ('NG',  3,     7, 2, 8),
 ('JG',  3,     8, 3, 1),
 ('SD',  3,     8, 3, 2),
 ('ROS', 3,     12,2, 9);

 
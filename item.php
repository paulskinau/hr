<?php require("header.inc"); ?>

<body>


<div data-role="page" id="home">

<?php require("menu.inc"); ?>

  <div data-role="header">
    <h1>Content Hierarchy</h1>
  </div>

 <?php require("db/db.inc"); ?> <?php include("bl/tree.inc"); ?>

  <div data-role="main" class="ui-content">

   <?php

    $id = 14;
    if (array_key_exists("id", $_GET))
	{ $id = $_GET["id"]; }

    $tree = new Tree(new HierarchyNode($id));

    printf("<h2>%s</h2>", $tree->rootNode->value);


    printf($tree->rootNode->toHTMLString());

    printf("<p>As Short String:<br/>%s</p>", $tree->rootNode->toShortString());

    #loadTree(1);

    $mysqli->close();
   ?>     

  <a href="list.php" data-transition="slide">Back</a>
    
  </div>

  

  <div data-role="footer">
    <h1>Copyright Paul Skinner</h1>
  </div>

</div>

</body>

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
   

   if ($stmt = $mysqli->prepare("SELECT ShortDescription from contenthierarchy where ContentID=?"))
   {
	$stmt->bind_param("s", $_GET["id"]);
	$stmt->execute();
	$stmt->bind_result($desc);
	$stmt->fetch();
	printf("<h2>%s</h2>", $desc);
        $stmt->close();
   }	

    $tree = new Tree(new Node($_GET["id"]));



    loadTree($_GET["id"]);

    $mysqli->close();
   ?>     

    
  </div>

  

  <div data-role="footer">
    <h1>Copyright Paul Skinner</h1>
  </div>

</div>

</body>

<?php require("header.inc"); ?>

<body>


<div data-role="page" id="home">

<?php require("menu.inc"); ?>

  <div data-role="header">
    <h1>List Content Hierarchies</h1>
  </div>

 <?php require("db/db.inc"); ?>

  <div data-role="main" class="ui-content">

     <ul class="ui-listview ui-listview-inset ui-corner-all ui-shadow" data-role="listview" data-inset="true">
	<?php
	  $firstlastchild = 'ui-first-child';
	  $query = 'SELECT ShortDescription, Description FROM contenthierarchy';
	  $result = mysql_query($query) or die('Query failed: ' . mysql_error());	
	  	
	  while ($line = mysql_fetch_array($result, MYSQL_NUM)) {
	  ?>
		<li class="ui-li-static ui-body-inherit ui-first-child">
	  <?php printf("<h3> %s </h3><p> %s </p>", $line[0], $line[1]); ?>         
                 </li>		
	<?php 
		 }
	  
           ?>
                </ul>    

    
  </div>

  

  <div data-role="footer">
    <h1>Copyright Paul Skinner</h1>
  </div>

</div>

</body>

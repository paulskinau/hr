<?php

$db_servername = "localhost";
$db_username = "root";
$db_password = "switch";

$mysqli = newConn();

/* check connection */
if (mysqli_connect_errno()) {
    $err = sprintf("Connect failed: %s\n", mysqli_connect_error());
    die($err);
}

function newConn()
{ global $db_servername;
  global $db_username;
  global $db_password;
  return new mysqli($db_servername, $db_username, $db_password, 'hierarchy');

}

function getContentTypeTableName($contenttype)
{
   switch ($contenttype)
    {
	case 1:
	  $tn = "contenthierarchy";
	  break;	
	case 2:
	  $tn = "tvshow";
	  break;
        case 3: 
	  $tn = "actor";
	  break;
	case 4:
	  $tn = "country";
	  break;
     }
  return $tn;
}

?>

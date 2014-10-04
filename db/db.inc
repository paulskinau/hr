<?php

$db_servername = "localhost";
$db_username = "root";
$db_password = "switch";


$connect = mysql_connect($db_servername, $db_username, $db_password)
	or die ( 'Unable to connect to mysql server');

mysql_select_db('hierarchy') or die('Could not select database');

?>

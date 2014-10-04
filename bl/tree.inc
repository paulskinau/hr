<?php

#include("../db/db.inc");

class Node
{
  public $leftNode;
  public $rightNodes = array();
  public $value;

  public function __construct($value)
  {
	$this->value = $value;
  }
}

class Tree
{
   public $rootNode;

  public function __construct($value)
  {
	$this->rootNode = $value;
  }

   public function add($newnode, $parent)
   {
   	$newnode->left = $parent;
        if (!in_array($newnode, $parent->right))
        {
	   push_array($newnode, $parent->right);	
        }
   }
}

function loadTree($id)
{
   global $mysqli;

   #if (!is_int($id)) { $id = 1; } 

   if ($stmt = $mysqli->prepare("SELECT leftNode, rightNode, ID as treeID from tree where ContentID=?"))
   {
	$stmt->bind_param("i", $id);
	$stmt->execute();
	$stmt->bind_result($leftNode, $rightNode, $treeID);
	$stmt->fetch();
	$stmt->close();
   }	

   if ($stmt = $mysqli->prepare("SELECT ContentID, ContentType, leftNode, rightNode from tree where TreeID = ? and leftNode >= ? and leftNode <= ? order by leftNode ASC"))
   {

	$stmt->bind_param("iii", $id, $leftNode, $rightNode);
	$stmt->execute();
	$stmt->bind_result($contentid, $contenttype,$ln,$rn);

	$right = array();

	  /* fetch values */
  	while ($stmt->fetch()) {
        #printf ("<p>%s - %s (%s - %s)</p>", $contentid, $contenttype, $ln, $rn);

	if (count($right) > 0)
        {
		while ($right[count($right)-1] < $rn) {
	
		 array_pop($right);

		}
 	}

	echo "<p>" . str_repeat('&nbsp;&nbsp;',count($right)) . '' . $contenttype . '-' . $contentid. ' -> '.ToString($contentid, $contenttype). '</p>';
	#echo 'adding ' . $rn;
	$right[] = $rn;
    	}

    	/* free result set */
   	 $stmt->close();
   
   }
 
}

function ToString($contentid, $contenttype)
{ 
    $mysqli = newConn();

   $tn = getContentTypeTableName($contenttype);


    $sql = sprintf("SELECT ShortDescription FROM %s where ContentID = ?", $tn);
		
   if ($stmt = $mysqli->prepare($sql))
   {
	$stmt->bind_param("i",$contentid);
	$stmt->execute();
	$stmt->bind_result($ShortDescription);
	$stmt->fetch();
	$stmt->close();
	return $ShortDescription;
   }	
   else
	{ echo 'failed'; }		
}

?>



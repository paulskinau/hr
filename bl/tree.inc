<?php

#include("../db/db.inc");

class ActorNode extends Node
{
}

class HierarchyNode extends Node
{
}

class TVShowNode extends Node
{
}

class ReferenceNode extends Node
{
	public $refid;

	public function __construct($id)
	{
		$refid = $id;

		$mysqli = newConn();

		if ($stmt = $mysqli->prepare("SELECT contentid from tree where ID=?"))
        	{	

			$stmt->bind_param("i", $refid);
			$stmt->execute();
			$stmt->bind_result($newid);
	
			$stmt->fetch();

			$stmt->close();
	
       		}

		$mysqli->close();

		parent::__construct($newid);
	}
}

class Node
{
  public $parentNode;
  public $childNodes = array();
  public $value;
  public $id;
  public $contentid;
  public $contenttype;
  public $allSubordinates;
  public $rootNode;

  public function __construct($id, $value = NULL, $contenttype = null, $contentid = null)
  {

	$this->id = $id;
	if ($value == null || $contenttype == null || $contentid == null )
	{

		$this->load();
	}
	else
	{
		$this->value = $value;
		$this->contenttype = $contenttype;
		$this->contentid = $contentid;
	}

	$this->loadChildren();
	
  }


  public static function fromContentType($id, $value, $contenttype, $contentid)
  {
 	    switch ($contenttype)
	    {
		case 1:
			return new HierarchyNode( $id,$value, $contenttype, $contentid);
		case 2:
			return new TVShowNode($id, $value, $contenttype, $contentid);
		case 3:
			return new Actornode($id, $value, $contenttype, $contentid);		
		case 5:
			return new ReferenceNode($id); 
	    }
	
  }

  private static function getDescription($contentid, $contenttype)
  { 
	#echo "getDescription - " . $contentid . " - " . $contenttype . "!!! </br>";

    $mysqli = newConn();

    $tn = getContentTypeTableName($contenttype);
 

    $sql = sprintf("SELECT ShortDescription FROM %s where ContentID = ?", $tn);
		
   # echo $sql . " - " . $contentid . "<br/>";

   if ($stmt = $mysqli->prepare($sql))
   {
	$stmt->bind_param("i",$contentid);
	$stmt->execute();
	$stmt->bind_result($ShortDescription);
	$stmt->fetch();
	$stmt->close();
   	$mysqli->close();	
	#echo $ShortDescription;
	return $ShortDescription;
   }	
   else
	{ echo 'failed to prepare in getDescription'; }	

   $mysqli->close();	
}

  public function load()
  {
  	$mysqli = newConn();

	if ($stmt = $mysqli->prepare("SELECT contenttype, contentid from tree where ID=?"))
        {

	$stmt->bind_param("i", $this->id);
	$stmt->execute();
	$stmt->bind_result($ctype, $contentid);
	
	$stmt->fetch();

	$this->value = node::getDescription($contentid, $ctype);
	$this->contenttype = $ctype;
	$this->contentid = $contentid;

	$stmt->close();
	
       }

	$mysqli->close();
  }

  public function loadChildren()
  {
	$mysqli = newConn();

	#echo 'Load Children on ' . $this->value . " " . $this->id.  " <br/>\n";

	if ($stmt = $mysqli->prepare("SELECT id, contenttype, contentid from tree where ParentID=?"))
        {
		$stmt->bind_param("i", $this->id);
		$stmt->execute();
		$stmt->bind_result($cid, $ctype, $contentid);
	
	while ($stmt->fetch())
	{
		$desc = node::getDescription($contentid, $ctype);
		$node = node::fromContentType($cid, $desc, $ctype, $contentid);
		array_push($this->childNodes, $node);		
		#$node->loadChildren();
	}

	$stmt->close();
	
	#echo 'children = ' . count($this->childNodes) . "<br/>\n";
	
       }

	foreach ($this->childNodes as $child)
	{
		array_push($this->allSubordinates, $child);
		array_push($this->allSubordinates, $child->allSubordinates);
	}

	$mysqli->close();
  }

  public function toHTMLString($level = 0)
  {
 	$result = "<p>" . str_repeat('&nbsp;&nbsp;',$level) . ' -> ' . $this->value . '</p>';
	foreach ($this->childNodes as $childNode)
	{
	   $result = $result . $childNode->toHTMLString($level + 1);
	}

	return $result;
  }

 public function toShortString($parentid = 0)
  {
 	$result = $parentid . " " . $this->id . " ";
	foreach ($this->childNodes as $childNode)
	{
	   $result = $result . $childNode->toShortString($this->id);
	}

	return $result;
  }

   public function addChild($newnode, $parent)
   {
   	$newnode->parentNode = $parent;
        if (!in_array($newnode, $parent->childNodes))
        {
	   push_array($newnode, $parent->childNodes);	
        }
   }
}

class Tree
{
  public $rootNode;

  public function __construct($value)
  {
	$this->rootNode = $value;
  }


}




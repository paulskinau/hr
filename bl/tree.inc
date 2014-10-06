<?php

#include("../db/db.inc");

class ActorNode extends Node
{
   public $FirstName;
   public $LastName;
   private $tagsuffix;

   protected function loadNodeData()
  {
	$mysqli = newConn();

    	$tn = getContentTypeTableName($this->contenttype);
 
    	$sql = sprintf("SELECT FirstName, LastName FROM %s where ContentID = ?", $tn);
		
        if ($stmt = $mysqli->prepare($sql))
   	{
	  $stmt->bind_param("i",$this->contentid);
	  $stmt->execute();
	  $stmt->bind_result($FirstName, $LastName);
	  $stmt->fetch();
	  $stmt->close();
   	  $mysqli->close();	
	  $this->value = $FirstName . " " . $LastName;
	  $this->tagsuffix = $FirstName . "|" . $LastName;
   	}	
   	else
	{ echo 'failed to prepare in ActorNode.loadNodeData ' . $sql.  ' ' . $this->contentid; }	

   #$mysqli->close();	
  }

  public function getTagSuffix()
  {
  	return $this->tagsuffix;
  }

}

class HierarchyNode extends Node
{
}

class TVShowNode extends Node
{
}

class CountryNode extends Node
{
}

class ReferenceNode extends Node
{
	public $refid;

	public function __construct($id, $rootnode)
	{
		$refid = $id;
		$this->rootNode = $rootnode;

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

  public function __construct($id, $rootnode = null, $contenttype = null, $contentid = null)
  {

	$this->id = $id;
	$this->allSubordinates = array();
	if ($rootnode != null)
	{
		$this->rootNode = $rootnode;
	}

	if ($contenttype == null || $contentid == null )
	{

		$this->load();
	}
	else
	{	$this->contenttype = $contenttype;
		$this->contentid = $contentid;
	}

	$this->loadNodeData();

	$this->loadChildren();
	
  }

  public function getTagSuffix()
  {
  	return $this->value;
  }

  public static function fromContentType($id, $rootnode, $contenttype, $contentid)
  {
 	    switch ($contenttype)
	    {
		case 1:
			return new HierarchyNode( $id, $rootnode, $contenttype, $contentid);
		case 2:
			return new TVShowNode($id, $rootnode, $contenttype, $contentid);
		case 3:
			return new ActorNode($id, $rootnode, $contenttype, $contentid);	
		case 4:
			return new CountryNode($id, $rootnode, $contenttype, $contentid);		
		case 5:
			return new ReferenceNode($id, $rootnode); 
	    }
	
  }

  protected function loadNodeData()
  {
	$mysqli = newConn();

    	$tn = getContentTypeTableName($this->contenttype);
 
    	$sql = sprintf("SELECT ShortDescription FROM %s where ContentID = ?", $tn);
		
        if ($stmt = $mysqli->prepare($sql))
   	{
	  $stmt->bind_param("i",$this->contentid);
	  $stmt->execute();
	  $stmt->bind_result($ShortDescription);
	  $stmt->fetch();
	  $stmt->close();
   	  $mysqli->close();	
	  $this->value = $ShortDescription;
   	}	
   	else
	{ echo 'failed to prepare in loadNodeData ' . $sql.  ' ' . $this->contentid; }	

        #$mysqli->close();	
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

	$this->contenttype = $ctype;
	$this->contentid = $contentid;
	$stmt->close();
	
       }

	$mysqli->close();
  }

  public function loadChildren()
  {
	$mysqli = newConn();

	if ($stmt = $mysqli->prepare("SELECT id, contenttype, contentid from tree where ParentID=?"))
        {
		$stmt->bind_param("i", $this->id);
		$stmt->execute();
		$stmt->bind_result($cid, $ctype, $contentid);
	
	while ($stmt->fetch())
	{
		if (array_key_exists($cid, $this->rootNode->allSubordinates))
		{	
			throw new RecursiveTreeException(" ID = " . $cid . " is a duplicate");
		}

		$this->rootNode->allSubordinates[$cid] = '';

		$node = node::fromContentType($cid, $this->rootNode, $ctype, $contentid);
				
		$this->addChild($node);
		$this->rootNode->allSubordinates[$cid] = $child;
			
	}

	$stmt->close();

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

 public function toShortestString()
	{
		return gzcompress($this->toShortString());
	}

 public function getTag($parentid = 0)
  {
  	return str_pad($parentid,3,"0", STR_PAD_LEFT) . "" . str_pad($this->id,3,"0", STR_PAD_LEFT) . "" . str_pad($this->contenttype, 2, "0", STR_PAD_LEFT). "" . $this->getTagSuffix() . "~";
  }



 public function toShortString($parentid = 0)
  {
 	$result = $this->getTag($parentid);
	foreach ($this->childNodes as $childNode)
	{
	   $result = $result . $childNode->toShortString($this->id);
	}

	return $result;
  }

   public function addChild($newnode)
   {
        if (!in_array($newnode,$this->childNodes))
        {
	   array_push($this->childNodes,$newnode);	
        }

	$this->rootNode->allSubordinates[$newNode->id] = $newNode;
   }

   public function updateTags($parentid = 0)
   {
	global $mysqli;
	   $sql = "update tree set TagName = ? where ID = ?";
	   if ($stmt = $mysqli->prepare($sql))
   {
	$ss = $this->getTag($parentid);
	$stmt->bind_param("si", $ss, $this->id);
	$stmt->execute();
	$stmt->fetch();
	$stmt->close();
   }
	else 
	{ echo "could not prepare in UpdateTags"; }

	foreach ($this->childNodes as $node)
	{
		$node->updateTags($this->id);
	}

}
}

class Tree
{
  public $rootNode;

  public function __construct($value)
  {
	$this->rootNode = $value;
	$this->rootNode->allSubordinates[$value->id] = $value;
  }

  public function updateTags()
  {
	$mysqli = newConn();

	$this->rootNode->updateTags();
  }
}

class RecursiveTreeException extends Exception
{}




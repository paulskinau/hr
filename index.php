<?php require("header.inc"); ?>

<body>


<div data-role="page" id="home">

<?php require("menu.inc"); ?>

  <div data-role="header">
    <h1>Content Hierarchies</h1>
  </div>

  <div data-role="main" class="ui-content">
    <p>This mobile site will allow you to add new TV content hierarchies. A hierarchy is a list of relationships between TV shows, Actors and Countries of Origin.</p>
    <a href="#pagetwo" data-transition="slide">Read more on content types</a>
  </div>  

  <div data-role="footer">
    <h1>Copyright Paul Skinner</h1>
  </div>
</div>

<div data-role="page" id="pagetwo">

<?php require("menu.inc"); ?>

  <div data-role="header">
    <h1>Content Hierarchies</h1>
  </div>

  <div data-role="main" class="ui-content">
<p>There are several content types that can be linked to a hierarchy. These include: </p>

     <ul class="ui-listview ui-listview-inset ui-corner-all ui-shadow" data-role="listview" data-inset="true">
			<li class="ui-li-static ui-body-inherit ui-first-child">
				<h3>TV Shows</h3>
				<p>TV Shows are show on TV. They star actors and are typically located in a single country, or country of origin.</p>
			</li>
			<li class="ui-li-static ui-body-inherit">
				<h3>Actors</h3>
				<p>An actor performs in a TV show. Actors can be male or female. Actors are born in a country, which is their country of origin</p>
			</li>
			<li class="ui-li-static ui-body-inherit ui-last-child">
                                <h3>Countries of Origin</h3>
                                <p>TV shows are typically filmed in a single country, or mostly in a single country. </p>
				<p>Actors are borin in their country of origin.</p>
                        </li>
		</ul>    

    <a href="#home" data-transition="slide">Back to home</a>
  </div>  

  <div data-role="footer">
    <h1>Copyright Paul Skinner</h1>
  </div>



</div>


</body>

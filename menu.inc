<?php $fn = basename($_SERVER['PHP_SELF']); ?>

<div data-role="header">
  <div data-role="navbar">
    <ul>
      <li><a href="index.php" data-icon="home" 
	<?php if ($fn == "index.php") echo 'class="ui-btn-active ui-state-persist"' ?>
	>Home</a></li>
      <li><a href="list.php" data-icon="grid"
	<?php if ($fn == "list.php" || $fn == "item.php") echo 'class="ui-btn-active ui-state-persist"' ?>
	>List Hierarchies</a></li>
      <li><a href="search.php" data-icon="search"
        <?php if ($fn == "search.php") echo 'class="ui-btn-active ui-state-persist"' ?>
        >Search Hierrchies</a></li>
    </ul>
  </div>
</div>


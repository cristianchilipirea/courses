Hello
<?php
	echo "World";

	$private = " ";
	$shared = " ";
	$redis = new Redis();
	$redis->connect('myredis');

	if(isset($_POST['shared']))
		$redis->set('shared', $_POST['shared']);
	if(isset($_POST['private']))
		file_put_contents("/tmp/private_val",$_POST['private']);
	$shared = $redis->get('shared');
	if(file_exists("/tmp/private_val"))
		$private = file_get_contents("/tmp/private_val");
?>

<form action="index.php"  method="post">
  <label for="shared">Shared Value:</label><br>
  <input type="text" id="shared" name="shared" value="<?php echo $shared; ?>"><br>
  <input type="submit" value="Submit">
</form> 
 <form action="index.php"  method="post">
  <label for="private">Private Value:</label><br>
  <input type="text" id="private" name="private" value="<?php echo $private; ?>"><br><br>
  <input type="submit" value="Submit">
</form>

<?php
	if(file_exists("/var/www/html/MY_NAME"))
		echo "My name is ".file_get_contents("/var/www/html/MY_NAME");
	else
		echo "You still need to add MY_NAME file";
?>

<?php
function hasAccess($key, $timestamp, $username) {
	//echo $key." ".$timestamp." ".$username." ".time()." ".($timestamp + 3600);
	if($timestamp + 2*3600 < time())
		return false;
	return (strcmp($key, md5($username."PRIVATE_KEY".$timestamp)) == 0);
}
?>

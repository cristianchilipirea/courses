<?php

function shutDownFunction() {
    $error = error_get_last();
     // Fatal error, E_ERROR === 1
    if ($error['type'] === E_ERROR) {

	echo "Acest server folosește versiunea greșită de php, si nu putem folosi funcțiile mysqli pentru a ne conecta la serverul web. Va trebui să dezinstalați această versiune de php și să instalați versiunea 5.6.";
    }
}
register_shutdown_function('shutDownFunction');

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

define('DB_SERVER', 'mysql-server');
define('DB_USERNAME', 'root');
define('DB_PASSWORD', 'student');
define('DB_NAME', 'demo');

$link = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}

$ip = $_SERVER['REMOTE_ADDR'];

$sql = "INSERT INTO user_access(ip) VALUES ('" . $ip . "');";

if($link->query($sql) != TRUE)
{
	echo "ERROR SQL: " . sql . $link->error . "<br>Asigurati-va ca baza de date 'demo' a fost creata impreuna cu tabelul 'user_access'.";
	die();
}

$sql = "SELECT COUNT(*) AS total FROM user_access WHERE ip = '" . $ip . "';";

$result = $link->query($sql);
$row = $result->fetch_row();
$nTimes = $row[0];

echo "<h1>Hello, $ip, you accessed the page $nTimes times.</h1>";

?>



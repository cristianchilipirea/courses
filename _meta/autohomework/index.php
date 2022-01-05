<?php
if($_SERVER["HTTPS"] != "on")
{
    header("Location: https://" . $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"]);
    exit();
}
$timestamp = date("U");
function authUser($username, $passwd, &$fullName) {
	// basic sequence with LDAP is connect, bind, search, interpret search
	// result, close connection

	$credentials = array_map('str_getcsv', file('students.csv'));
	//print_r($credentials);
	foreach($credentials as $credential) {
		if($credential[1] == $username && $credential[2] == $passwd)
			return true;
	}
	return false;
}

session_start();

if(isset($_POST['username']) &&  isset($_POST['password'])) {
	$Name = "";
	$rez = authUser($_POST['username'], $_POST['password'], $Name);
	if($rez) {
		$_SESSION['Name'] = $Name;
		$_SESSION['username'] = $_POST['username'];
	} else {
		$failedLogIn = true;
	}
}
if(isset($_POST['logout'])) {
	unset($_SESSION['Name']);
	unset($_SESSION['username']);
}
?>
<html>
<head>
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
<link href="style.css" rel="stylesheet">
<script src="https://code.jquery.com/jquery-3.3.1.js" integrity="sha256-2Kok7MbOyxpgUVvAk/HJ2jigOSYS2auK4Pfzbm7uH60=" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
<script src="js.js"></script>
<title>Uploader teme APD</title>
<script>
	function validateForm() {
		var x = document.forms["myForm"]["username"].value;
		var y = document.forms["myForm"]["password"].value;
		if ((x == null || x == "")||(y == null || y == "")) {
			alert("Numele de utilizator si Parola trebuie completate!");
			return false;
		}
	}
	function logout(){
		logout = $_POST['logout'];
	}
</script>
</head>
<body>

<?php
	if(!isset($_SESSION["username"])) {
	?>
		<div class="w3-container">
		  <div  style="background-color:white;"> <h2 style="text-align:left;"><strong>Checker teme STD</strong></h2></div> 
		  <h3 class="form-signin-heading" >Trebuie sa te autentifici, folosind datele de autentificare de pe serverul de laboratoare din fisierul password.</h3>
		</div>
<?php
	}
	if(isset($failedLogIn)) {
	?>
		<div class="w3-container w3-orange" style =" position:float; center:50%;" >
		<h2 class="form-signin-heading" style="color:red;background-color:white; align:center;"> Combinatia nume utilizator, parola nu exista!</h2>
		</div>
	<?php
	}
	if(!isset($_SESSION["username"])) {
	?>		
		 <div class="form">
			<form class="form-signin" action="index.php" method="post" name ="myForm" onsubmit="return validateForm()">
			  <input class="form-control" type="text" name="username" placeholder="Nume utlizator"/>
			  <input class="form-control" type="password" name="password" placeholder="Parola"/>
			  <button class="btn btn-lg btn-primary btn-block">login</button>
			</form>
			</div>
	<?php
	} else {
		?>
	<nav class="navbar justify-content-end">
		<?php 	$username = strtolower(trim($_SESSION["username"]," "));
		echo "<strong>". $username."</strong>";
		?>
		<form action="index.php" method="post">
			<button type="submit" class="btn btn-primary btn-sm" name="logout">Log Out</button>
		</form>
	</nav>
	<form>
	<button class="btn btn-primary" onclick="location.reload();" style="margin-left:30px">Refresh Page</button>
	</form>
	 <iframe id="content" src="https://chilipirea.ro/ap-homework/main.php?username=<?php echo $username; ?>&key=<?php echo md5($username."bdsadsadasdsa".$timestamp); ?>&timestamp=<?php echo $timestamp; ?>" width="100%" frameborder="0"></iframe>
	<?php
	}
	?>
</body>
</html>


<html>
<head>
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
<link href="style.css" rel="stylesheet">
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
<script src="js.js"></script>
</head>
<body>
<div class="accordion" id="accordionExample">

<?php

function getTimeFromFile($fileName) {
	$parts = explode('#', $fileName);
	$parts = explode('@', $parts[1]);
	return((int)$parts[1]);
}

function getTimeFromDir($fileName) {
	$parts = explode('@', $fileName);
	return((int)$parts[1]);
}

function getIdFromTime($time) {
	return(date("d-M-Y H:i:s",$time));
}

include 'authorization.php';
if(!hasAccess($_GET['key'], $_GET['timestamp'], $_GET['username']))
{
	echo "NO ACCESS";
	exit();
}

$username = $_GET['username'];
$timestamp = date("U");

?>
Dacă checker-ul nu afișează rezultatul (nici după 30 min) anuntati pe teams .
<br>
Pentru a vedea rezultatele trebuie sa dati refresh. 
<div style="display: flex;">
	<form id="submissionForm" class="form-inline" action="upload.php" method="post" enctype="multipart/form-data">
		<input type="hidden" name="username" value="<?php echo $username;?>">
		<input type="hidden" name="key" value="<?php echo $_GET['key'];?>">
		<input type="hidden" name="timestamp" value="<?php echo $_GET['timestamp'];?>">
		<input type="hidden" name="task" value="<?php echo $_GET['task'];?>">

		<div class="form-group">
			<label for="submitHomework">Submite tema:</label>
			<input type="file" name="fileToUpload" id="fileToUpload" accept=".zip">
		</div>
		<input class="btn btn-primary" type="submit" value="Upload" name="submit">
		<!--<div class="upload-drop-zone" id="drop-zone">
			Just drag and drop files here
		</div>-->
	</form>
</div>

<?php




// uploads?
$files = scandir("uploads");
foreach($files as $file) {
	if(strpos($file, $username)!==FALSE) {
		echo "<div class=\"alert alert-success\" role=\"alert\">Submission ".getIdFromTime(getTimeFromFile($file))." is <strong>";
		$count = -2; // to account for . and ..
		$files1 = scandir("uploads");
		foreach($files1 as $fileAux) {
			if(getTimeFromFile($file) > getTimeFromFile($fileAux))
				$count++;
		}
		echo $count."</strong> in WAITING queue</div>";
	}
}

$files = scandir("buffer");
$submissionsRunning = array();
foreach($files as $file) {
	if(strpos($file, $username)!==FALSE) {
		//echo "<div class=\"alert alert-success\" role=\"alert\">Submission ".getIdFromTime(getTimeFromFile($file))." is RUNNING</div><br>";
		array_push($submissionsRunning, getTimeFromFile($file));
	}
}

$homeworksTypes = scandir("rezults", SCANDIR_SORT_DESCENDING);
$i = 0;
//foreach($homeworksTypes as $homeworkType) {
	$homeworkType = $_GET['task'];
	if(!is_dir("rezults/".$homeworkType."/".$username))
		return;
	$homeworkDirs = scandir("rezults/".$homeworkType."/".$username, SCANDIR_SORT_DESCENDING);
	foreach($homeworkDirs as $homeworkDir) {
		if($homeworkDir=="." || $homeworkDir=="..")
			continue;
		?>
		 <div class="card">
			<div class="card-header" id="heading<?php echo $i; ?>">
				<h5 class="mb-0">
					<button class="btn <?php if(in_array($homeworkDir, $submissionsRunning)) echo "btn-success"; else echo "btn-link";?>" type="button" data-toggle="collapse" data-target="#collapse<?php echo $i; ?>" aria-expanded="false" aria-controls="collapse<?php echo $i; ?>">
					<?php echo "Submission ".getIdFromTime($homeworkDir)." for ".$homeworkType; if(in_array($homeworkDir, $submissionsRunning)) echo " is RUNNING";?>
					</button>
				</h5>
			</div>

		<div id="collapse<?php echo $i; ?>" class="collapse" aria-labelledby="heading<?php echo $i; ?>" data-parent="#accordionExample">
		  <div class="card-body">
			<?php
				$myfile = fopen("rezults/".$homeworkType."/".$username."/".$homeworkDir."/contents.txt", "r");
				$contents = fread($myfile, filesize("rezults/".$homeworkType."/".$username."/".$homeworkDir."/contents.txt"));
				echo "<xmp>".$contents."</xmp>";
				fclose($myfile);

				$myfile = fopen("rezults/".$homeworkType."/".$username."/".$homeworkDir."/rezult.txt", "r");
				$contents = fread($myfile, filesize("rezults/".$homeworkType."/".$username."/".$homeworkDir."/rezult.txt"));
				//
				//print_r($contents);
				//$contents = explode("========================", $contents);
				//print_r($contents);
				echo "<xmp>".$contents."</xmp>";
				fclose($myfile);
			?>
		  </div>
		</div>
		</div>
		<?php
		$i++;
	}
//}
?>
  </div>
</body>
</html>

<?php
include 'authorization.php';

if(!hasAccess($_POST['key'], $_POST['timestamp'], $_POST['username']))
{
	echo "NO ACESSS. You need to login again or refresh the page before you try to submit again.";
	exit();
}

//echo "UPLOAD PERIOD ENDED";
//exit();

function getHomeworkType($username, $time) {
	$homeworkTypes = array(
				array("users"=>"" , "startTime"=>1635960676, "endTime"=>1636952400, "name"=>"2021-ap-homework-1"),
				array("users"=>"" , "startTime"=>1617606000, "endTime"=>1619769600, "name"=>"sda-homework1"));

	foreach($homeworkTypes as $homeworkType) {
		if ($homeworkType["startTime"] < $time && $time < $homeworkType["endTime"]) {
			return $homeworkType["name"];
		}
	}
	echo "You are outside submission time";
	exit();
}

$target_dir = "uploads/";
$homeworkType = $_POST['task'];
$target_file = $target_dir.$homeworkType."#".$_POST['username']."@".date('U')."#.zip";
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

$uploads_files = scandir($target_dir);
foreach($uploads_files as $upload_file) {
	if(strpos($upload_file,  $_POST['username'])!==FALSE) {
		echo "ERROR You already have a submission in the waiting queue";
		exit();
	}
}

// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $uploadOk = 1;
}
// Check if file already exists
if (file_exists($target_file)) {
    echo "Sorry, file already exists.";
    $uploadOk = 0;
	exit();
}
// Check file size
if ($_FILES["fileToUpload"]["size"] > 500000) {
    echo "Sorry, your file is too large.";
    $uploadOk = 0;
	exit();
}
// Allow certain file formats
if($imageFileType != "zip") {
    echo "Sorry, only ZIP files are allowed.";
    $uploadOk = 0;
	exit();
}
// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
	exit();
} else {
	echo($_FILES["fileToUpload"]["tmp_name"]);
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
    } else {
        echo "Sorry, there was an error uploading your file.";
		exit();
    }
}
header('Location: main.php?task='.$_POST['task'].'&username='.$_POST['username'].'&key='.$_POST['key'].'&timestamp='.$_POST['timestamp']);
?>

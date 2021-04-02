<?php
// Heavely UGLY code, do not use in real life stuff, this is meant just to be a demo
function CallAPI($method, $url, $data = false)
{
    $curl = curl_init();

    switch ($method)
    {
        case "POST":
            curl_setopt($curl, CURLOPT_POST, 1);

            if ($data)
                curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
            break;
        case "PUT":
            curl_setopt($curl, CURLOPT_PUT, 1);
            break;
        default:
            if ($data)
                $url = sprintf("%s?%s", $url, http_build_query($data));
    }

    // Optional Authentication:
    //curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    //curl_setopt($curl, CURLOPT_USERPWD, "username:password");
	curl_setopt($curl, CURLOPT_HTTPHEADER, array(
		'User-Agent: PostmanRuntime/7.26.10',
		'Ocp-Apim-Subscription-Key: ***REMOVED***',
		'Host: westeurope.stt.speech.microsoft.com',
		'Content-type: application/ssml+xml; charset=utf-8',
		'Connection: Keep-Alive',
		'X-Microsoft-OutputFormat: ogg-24khz-16bit-mono-opus'
	));
	curl_setopt($curl, CURLINFO_HEADER_OUT, true);
	curl_setopt($curl, CURLOPT_HEADER, 1);
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
	
    $result = curl_exec($curl);
	echo "rere1";
	print_r(curl_getinfo($curl));
	echo "dede1";
    curl_close($curl);

    return $result;
}


echo "sasa3";
echo "sasa2";

$somexml = "<speak version='1.0' xml:lang='ro-RO'><voice xml:lang='ro-RO' xml:gender='Female' name='ro-RO-EmilNeural '>Și cum știți eu știu să sar.</voice></speak>";
$aux = CallAPI("POST", "https://westeurope.tts.speech.microsoft.com/cognitiveservices/v1",$somexml);
file_put_contents("test.ogg",$aux);

echo "sasa56";
// PHP Data Objects(PDO) Sample Code:
try {
    $conn = new PDO("sqlsrv:server = tcp:chilipirea.database.windows.net,1433; Database = mydb", "chilipirea", "cristian#12345");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch (PDOException $e) {
    print("Error connecting to SQL Server.");
    die(print_r($e));
}

foreach ($conn->query("select * from [dbo].[Persons];") as $row) {
	print_r($row);
}


echo "sasa566";
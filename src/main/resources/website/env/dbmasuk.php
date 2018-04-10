<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if (isset($_GET['flow']) && isset($_GET['ultra'])) {
 
    $flow = $_GET['flow'];
    $ultra = $_GET['ultra'];
 
    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
	require_once($filepath."/dbcon.php");

 
    // Connecting to database 
    $db = new DB_CONNECT();
 
    // Fire SQL query to insert data in sensor
    $result = mysql_query("INSERT INTO sensor(flow,ultra) VALUES('$flow','$ultra')");
 
    // Check for succesfull execution of query
    if ($result) {
        // successfully inserted 
        $response["success"] = 1;
        $response["message"] = "Sensor berhasil dibuat.";
 
        // Show JSON response
        echo json_encode($response);
    } else {
        // Failed to insert data in database
        $response["success"] = 0;
        $response["message"] = "hmm.. sepertinya ada yang salah.";
 
        // Show JSON response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter ada yang hilang. cek lagi permohonannya.";
 
    // Show JSON response
    echo json_encode($response);
}
?>
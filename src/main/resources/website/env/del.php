<?php
 
header('content-type: application/json; charset=utf-8');
header("access-control-allow-origin: *");

//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if (isset($_GET['id'])) {
    $id = $_GET['id'];
 
    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
	require_once($filepath."/dbcon.php");
 
    // Connecting to database 
    $db = new DB_CONNECT();
 
    // Fire SQL query to delete sensor data by id
    $result = mysql_query("DELETE FROM sensor WHERE id = $id");
 
    // Check for succesfull execution of query
    if (mysql_affected_rows() > 0) {
        // successfully deleted
        $response["success"] = 1;
        $response["message"] = "Data berhasil dihapus";
 
        // Show JSON response
        echo json_encode($response);
    } else {
        // no matched id found
        $response["success"] = 0;
        $response["message"] = "Tidak terdeteksi data sensor dari id";
 
        // Echo the failed response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter hilang. check permohonan lagi coba";
 
    // Show JSON response
    echo json_encode($response);
}
?>
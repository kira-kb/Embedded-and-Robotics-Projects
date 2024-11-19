<?php
$servername = "localhost";
$dbname = "id20412039_espdata";
$username = "id20412039_esp32";
$password = "JWj<K@b4f1tVZ<r2";

$con = mysqli_connect($servername, $username, $password, $dbname);

if (mysqli_connect_errno()) {
    die("Failed to connect to MySQL: " . mysqli_connect_error());
}
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $sql = "SELECT *FROM data WHERE id=1";
    $res = $con->query($sql);

    if ($res) {

        while ($row = mysqli_fetch_assoc($res)) {
            // echo "led1" . $row["led1"]. " <br> led2" . $row["led2"];
            echo json_encode(array("led1" => $row["led1"], "led2" => $row["led2"]));
        }
    } else {
        echo "sorry cannot display";
    }

}

if ($_SERVER["REQUEST_METHOD"] == "POST") {

    $led1 = $_POST["led1"];
    $led2 = $_POST["led2"];

    // if (!$con) {
    //     die("connection faild...");
    // }

    echo $led1;
    echo $led2;

    // $sql = "UPDATE data SET led1 = " . $led1 . " , led2 = " . $led2 . " WHERE id=1";
    $sql = "UPDATE data SET led1 = " . $led1 . " , led2 = " . $led2 . ", led3 = " . $led3 . ", led4 = " . $led4 . " , led5 = " . $led5 . ", led6 = " . $led6 . " , led7 = " . $led7 . " , led8 = " . $led8 . " WHERE id=1";

    if (!$con->query($sql)) {
        echo "faild to update";
    }

    // if($con->query($sql)) echo "update succesfully";
    // else echo "faild to update";
}

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $fname = htmlspecialchars($_POST['fname']);
    $lname = htmlspecialchars($_POST['lname']);
    $dob = htmlspecialchars($_POST['dob']);
    $username = htmlspecialchars($_POST['username']);
    $password = htmlspecialchars($_POST['password']);

    echo "First Name: " . $fname . "<br>";
    echo "Last Name: " . $lname . "<br>";
    echo "Date of Birth: " . $dob . "<br>";
    echo "Username: " . $username . "<br>";
    echo "Password: " . $password . "<br>";
} else {
    echo "Invalid request method.";
}
?>
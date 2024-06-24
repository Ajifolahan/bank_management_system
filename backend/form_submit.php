<?php
// Db connection parameters
$host = 'your_host';
$dbname = 'your_dbname';
$user = 'your_dbuser';
$password = 'your_dbpassword';

try {
        // Connect to PSQL
        $dsn = "pgsql:host=$host;dbname=$dbname";
        $pdo = new PDO($dsn, $user, $password, [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);

        // SQL statement
        $stmt = $pdo->prepare('INSERT INTO users (first_name, last_name, date_of_birth, username, password) VALUES (:fname, :lname, :dob, :username, :password)');

        // Hash password for security
        $hashed_password = password_hash($_POST['password'], PASSWORD_DEFAULT);

        // Process form data
        $stmt->execute([
            ':fname' => $_POST['fname'],
            ':lname' => $_POST['lname'],
            ':dob' => $_POST['dob'],
            ':username' => $_POST['username'],
            ':password' => $hashed_password
        ]);

        echo "<p>Signup successful! Welcome, " . htmlspecialchars($_POST['fname']) . ".</p>";
    }
    catch (PDOException $e)  // Error handling
    {
        echo 'Database error: ' . $e->getMessage();
    }
?>

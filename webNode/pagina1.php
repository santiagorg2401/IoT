<!DOCTYPE html>
<html>

<head>
    <link rel="stylesheet" href="index.css">
</head>

<body>
    <?php include "login.php"; ?>

    <h1>CALI DATOS</h1>
    <h2>Seleccione una variable:</h2>
    <table border="2px">
        <tr>
            <th>
                VARIABLE
            </th>
            <th>
                DESCRIPCION
            </th>
        </tr>
        <tr>
            <td><a href="temperatura.php">Temperatura</a></td>
            <td>Temperatura del nodo.</td>
        </tr>
        <tr>
            <td><a href="humedad.php">Humedad</a></td>
            <td>Humedad del nodo.</td>
        </tr>
    </table>
    <a href="logout.php">Cerrar sesion.</a>
</body>

</html>
<!DOCTYPE html>
<html>

<head>
    <link rel="stylesheet" href="index.css">
</head>

<body>
    <?php include "login.php"; ?>

    <h1>CALI DATOS</h1>
    <h2>Seleccione una opción:</h2>
    <table border="2px">
        <tr>
            <th>
                Opción
            </th>
        </tr>
        <tr>
            <td><a href="all.php">Ver todos los datos.</a></td>
        </tr>
        <tr>
            <td><a href="variables.php">Ver datos de sensores.</a></td>
        </tr>
        <tr>
            <td><a href="states.php">Ver datos de alertas.</a></td>
        </tr>
    </table>
    <a href="logout.php">Cerrar sesion.</a>
</body>

</html>
<!DOCTYPE html>
<html>

<head>
    <link rel="stylesheet" href="index.css">

</head>

<body>
    <?php include "login.php"; ?>
    <h1>Datos de humedad.</h1>
    <table border="2px">
        <tr>
            <th>ID NODO</th>
            <th>HUMEDAD</th>
            <th>FECHA</th>
        </tr>
        <?php
        $url_rest = "http://localhost:3000/datos";
        $curl = curl_init($url_rest);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        $respuesta = curl_exec($curl);
        if ($respuesta === false) {
            curl_close($curl);
            die("Error...");
        }
        curl_close($curl);
        //echo $respuesta;
        $resp = json_decode($respuesta);
        $tam = count($resp);
        for ($i = 0; $i < $tam; $i++) {
            $j = $resp[$i];
            $idnodo = $j->idnodo;
            $hum = $j->humedad;
            $fecha = $j->fecha;
            echo "<tr><td>$idnodo</td><td>$hum</td><td>$fecha</td></tr>";
        }
        ?>
    </table>
    <a href="pagina1.php">Volver.</a>
    <a href="logout.php">Cerrar sesion.</a>
</body>

</html>
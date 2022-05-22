<!DOCTYPE html>
<html>

<head>
    <link rel="stylesheet" href="index.css">

</head>

<body>
    <?php include "login.php"; ?>
    <h1>Datos de estados y alertas.</h1>
    <table border="2px">
        <tr>
            <th>My Solar Grid ID.</th>
            <th>date.</th>
            <th>batteryAlert.</th>
            <th>lightSwitch.</th>
        </tr>
        <?php
        if ($us == "usuario1@mysolargrid.com") {
            $url_rest = "http://localhost:3000/datos/1/states";
        } else if ($us == "usuario2@mysolargrid.com") {
            $url_rest = "http://localhost:3000/datos/2/states";
        } else if ($us == "usuario3@mysolargrid.com") {
            $url_rest = "http://localhost:3000/datos/3/states";
        }
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
            $MySolarGridID = $j->MySolarGridID;
            $date = $j->date;
            $batteryAlert = $j->batteryAlert;
            $lightSwitch = $j->lightSwitch;
            echo "<tr><td>$MySolarGridID</td><td>$date</td><td>$batteryAlert</td><td>$lightSwitch</td></tr>";
        }
        ?>
    </table>
    <a href="pagina1.php">Volver.</a>
    <a href="logout.php">Cerrar sesion.</a>
</body>

</html>
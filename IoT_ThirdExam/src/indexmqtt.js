var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost')
const mysql = require('mysql');
// se crea la conexión a mysql
const connection = mysql.createPool({
    connectionLimit: 500,
    host: 'localhost',
    user: 'root',
    password: 'password', //el password de ingreso a mysql
    database: 'SolarGrid',
    port: 3306
});
client.on('connect', function () {
    client.subscribe('topico1', function (err) {
        if (err) {
            console.log("error en la subscripcion")
        }
    })
})
client.on('message', function (topic, message) {
    // message is Buffer
    json1 = JSON.parse(message.toString());
    console.log(json1);
    //client.publish('topico2', 'mensaje recibido')
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            
            if (json1.BatteryVoltaje < 10.0){
                var batteryAlert = 1;
            } else {
                var batteryAlert = 0;
            }

            if (json1.LightLevel < 6000){
                var lightSwitch = 1;
            } else {
                var lightSwitch = 0;
            }

            tempConn.query('INSERT INTO gridData VALUES(null, ?, ?,?,?, ?, ?)', [json1.MySolarGridID, json1.BatteryVoltaje,
            json1.LightLevel, json1.date, batteryAlert, lightSwitch], function (error, result) { //se ejecuta lainserción
                if (error) {
                    throw error;
                    console.log("error al ejecutar el query");
                } else {
                    tempConn.release();
                    console.log("datos almacenados"); //mensaje de respuesta en consola
                }
                //client.end() //si se habilita esta opción el servicio termina
            });
        }
    });
})
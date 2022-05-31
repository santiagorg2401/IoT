const { Router } = require('express');
const router = Router();
const mysql = require('mysql');
// se crea la conexión a mysql
const connection = mysql.createPool({
    connectionLimit: 500,
    host: 'localhost',
    user: 'root',
    password: 'password', //el password de ingreso a mysql
    database: 'robotData',
    port: 3306
});
//function get en la ruta /datos, que trae todos los datos almacenados en la tabla
router.get('/datos', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //si no se pudo conectar
        }
        else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM data', function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se librea la conexión
                    for (i = 0; i < resultado.length; i++) {
                        //se lee el resultado y se arma el json
                        json1 = {
                            "robot_id": resultado[i].robot_id, "temperature": resultado[i].temperature,
                            "weight": resultado[i].weight, "timedate": resultado[i].timedate, "powerState": resultado[i].powerState
                        };
                        console.log(json1); //se muestra el json en la consola
                        arreglo.push(json1); //se añade el json al arreglo
                    }
                    res.json(arreglo); //se retorna el arreglo
                }
            });
        }
    });
});
//función post en la ruta /datos que recibe datos
router.post('/datos', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('INSERT INTO data VALUES(null,?,?,?,?,?)', [json1.robot_id, json1.temperature,
            json1.weight, json1.timedate, json1.powerState], function (error, result) { //se ejecuta lainserción
                if (error) {
                    throw error;
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("datos almacenados"); //mensaje de respuesta
                }
            });
        }
    });
});
module.exports = router;
router.get('/datos/:robot_id', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json
    var id = req.params.robot_id; //recogemos el parámetro enviado en la url
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //si no se pudo conectar
        } else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM data where robot_id=?', [id], function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    //res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se librea la conexió
                    for (i = 0; i < resultado.length; i++) {
                        //se lee el resultado y se arma el json
                        json1 = {
                            "robot_id": resultado[i].robot_id, "temperature": resultado[i].temperature,
                            "weight": resultado[i].weight, "timedate": resultado[i].timedate, "powerState": resultado[i].powerState
                        };
                        console.log(json1); //se muestra el json en la consola
                        arreglo.push(json1); //se añade el json al arreglo
                    }
                    res.json(arreglo); //se retorna el arreglo
                }
            }
            );
        }
    });
});
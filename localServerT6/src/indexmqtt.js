var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost')
client.on('connect', function () {
    client.subscribe('topico1', function (err) {
        if (err) {
            console.log("error en la subscripcion")
        }
    })
})
client.on('message', function (topic, message) {
    // message is Buffer
    console.log(message.toString())
    client.publish('topico2', 'mensaje recibido')
    //client.end() //si se habilita esta opción el servicio termina
})
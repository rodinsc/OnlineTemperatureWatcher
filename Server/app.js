var express = require('express');  
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var urlencodedParser = require('body-parser').urlencoded({extended: false});

var lastUpdate;
var lastRecordedTemperature;

app.use(express.static(__dirname + '/node_modules'));
app.use('/static', express.static('static'));

app.get('/', function(req, res){
    res.end("Main page, you can modify this part.");
});

app.get('/temperature', function(req, res) {  
    res.sendFile(__dirname + '/index.html');
});

app.post('/temperature', urlencodedParser, function(req, res){
    var today = new Date();
    lastUpdate = `${today.getDate()}.${today.getMonth()+1}.${today.getFullYear()} - ${("0" + today.getHours()).slice(-2)}:${("0" + today.getMinutes()).slice(-2)}:${("0" + today.getSeconds()).slice(-2)}`;
    lastRecordedTemperature = req.body.temp;
    io.sockets.emit('update', {temp: req.body.temp, date: lastUpdate});
    res.end("Success.");
})

io.on('connection', function(client) {

    console.log('New client socket connected to server.');
    client.emit('update', {temp: lastRecordedTemperature, date: lastUpdate});

    client.on('join', function(data) {
        if(data === 'Client message.')
        {
            console.log('Client connection successful.');
        }
    });
});

server.listen(80);

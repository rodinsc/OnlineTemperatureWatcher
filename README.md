# Online Temperature Watcher

Online Temperature Watcher is an example of online data transmission between an Arduino and an Express.js Web Server. It is using an Ethernet Card with ENC28J60 chip, and DHT11 to get temperature data. You can modify the code to watch another data with another sensors.

## Watching the data

The Arduino makes POST request to server every 30 seconds, and server updates the data to received data via socket.io so you dont need to refresh the page.

You can change the data update interval in the Arduino code.

## Modifying the code

Things that you have to be careful about when modifying the code are below.

- Dont forget to change the URL in index.html to your server IP address/domain.
- Dont forget to change the host URL in Arduino code to your server IP address/domain.
- You cant establish a TLS (SSL) connection with this code.
- If you have changed the post URL in the server code, dont forget to change it in the Arduino code too.

## Starting the server

Dont forget to install required npm modules before starting the server. You can run the `npm i` command.

## Scheme

<img src="https://i.hizliresim.com/1rap88t.png" width="500"></img>

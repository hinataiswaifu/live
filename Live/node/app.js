const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 4200 });
const seed = Math.floor(Math.random() * 1e7);

let connections = [];

wss.on('connection', function connection(ws) {
    ws.send(seed);
    connections.push(ws);
  ws.on('message', function incoming(message) {
    for(w of connections) {
        if( w != ws ) {
            w.send(message);
        }
    }
  });

  ws.on('close', function close() {
    connections.splice(connections.indexOf(ws), 1);
  });
});

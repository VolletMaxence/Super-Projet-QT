var socket = null;

socket = new WebSocket("ws://127.0.0.1:4321");

function Message(){
    var message = document.getElementById('message').value;
    socket.send(message);
}
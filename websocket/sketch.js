
var socket = null;


//socket = new WebSocket("ws://192.168.64.107:4321");



function Message(){
    socket = new WebSocket("ws://127.0.0.1:4321/ws");
    var json = JSON.stringify("test");
    socket.send(json);
    socket.send(USVString,json);
    socket.onopen = () => socket.send(USVString,json);
    console.log(json);

}
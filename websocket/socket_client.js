var socket = null;

socket = new WebSocket("ws://127.0.0.1:4321");

//fonction qui permet d'envoyer un message au server tcp

function Message(){
    var message = document.getElementById('message').value;
    document.getElementById('message').value = "";
    socket.send(message);
    afficheMess(message);
}


//fonction qui permet de s'inscrire
function inscriptin(){

}
//fonction qui permet de se connecter
function connection(){

}
socket.onmessage = function(recu){
    console.log("un message a etais recu");
}

function afficheMess(Message){
    var li = document.createElement('p');
    li.innerText = Message;
    document.getElementById("Mess").appendChild(li);

}

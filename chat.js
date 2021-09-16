    // API

    // Chat JS

    // Objets

    // Fonctions
    function Affichage(AuthChat){
        if(AuthChat == 1){
            document.getElementById('AuthOn').className = "Sous-Menu-1 DisplayON";
            document.getElementById('AuthOff').className = "Sous-Menu-1 DisplayOFF";
            document.getElementById('AuthChatOn').className = "Chat DisplayON";
            document.getElementById('AuthChatOff').className = "Chat DisplayOFF";
        }
        else{
            document.getElementById('AuthOn').className = "Sous-Menu-1 DisplayOFF";
            document.getElementById('AuthOff').className = "Sous-Menu-1 DisplayON";
            document.getElementById('AuthChatOn').className = "Chat DisplayOFF";
            document.getElementById('AuthChatOff').className = "Chat DisplayON";
        }
    }
    // Variables
    var AuthChat;

    // API

    // Chat JS

    // Fonctions
        function Affichage(AuthChat){
            if(AuthChat == 1){
                document.getElementById('unlogin_user').className = "Sous-Menu-1 DisplayON";
                document.getElementById('connect_user').className = "Sous-Menu-1 DisplayOFF";
                document.getElementById('create_user').className = "Sous-Menu-1 DisplayOFF";
                document.getElementById('AuthChatOn').className = "Chat DisplayON";
                document.getElementById('AuthChatOff').className = "Chat DisplayOFF";
            }
            else{
                document.getElementById('unlogin_user').className = "Sous-Menu-1 DisplayOFF";
                document.getElementById('connect_user').className = "Sous-Menu-1 DisplayON";
                document.getElementById('create_user').className = "Sous-Menu-1 DisplayON";
                document.getElementById('AuthChatOn').className = "Chat DisplayOFF";
                document.getElementById('AuthChatOff').className = "Chat DisplayON";
            }
        }
        // Fonction contact Serveur
        function ContactServer(content){
            // Envoyer Variable
        }
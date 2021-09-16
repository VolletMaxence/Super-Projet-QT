    // Variables
    var AuthChat;

    // API

    // Chat JS

    // Objets

    // Fonctions
        function Affichage(AuthChat){
            if(AuthChat == 1){
                document.getElementById('AuthMenuOn').className = "Sous-Menu-1 DisplayON";
                document.getElementById('AuthMenuOff').className = "Sous-Menu-1 DisplayOFF";
                document.getElementById('AuthChatOn').className = "Chat DisplayON";
                document.getElementById('AuthChatOff').className = "Chat DisplayOFF";
            }
            else{
                document.getElementById('AuthMenuOn').className = "Sous-Menu-1 DisplayOFF";
                document.getElementById('AuthMenuOff').className = "Sous-Menu-1 DisplayON";
                document.getElementById('AuthChatOn').className = "Chat DisplayOFF";
                document.getElementById('AuthChatOff').className = "Chat DisplayON";
            }
        }
        function AffichageStart(){
            Affichage(0);
        }
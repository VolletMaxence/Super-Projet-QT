    // Variables
        var AuthChat;

    // Deffinition Variable CookieUser
        if(typeof CookieUser !== 'undefined'){
            var User_Pseudo = CookieUser['Pseudo'];
            var User_ID = CookieUser['ID'];
        }
        else{
            var User_Pseudo = "Default";
            var User_ID = 0;
        };

    // Chat JS : Recevoir un Message
    function ReceiveMSG(Receive_Pseudo,VMessage,VTime){
        if(Receive_Pseudo === User_Pseudo){
            // Ne rien Faire.
        }
        else{
            // Écrire la valeur
            $('div .Chatbox').append(
                "<p class='ChatTexte'><span class='Time'>[" + VTime + "]</span> | <span class='OtherPseudo'>" + Receive_Pseudo + "</span> : " + VMessage + "</p>"
            )
            // ScrollBare Bottom
            const scrollbarre = document.querySelector("div.Chatbox");
            scrollbarre.scroll(scrollbarre.scrollTopMax, scrollbarre.scrollTopMax);
        }
    }

    // Chat JS : Envoyer un Message
        function SendMSG(){
            // Récupérer l'input et sa valeur
            var VMessage = document.getElementById('ChatArea').value;

            if(VMessage === ''){
                window.alert('Vous ne pouvez pas envoyer un message vide.');
            }
            else{
                // Envoyer la valeur
                    // window.alert('SEND : "SEND :: UserID :: ' + User_ID + ' Message : ' + VMessage + '"');
                // Écrire la valeur
                $('div .Chatbox').append(
                    "<p class='ChatTexte'><span class='Time'>[" + HeureDynamique + "]</span> | <span class='MePseudo'>" + User_Pseudo + "</span> : " + VMessage + "</p>"
                )
                // ScrollBare Bottom
                const scrollbarre = document.querySelector("div.Chatbox");
                scrollbarre.scroll(scrollbarre.scrollTopMax, scrollbarre.scrollTopMax);
                // Vider Champs texte
                $('#ChatArea').val('');
            }
        }

    // Fonctions
        function Affichage(AuthChat){
            // Si connecté
                if(AuthChat == 1){
                    document.getElementById('unlogin_user').className = "Sous-Menu-1 DisplayON";
                    document.getElementById('connect_user').className = "Sous-Menu-1 DisplayOFF";
                    document.getElementById('create_user').className = "Sous-Menu-1 DisplayOFF";
                    document.getElementById('AuthChatOn').className = "Chat DisplayON";
                    document.getElementById('AuthChatOff').className = "Chat DisplayOFF";
                }
            // Si Pas connecté
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

    // DateTime : Heure Dynamique
        function DateTime(){
            date = new Date;
            heure = date.getHours();
            min = date.getMinutes();
            sec = date.getSeconds();
            if (sec < 10)
                sec0 = "0";
            else
                sec0 = "";
            if (min < 10)
                min0 = "0";
            else
                min0 = "";
            if (heure < 10)
                heure0 = "0";
            else
                heure0 = "";
            HeureDynamique = heure0 + heure + ":" + min0 + min + ":" + sec0 + sec;
            if (document.getElementById){
                document.getElementById("DateTime").innerHTML=HeureDynamique;
            }
            setTimeout("DateTime()", 1000)
        }
        window.onload = DateTime;

    // WebSocket
        // Connexion WebSocket
            const socket = new WebSocket('ws://localhost:8080');

        // Connexion ouverte
            socket.addEventListener('open', function (event) {
                socket.send('Coucou le serveur !');
            });

        // Écoute des messages
            socket.addEventListener('message', function (event) {
                console.log('Voici un message du serveur', event.data);
                if(/*   Je recoit un truc qui me dit que le login est bon   */){
                    AuthmLogin(User_ID,User_Pseudo);
                }
                else if(/*   Je recoit un truc qui me dit que l'inscription est bonne   */){
                    
                }
                else if(/*   Je recoit un message classique   */){
                    
                }
            });

    // Authentification
        // Login
        AuthmLogin(User_ID,User_Pseudo){
            document.CookieUser = "Cookie_Pseudo=" + User_Pseudo + "; Cookie_ID=" + User_ID + "; Secure";
            var User_Pseudo = CookieUser['Pseudo'];
            var User_ID = CookieUser['ID'];
        }
    // Variables
        var AuthChat;

    // Deffinition Variable cookie
        if(typeof cookie !== 'undefined'){
            var User_Pseudo = cookie['Cookie_Pseudo'];
            //var User_ID = cookie['ID'];
        }
        else{
            var User_Pseudo = "Default";
            //var User_ID = 0;
        };

    // Chat JS : Recevoir un Message
    function ReceiveMSG(Receive_Pseudo,VMessage){
        if(Receive_Pseudo === User_Pseudo){
            // Ne rien Faire.
        }
        else{
            // Écrire la valeur
            $('div .Chatbox').append(
                "<p class='ChatTexte'><span class='Time'>[" + HeureDynamique + "]</span> | <span class='OtherPseudo'>" + Receive_Pseudo + "</span> : " + VMessage + "</p>"
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
                    socket.send("MESSAGE :: Pseudo :: " + User_Pseudo + " :: Message : " + VMessage);
                    console.log("MESSAGE :: Pseudo :: " + User_Pseudo + " :: Message : " + VMessage)
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
            const socket = new WebSocket("ws://192.168.65.225:4321");

        // Connexion ouverte
            socket.addEventListener('open', function (event) {
                socket.send('Coucou le serveur ! Test');
            });

        // Écoute des messages
            socket.addEventListener('message', function (event) {
                console.log('Voici un message du serveur', event.data);

                if(event.data === "MSG100"){
                    console.log('Je renvoie un MSG100');
                    socket.send("MSG100");
                }
                if(event.data === "LOK"){ // Si le serveur me répond favorablement pour la connexion.
                    if(Temp_CO_Pseudo !== 'undefined'){
                        AuthmLogin(Temp_CO_Pseudo);
                        window.location.reload();
                        console.log('Rafraichisement de la page');
                    }
                }
                //else if(){
                //    AuthmLogin(User_ID,User_Pseudo);
                //}
                //else if(/*   Je recoit un truc qui me dit que l'inscription est bonne   */){
                    
                //}
                else if(event.data.substring(0, 11) === "MESSAGE :: "){
                    Tempo_MSG = event.data.substring(0, 11);
                    const regex = /^([^\t]+) :: ([^\t]+) :: ([^\t]+) : ([^\t]+)$/gm;
                    Temp_MSG_Rec = regex.exec(Tempo_MSG);

                    Receive_Pseudo = Temp_MSG_Rec[2];
                    VMessage = Temp_MSG_Rec[4];

                    console.log(Temp_MSG_Rec);
                    console.log(VMessage);
                    console.log(Receive_Pseudo);

                    ReceiveMSG(Receive_Pseudo,VMessage);
                }
            });

    // Authentification
        // Login
        function AuthmLogin(User_Pseudo){
            document.cookie = "Cookie_Pseudo=" + User_Pseudo;// + "//; Cookie_ID=" + User_ID + "; Secure";
            //var User_Pseudo = cookie['Pseudo'];
            //var User_ID = cookie['ID'];
        }
        // Déconnexion
        function unlogin(){
            document.cookie = 'Cookie_Pseudo=; path=/; expires=Thu, 01 Jan 1970 00:00:00 UTC';
            window.location.reload();
            console.log('Rafraichisement de la page');
        }
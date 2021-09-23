$(function(){
    //Value Inscription
        var in_form;
        var in_dialog;
        var in_name = $("#in_name");
        var in_password = $("#in_password");
        var in_allFields = $([]).add(in_name).add(in_password);
        var in_tips = $(".in_validateTips");
    //Value Connexion
        var co_form;
        var co_dialog;
        var co_name = $("#co_name");
        var co_password = $("#co_password");
        var co_allFields = $([]).add(co_name).add(co_password);
        var co_tips = $(".co_validateTips");

    // Ouverture des Dialog
        $("#create_user").button().on("click", function(){
            in_dialog.dialog("open");
        });
        $("#connect_user").button().on("click", function(){
            co_dialog.dialog("open");
        });
        // UnLogin
        $("#unlogin_user").button().on("click", function(){
            unlogin();
        });

    // Fonction Suivant Inscription Bouton
        function IN_User(){
            var valid = true;
            in_allFields.removeClass("ui-state-error");

            valid = valid && in_checkLength(in_name, "username", 3, 16);
            valid = valid && in_checkLength(in_password, "password", 5, 16);

            valid = valid && in_checkRegexp(in_name, /^[a-z]([0-9a-z_\s])+$/i, "Le nom d'utilisateur ne peut-être que composé de chiffres, de lettres, d'underscores, d'espaces, et doit commencer par une lettre.");
            valid = valid && in_checkRegexp(in_password, /^([0-9a-zA-Z])+$/, "Le mot de passe n'autorise que des chiffres et des lettres.");

            if(valid){
                var IN_Pseudo   =   in_name.val();
                var IN_PassWord =   in_password.val();
                in_dialog.dialog("close");
                window.alert('Le Pseudo est \"' + IN_Pseudo + '\" et le Mots de Passe est \"'+ IN_PassWord + '\".');
                window.alert('INSCRIPTION : "INSCRIPTION :: Pseudo :: IN_Pseudo MdP : IN_PassWord "');
            };
            return valid;
        };

    // Fonction Suivant Connection Bouton
        function Co_User(){
            var valid = true;
            co_allFields.removeClass("ui-state-error");

            valid = valid && co_checkLength(co_name, "username", 3, 16);
            valid = valid && co_checkLength(co_password, "password", 5, 16);

            valid = valid && co_checkRegexp(co_name, /^[a-z]([0-9a-z_\s])+$/i, "Le nom d'utilisateur ne peut-être que composé de chiffres, de lettres, d'underscores, d'espaces, et doit commencer par une lettre.");
            valid = valid && co_checkRegexp(co_password, /^([0-9a-zA-Z])+$/, "Le mot de passe n'autorise que des chiffres et des lettres.");

            if(valid){
                var CO_Pseudo   =   co_name.val();
                var CO_PassWord =   co_password.val();
                co_dialog.dialog("close");
                window.alert('Le Pseudo est \"' + CO_Pseudo + '\" et le Mots de Passe est \"'+ CO_PassWord + '\".');
                window.alert('LOGIN : "LOGIN :: Pseudo :: IN_Pseudo MdP : IN_PassWord "');
            };
            return valid;
        };

    // Fonction sur la Boite Dialogue Inscription
        in_dialog = $("#dialog_inscription").dialog({
            autoOpen: false,
            height: 350,
            width: 350,
            modal: true,
            buttons:{
                "Créer un compte": IN_User,
                Cancel: function(){
                    in_dialog.dialog("close");
                }
            },
            close: function(){
                in_form[0].reset();
                in_allFields.removeClass("ui-state-error");
            }
        });
        in_form = in_dialog.find("form").on("submit", function(event){
            event.preventDefault();
            IN_User();
        });
        function in_updateTips(t){
            in_tips.text(t).addClass("ui-state-highlight");
            setTimeout(function(){
                in_tips.removeClass("ui-state-highlight", 1500);
            }, 500);
        };
        function in_checkLength(o, n, min, max){
            if(o.val().length > max || o.val().length < min){
                o.addClass("ui-state-error");
                in_updateTips("Longueur de " + n + " doit être entre " +
                min + " et " + max + ".");
                return false;
            }else{
                return true;
            }
        };
        function in_checkRegexp(o, regexp, n){
            if(!(regexp.test(o.val()))){
                o.addClass("ui-state-error");
                in_updateTips(n);
                return false;
            }else{
                return true;
            }
        };

    // Fonction sur la Boite Dialogue Connexion
        co_dialog = $("#dialog_connect").dialog({
            autoOpen: false,
            height: 350,
            width: 350,
            modal: true,
            buttons:{
                "Se connecter": Co_User,
                Cancel: function(){
                    co_dialog.dialog("close");
                }
            },
            close: function(){
                co_form[0].reset();
                co_allFields.removeClass("ui-state-error");
            }
        });
        co_form = co_dialog.find("form").on("submit", function(event){
            event.preventDefault();
            CO_User();
        });
        function co_updateTips(t){
            co_tips.text(t).addClass("ui-state-highlight");
            setTimeout(function(){
                co_tips.removeClass("ui-state-highlight", 1500);
            }, 500);
        };
        function co_checkLength(o, n, min, max){
            if(o.val().length > max || o.val().length < min){
                o.addClass("ui-state-error");
                co_updateTips("Longueur de " + n + " doit être entre " +
                min + " et " + max + ".");
                return false;
            }else{
                return true;
            }
        };
        function co_checkRegexp(o, regexp, n){
            if(!(regexp.test(o.val()))){
                o.addClass("ui-state-error");
                co_updateTips(n);
                return false;
            }else{
                return true;
            }
        };
});
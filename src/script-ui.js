$(function(){
    var dialog, form,

    //Value Inscription
        name = $("#in-name"),
        password = $("#in-password"),
        allFields = $([]).add(name).add(password),
        tips = $(".validateTips");
    //Value Connexion
        name = $("#co-name"),
        password = $("#co-password"),
        allFields = $([]).add(name).add(password),
        tips = $(".validateTips");

    // Fonction Check Global
    function updateTips(t){
        tips.text(t).addClass("ui-state-highlight");
        setTimeout(function(){
            tips.removeClass("ui-state-highlight", 1500);
        }, 500);
    }
    function checkLength(o, n, min, max){
        if(o.val().length > max || o.val().length < min){
            o.addClass("ui-state-error");
            updateTips("Longueur de " + n + " doit être entre " +
            min + " et " + max + ".");
            return false;
        }else{
            return true;
        }
    }
    function checkRegexp(o, regexp, n){
        if(!(regexp.test(o.val()))){
            o.addClass("ui-state-error");
            updateTips(n);
            return false;
        }else{
            return true;
        }
    }

    // Fonction Suivant Inscription Bouton
        function addUser(){
            var valid = true;
            allFields.removeClass("ui-state-error");

            valid = valid && checkLength(name, "username", 3, 16);
            valid = valid && checkLength(password, "password", 5, 16);

            valid = valid && checkRegexp(name, /^[a-z]([0-9a-z_\s])+$/i, "Le nom d'utilisateur ne peut-être que composé de chiffres, de lettres, d'underscores, d'espaces, et doit commencer par une lettre.");
            valid = valid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Le mot de passe n'autorise que des chiffres et des lettres.");

            if(valid){
                var Pseudo      =   name.val();
                var PassWord    =   password.val();
                dialog.dialog("close");
                window.alert('Le Pseudo est \"' + Pseudo + '\" et le Mots de Passe est \"'+ PassWord + '\".')
                //  LOGIN       : "LOGIN :: Pseudo :: Pseudo MdP : PassWord "
            }
            return valid;
        }

    // Fonction Suivant Connection Bouton
        function CoUser(){
            var valid = true;
            allFields.removeClass("ui-state-error");

            valid = valid && checkLength(name, "username", 3, 16);
            valid = valid && checkLength(password, "password", 5, 16);

            valid = valid && checkRegexp(name, /^[a-z]([0-9a-z_\s])+$/i, "Le nom d'utilisateur ne peut-être que composé de chiffres, de lettres, d'underscores, d'espaces, et doit commencer par une lettre.");
            valid = valid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Le mot de passe n'autorise que des chiffres et des lettres.");

            if(valid){
                var Pseudo      =   name.val();
                var PassWord    =   password.val();
                dialog.dialog("close");
                window.alert('Le Pseudo est \"' + Pseudo + '\" et le Mots de Passe est \"'+ PassWord + '\".')
                //  LOGIN       : "LOGIN :: Pseudo :: Pseudo MdP : PassWord "
            }
            return valid;
        }

    // Fonction sur la Boite Dialogue Inscription
        dialog = $("#dialog-inscription").dialog({
            autoOpen: false,
            height: 350,
            width: 350,
            modal: true,
            buttons:{
                "Créer un compte": addUser,
                Cancel: function(){
                    dialog.dialog("close");
                }
            },
            close: function(){
                form[0].reset();
                allFields.removeClass("ui-state-error");
            }
        });

        form = dialog.find("form").on("submit", function(event){
            event.preventDefault();
            addUser();
        });

        $("#create-user").button().on("click", function(){
            dialog.dialog("open");
        });

    // Fonction sur la Boite Dialogue Connexion
        dialog = $("#dialog-connect").dialog({
            autoOpen: false,
            height: 350,
            width: 350,
            modal: true,
            buttons:{
                "Se connecter": CoUser,
                Cancel: function(){
                    dialog.dialog("close");
                }
            },
            close: function(){
                form[0].reset();
                allFields.removeClass("ui-state-error");
            }
        });

        form = dialog.find("form").on("submit", function(event){
            event.preventDefault();
            addUser();
        });

        $("#connect-user").button().on("click", function(){
            dialog.dialog("open");
        });
});
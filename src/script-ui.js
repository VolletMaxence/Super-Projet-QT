$(function(){
    var dialog, form,

    name = $("#name"),
    password = $("#password"),
    allFields = $([]).add(name).add(password),
    tips = $(".validateTips");

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

    function addUser(){
        var valid = true;
        allFields.removeClass("ui-state-error");

        valid = valid && checkLength(name, "username", 3, 16);
        valid = valid && checkLength(password, "password", 5, 16);

        valid = valid && checkRegexp(name, /^[a-z]([0-9a-z_\s])+$/i, "Le nom d'utilisateur ne peut-être que composé de chiffres, de lettres, d'underscores, d'espaces, et doit commencer par une lettre.");
        valid = valid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Le mot de passe n'autorise que des chiffres et des lettres.");

        if(valid){
            var Pseudo  =   name.val();
            var MDP     =   password.val();
            dialog.dialog("close");
            window.alert('Le Pseudo est \"' + Pseudo + '\" et le Mots de Passe est \"'+ MDP + '\".')
            //  LOGIN       : "LOGIN :: Pseudo :: name.val() MdP : password.val() "
            //  INSCRIPTION : "INSCRIPTION :: Pseudo : Pseudo MdP : MDP "
        }
        return valid;
    }

    dialog = $("#dialog-form").dialog({
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
});
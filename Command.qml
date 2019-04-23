import QtQuick 2.12

Item{
    signal commandReply(string reply)

    function commandReceive(data){//parses command received from outside and handles it internally
         var command = data["message"]
        if (command !== undefined) {
            var executeCommand = allCommands[data["message"]]

            if(command === "")// ! is special case for help command
                help(data);
            else if(executeCommand === undefined)
                unrecognizedCommand(data) 
            else
                executeCommand.functionToExecute(data)
        }
    }

    Component.onCompleted:{
        //loads all functions
        allCommands["help"] = {"functionToExecute": help, "description": "All the available commands"};
        allCommands["rollDice"] = {"functionToExecute": rollDice, "description": "Rolls the dice and tells you the number it rolled!"};
    }
    function unrecognizedCommand(data){//parsed command non existent
        var reply = ":%1!%1@%1%2 PRIVMSG #%3 :@%1 Command '!%4' not recognized! Use !help to list all available commands"
                              .arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(data["message"]);
        commandReply(reply);
    }

function help(data) {
    var reply;
    if(data["messageArgs"] === "") {//general help, lists all commands (!help)
        var partialReply = "Commands: ";
        for (var pair in allCommands)
            partialReply += "!" + pair + ", ";
           
        partialReply= partialReply.substring(0, partialReply.length - 2);//eliminate trailing ','

        reply = ":%1!%1@%1%2 PRIVMSG #%3 :@%1 %4"
                      .arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(partialReply);
    }
    else{//description of a specific command (!help arg)
        var requiredCommand = data["messageArgs"].split(/\s/)[0];
        if (allCommands[requiredCommand] === undefined)
            reply = ":%1!%1@%1%2 PRIVMSG #%3 :@%1 Command '%4' not recognized!".arg(data["userName"])
                            .arg(data["channel"]).arg(requiredCommand);
        else
            reply = ":%1!%1@%1%2 PRIVMSG #%3 :@%1 %4: %5"
                            .arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(requiredCommand)
                            .arg(allCommands[requiredCommand]["description"]);
    }
    commandReply(reply);
}

function rollDice(data){
    var value = Math.floor(Math.random() * 6 ) + 1;
    var reply = ":%1!%1@%1%2 PRIVMSG #%3 :@%1 rolled %4"
                        .arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(value);

    commandReply(reply);
}


    property var allCommands: ({});//pair of functionName:function, functionDescription

}

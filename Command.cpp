/* PASSED TO QML/JS
#include "Command.h"
Command::Command() {
	allCommands.insert("rollDice", { &Command::rollDice, "Rolls the dice and tells you the number it rolled!"});
	allCommands.insert("help", { &Command::printHelp, "All the available commands" });
	allCommands.insert(QString(), { &Command::printHelp, "All the available commands" });

}

void Command::unrecognizedCommand(const QMap<QString, QString>& data) {
	QString reply = QString(":%1!%1@%1%2 PRIVMSG #%3 :@%1 Command '!%4' not recognized!\
 Use !help to list all available commands")
		.arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(data["message"]);

	emit Command::getInstance().commandReply(reply);
}

void Command::rollDice(const QMap<QString, QString>& data){
	quint32 value = QRandomGenerator::global()->generate()%6 + 1;
	QString reply = QString(":%1!%1@%1%2 PRIVMSG #%3 :@%1 rolled %4")
										    	.arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(value);

	emit Command::getInstance().commandReply(reply);
}

void Command::printHelp(const QMap<QString, QString>& data) {
	QString reply;
	if(data.find("messageArgs") == data.end()) {//general help, lists all commands (!help)
		QString partialReply = QString("Commands: ");
		for (auto command = Command::getInstance().allCommands.begin(); command != Command::getInstance().allCommands.end(); ++command)
			partialReply += "!" + command.key() + ", ";
		
		partialReply = partialReply.left(partialReply.size() - 2);//eliminate trailing ','
		reply = QString(":%1!%1@%1%2 PRIVMSG #%3 :%4")
			.arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(partialReply);

	}
	else{//description of a specific command (!help arg)
		auto requiredCommand = data["messageArgs"].split("\s").first();
		if (Command::getInstance().allCommands.find(requiredCommand) == Command::getInstance().allCommands.end())
			reply = QString(":%1!%1@%1%2 PRIVMSG #%3 :@%1 Command '%4' not recognized!").arg(data["userName"])
							.arg(data["channel"]).arg(requiredCommand);
		else
			reply = QString(":%1!%1@%1%2 PRIVMSG #%3 :@%1 %4: %5")
							.arg(data["userName"]).arg(data["server"]).arg(data["channel"]).arg(requiredCommand)
							.arg(Command::getInstance().allCommands[requiredCommand].second);
	}
	emit Command::getInstance().commandReply(reply);
}

void Command::commandReceive(const QMap<QString, QString>& data) {
	if (auto command = data.find("message"); 
		command != data.end()) {
		if (auto executeCommand = allCommands.find(data["message"]);
			executeCommand == allCommands.end())
			unrecognizedCommand(data);
		else
			executeCommand->first.operator()(data);
	}
}
*/
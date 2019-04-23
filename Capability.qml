import QtQuick 2.12
import QtQuick.Controls 2.5
Button{
	id: capability
	signal capabilityRequested(string command)
	
	property bool isSet: false
	property var command
	property var setColor: Qt.hsla(0.3, 1, 0.25, 0.7)
	property var notSetColor: Qt.hsla(0, 1, 0.5, 0.7)

	background: Rectangle{
		id: background
	}
	onClicked: {
		if(isSet !== true)
			capabilityRequested(command);
	}
	
	states:[
		State{
			name: "notGranted"
			when: (onIsSetChanged && isSet === false)
			PropertyChanges{ target: capability.background; color: capability.down? Qt.darker(notSetColor): notSetColor}
		},
		State{
			name: "granted"
			when: (onIsSetChanged && isSet === true)
			PropertyChanges{ target: capability.background; color: capability.down? Qt.darker(setColor): setColor }
		}
	]

	function replyMatch(reply){
	//	var pattern = /^.*CAP.*(:twitch.tv\/.*)$/i;//case insensitive search
		if(reply.includes(command.replace('CAP REQ :','')) === true)
				isSet = true;
	}
}
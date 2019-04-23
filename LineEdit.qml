import QtQuick 2.12
import QtQuick.Controls 2.5

Item{
	property alias textInput: textInput
	property alias button: sendButton
	property alias text: textInput.text
	TextInput{
			id: textInput
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			anchors.left: parent.left
			anchors.right: sendButton.left
			anchors.rightMargin: 5
			wrapMode: TextInput.Wrap

			selectByMouse: true
			clip: true
			z:1
			leftPadding: 3
			rightPadding: 3
			verticalAlignment: Text.AlignVCenter
	}
	Rectangle{
		anchors.fill: textInput
		color: Qt.hsla(1, 1, 1, 0.7);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3
	}

	Button{
		id: sendButton
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.right: parent.right
		width: 100
		text: "Send"
	}	
	Rectangle{
		anchors.fill: sendButton
		color: Qt.hsla(0.738, 1, 0.3, 0.2);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3
	}
}

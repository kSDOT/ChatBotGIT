import QtQuick 2.12
import QtQuick.Controls 2.5

Item{
	property alias textInput: textInput
	property alias button: sendButton
	property alias text: textInput.text
	signal returnPressed(string text)
	function done(){
		returnPressed(("join #" +textInput.text))
		textInput.text = ""
	}
	TextInput{
			id: textInput
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			anchors.left: sendButton.right
			anchors.right: parent.right
			anchors.topMargin: parent.height * 1/20
			anchors.bottomMargin: parent.height * 1/20
			anchors.leftMargin: 5
			width: 200
			
			wrapMode: TextInput.Wrap
			selectByMouse: true
			clip: true
			z:1
			leftPadding: 3
			rightPadding: 3
			verticalAlignment: Text.AlignVCenter

			Keys.onEnterPressed: done();
			Keys.onReturnPressed:done();
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
		anchors.left: parent.left
		width: parent.width / 2
		text: "Join Channel:"
		onClicked: done()
	}	
	Rectangle{
		id: background
		anchors.fill: sendButton
		color: Qt.hsla(0.738, 1, 0.3, 0.2);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3
	}
}

import QtQuick 2.12
import QtQuick.Controls 1.4
Item{
	signal returnPressed(string text)
	function done(){
		returnPressed(textInput.text)
	}
	property alias label: label
	property alias textInput: textInput
	/*Rectangle{
		anchors.fill: parent
		border.color: "green"
		z:-1
	}*/


	Label{
		id: label		
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.leftMargin: 5	
		width: parent.width/2 - anchors.leftMargin*2
	
		text: "setting"
		wrapMode: Text.Wrap
		clip: true
		leftPadding: 3
		rightPadding: 3
 		horizontalAlignment: Text.AlignHCenter
	    verticalAlignment: Text.AlignVCenter
		Rectangle{
			anchors.fill: parent
			color: Qt.hsla(0.738, 1, 0.3, 0.2);
			border.color: Qt.hsla(0.738, 1, 0.3, 1);
			border.width: 3
		}
	}
	TextInput{
		id: textInput
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.left: label.right
		anchors.leftMargin: label.anchors.leftMargin
		
		clip: true
		wrapMode: TextInput.Wrap
		selectByMouse: true
		leftPadding: 3
		rightPadding: 3
		z:1

		Keys.onEnterPressed: done();
		Keys.onReturnPressed:done();
		onFocusChanged: if(textInput.focus === false) done();
		color: "black"	
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}
	Rectangle{
		anchors.fill: textInput
		color: Qt.hsla(1, 1, 1, 0.7);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3

	}
}
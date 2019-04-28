import QtQuick 2.12
import QtQuick.Window 2.5
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
ApplicationWindow {
	id: root
	objectName: "window"
	background: Image{
			source: "Icons/Background.png"
	}

	visible:true
	width: 1080; height: 720
	signal submitCommandButtonPressed()
	signal textChanged(string msg)
	signal capabilityRequested(string command)
	signal capabilityGranted(string capability)
	signal commandReply(string reply)
	signal updateSettings(var model)

	function commandReceive(data){
		commandParser.commandReceive(data)
	}
	function dataReceived(data){
	//	textDisplay.textDisplayArea.append(data);
	textDisplay.model.append({"name": data});
     textDisplay.view.positionViewAtEnd();
	}
	function clearInputLine(){
		textInput.textInput.clear();
	}
	function setInputLineTo(input){
		textInput.text = input;
	}
	function capabilityResponse(response){
		for(var i = 0; i < popup.capabilities.count; i++)
			popup.capabilities.itemAt(i).replyMatch(response);		
	}

	Gradient{
		id: colorGradient
		GradientStop { position: 0.0; color: Qt.hsla(0.738, 1, 0.3, 0.0)}
		GradientStop { position: 0.25; color: Qt.hsla(0.738, 1, 0.3, 0.6)}
		GradientStop { position: 1.0; color: Qt.hsla(0.738, 1, 0.3, 0)}
	}
	
	TextDisplay{
		id: textDisplay
		anchors.top: parent.top
		anchors.topMargin: 20
		anchors.left: parent.left
		anchors.leftMargin: 5
		anchors.right: parent.right
		anchors.rightMargin: 5
		height:root.height  * 5 / 8 - 20
	}

	Rectangle{//middle element to space out the other 2 elements, use to display capabilites
		id: spacer
		anchors.top: textDisplay.bottom
		anchors.left: textDisplay.left 
		anchors.right: textDisplay.right
		anchors.bottom: textInput.top
		anchors.topMargin: 10
		anchors.bottomMargin: 10
		height: root.height / 4
		
		gradient: colorGradient
		//border.color: root.colorGradient
		
		CapabilitiesPopup{
			id: popup
			anchors.left: parent.left
			anchors.top: parent.top
			anchors.topMargin: width/12
			anchors.leftMargin: width/12
			width: parent.width/7
		}

		JoinChannel{
			id: joinChannel
			anchors.left: popup.right
			anchors.top: popup.top
			anchors.leftMargin: width/12
			width: popup.width  * 2
			height: popup.height
			onReturnPressed: root.commandReply(text);
		}
		Rectangle{
			id: seperator
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			width: 1
			gradient: Gradient{
					GradientStop { position: 0.0; color: Qt.hsla(0.738, 1, 0.1, 0.1)}
					GradientStop { position: 0.25; color: Qt.hsla(0.738, 1, 0.1, 0.6)}
					GradientStop { position: 1.0; color: Qt.hsla(0.738, 1, 0.1, 0)}
			}
		}
		Settings{
			id: settingsArea
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			anchors.left: seperator.right
			anchors.right: parent.right
			onUpdateSettings: root.updateSettings(model)
		}
	}

    LineEdit{
		id: textInput
		objectName: "textInput"
		anchors.bottom: parent.bottom
		anchors.left: spacer.left
		anchors.right: spacer.right
		anchors.bottomMargin: 10
		height: 50
		button.onClicked: root.submitCommandButtonPressed();
		textInput.onTextChanged: root.textChanged(textInput.text);
	}
	Command{
		id: commandParser
		onCommandReply: root.commandReply(reply);
	}
}
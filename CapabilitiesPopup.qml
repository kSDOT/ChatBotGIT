import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
Button{
	id: popupOpenButton
	text: "Capabilities"
	onClicked: popup.open()
	property alias capabilities: capabilities
	Popup{
		id: popup
		width: parent.width
		y: parent.y + parent.height
		height: layout.height
		
		contentItem: ColumnLayout{
			id: layout
			anchors.fill: parent
			spacing: 1
			Repeater{
				id: capabilities
				model: capabilitiesModel
				
				delegate: Capability{
					//anchors.horizontalCenter: popup.horizontalCenter
					Layout.preferredWidth: popup.width
	
					text: type
					command: model.command
					isSet: {
						if(index == 3) 
							capabilities.itemAt(1).isSet && capabilities.itemAt(2).isSet;
						else if(index == 4)//ALL
							capabilities.itemAt(0).isSet && capabilities.itemAt(1).isSet && capabilities.itemAt(2).isSet && capabilities.itemAt(3).isSet;
						else false;
						}
					onCapabilityRequested: root.capabilityRequested(command);
					onIsSetChanged: if(isSet == 1) root.capabilityGranted(model.type);				
				}
			}
			Item{Layout.fillHeight: true}
		}
		focus: true
		closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
	}
	
	ListModel{
		id: capabilitiesModel
		
		ListElement{
			type: "Membership"
			command: "CAP REQ :twitch.tv/membership"
		}
		ListElement{
			type: "Tags"
			command: "CAP REQ :twitch.tv/tags"
		}
		ListElement{
			type: "Commands"
			command: "CAP REQ :twitch.tv/commands"
		}
		ListElement{
			type: "Chat Rooms"
			command: "CAP REQ :twitch.tv/tags twitch.tv/commands"
		}	
		ListElement{
			type: "All"
			command: "CAP REQ :twitch.tv/membership :twitch.tv/tags :twitch.tv/commands :twitch.tv/tags twitch.tv/commands"
		}
	}
			
	Rectangle{
		id: background
		anchors.fill: popupOpenButton
		color: Qt.hsla(0.738, 1, 0.3, 0.2);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3
	}
}
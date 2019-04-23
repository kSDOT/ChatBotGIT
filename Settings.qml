import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5

Item{
	id: root
	
	property bool isExpanded: false
	signal updateSettings(var model)
	GridLayout{
		id: gridLayout
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.left: settingsButton.right
		anchors.right: parent.right
		columns:2
		visible: false
		Repeater{
			id: settingsRepeater
			model: settingsModel					
			delegate: Setting{
				Layout.fillHeight: true
				Layout.fillWidth: true
				label.text: settingsModel[index].settingName
				textInput.text: settingsModel[index].settingValue
				onReturnPressed: root.updateSettings({settingName: label.text, settingValue: textInput.text}); 			
			}
		}				
	}
	Button{
		id: settingsButton
		anchors.top: parent.top
		anchors.topMargin: 10
		onClicked: root.isExpanded = !root.isExpanded;
	}
	Rectangle{
		anchors.fill: settingsButton
		color: Qt.hsla(0.738, 1, 0.3, 0.2);
		border.color: Qt.hsla(0.738, 1, 0.3, 1);
		border.width: 3
	}
	states : [
				State{
					name: "notExpanded"
					when: (root.onIsExpandedChanged && isExpanded === false)
					PropertyChanges{ target: settingsButton; icon.source:"Icons/BackArrow.png";text:"Settings"; height: 50; anchors.rightMargin: 10}
					AnchorChanges{
						target: settingsButton;
						anchors.right: settingsArea.right; 
					}
				},
				State{
					name: "expanded"
					when: (root.onIsExpandedChanged && isExpanded === true)
					PropertyChanges{ target: settingsButton;icon.source: "Icons/ForwardArrow.png"; width: 30; height: 30;anchors.leftMargin: 3; anchors.topMargin: 3;}
				    AnchorChanges{ target: settingsButton; anchors.left: settingsArea.left}
					PropertyChanges{ target: gridLayout; visible: true}
				}
			]

			transitions:[
				Transition{
					from: "notExpanded"; to: "expanded"
					
					AnchorAnimation{ duration: 1000; easing.type: Easing.InOutQuad;  }
					NumberAnimation{ 
						target: settingsButton; 
						properties:"anchors.topMargin, height, width";
						duration: 1000;
						easing.type: Easing.InOutQuad;
					}

				},
				Transition{
					from: "expanded"; to: "notExpanded"
					SequentialAnimation{
						AnchorAnimation{ duration: 1000;  easing.type: Easing.InOutQuad;  }
						PropertyAction{target: gridLayout; property: "visible"; value: "false"}
					}
					NumberAnimation{ 
						target: settingsButton; 
						properties:"anchors.topMargin, height, width";
						duration: 1000;
						easing.type: Easing.InOutQuad;
					}
				}
			]
}

import QtQuick 2.12
import QtQuick.Controls 2.12

Flickable{
	id: textDisplay

	property alias textDisplayArea : textDisplayArea
	contentHeight: textDisplayArea.height
	clip: true
	boundsMovement: Flickable.StopAtBounds
	boundsBehavior: Flickable.StopAtBounds

	   ScrollBar.vertical: ScrollBar {
		   id: vBar
           active: true
		   contentItem: Rectangle{
				 color: vBar.pressed? Qt.hsla(0.738, 1, 0.3, 1) : Qt.hsla(0.738, 1, 0.1, 1);
				  implicitWidth: 6
				  implicitHeight: 100
				  radius: width / 2
		   }
           onActiveChanged:  if (!active) active = true;		
       }

	 /*ScrollBar.horizontal: ScrollBar {//word wrap enabled
		   id: hBar
          active: true
		   contentItem: Rectangle{
				 color: hBar.pressed? Qt.hsla(0.738, 1, 0.3, 1) : Qt.hsla(0.738, 1, 0.1, 1);
				  implicitHeight: 6
				  implicitWidth: 100
				  radius: height / 2
		   }
           onActiveChanged:  if (!active) active = true;		
       }*/



	TextArea.flickable:	TextArea {
		 id:  textDisplayArea
		 //maximumBlockCount: 5000
		background: Rectangle{
			color: Qt.hsla(1, 1, 1, 0.7);
			border.color: Qt.hsla(0.738, 1, 0.3, 1);
			border.width: 3
		}
		readOnly: true
		selectByMouse: true
		wrapMode: Text.WordWrap
		font.weight: Font.Medium
		font.pointSize: 12
		color: "Black"
		clip: true
		MouseArea{
			anchors.fill: parent
			propagateComposedEvents: true
			acceptedButtons: Qt.MidButton
			onWheel: {
				if(wheel.modifiers & Qt.ControlModifier){ //ctrl + wheel
					if(wheel.angleDelta.y > 0)
						textDisplayArea.font.pointSize++;
					else if (wheel.angleDelta.y < 0)
						textDisplayArea.font.pointSize--;
				}
				else
					wheel.accepted = false;//pass for other events
			}
		}
	}
}
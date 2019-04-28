import QtQuick 2.12
import QtQuick.Controls 2.12
Rectangle{
   id: frame
   property alias model: model
   property alias view: textDisplay

   color: Qt.hsla(1, 1, 1, 0.7);
   border.color: Qt.hsla(0.738, 1, 0.3, 1);
   border.width: 3

	ListView{
		id: textDisplay
		anchors.fill: parent
		anchors.margins: 3
		boundsMovement: Flickable.StopAtBounds
		boundsBehavior: Flickable.StopAtBounds
		clip: true
	
		property real scale: 1
	    
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

	   	onCountChanged: console.log(count)
		ListModel { id: model}
		Component{	 
			id:  delegate
			Text{
				text: name
				font.weight: Font.Medium
				font.pointSize: 12 * textDisplay.scale
				color: "Black"	
				wrapMode: Text.WordWrap
				width: parent.width
			}		
		}

		model: model
		delegate: delegate

		MouseArea{
			anchors.fill: parent
			propagateComposedEvents: true
			acceptedButtons: Qt.MidButton
			onWheel: {
				if(wheel.modifiers & Qt.ControlModifier){ //ctrl + wheel
					if(wheel.angleDelta.y > 0)
						textDisplay.scale+= 0.1;
					else if (wheel.angleDelta.y < 0)
						textDisplay.scale-= 0.1;
				}
				else
					wheel.accepted = false;//pass for other events
			}
		}
	}
}
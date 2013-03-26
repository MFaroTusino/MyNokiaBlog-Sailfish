import QtQuick 1.1
import Sailfish.Silica 1.0

Rectangle {
    anchors.fill: parent
    color: black
    Image {
        anchors.centerIn: parent
        id: coverImage
        source: "/home/nemo/Pictures/5.jpg" //featured image from post
    }
    
    Label {
        id: label
        color: theme.highlightColor
        font.pixelSize: theme.fontSizeLarge
        anchors.left: parent.left
        text: "Most Recent Post Title"
        wrapMode: Text.Wrap
        width: parent.width
    }
    
    CoverActionList {
        id: coverAction
        
        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: coverImage.source="/home/nemo/Pictures/mnb.png"
        }
    }
}



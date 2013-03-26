import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    id: page
    Column {
    width: page.width
    spacing: theme.paddingLarge
    PageHeader {
        title: "Changelog"
    }
    Flickable {
               id: flickArea
                anchors.fill: parent
                contentWidth: parent.width; contentHeight: parent.height
                flickableDirection: Flickable.VerticalFlick
                clip: false
                    TextArea {
                         readOnly: true
                         width: parent.width
                         anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                         text: CHANGELOG
                         wrapMode: Text.Wrap
                         color: theme.primaryColor
                         font.pixelSize: theme.fontSizeLarge
    }
    }
}
}

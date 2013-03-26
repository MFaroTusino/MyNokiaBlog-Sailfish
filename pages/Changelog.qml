import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    id: page
    onStatusChanged: {
        if (status == PageStatus.Inactive) {
            flickArea.contentY = 0
        }
    }

    PageHeader {
        id: pageHeader
        title: "Changelog"
    }
    Flickable {
        id: flickArea
        anchors.top: pageHeader.bottom; anchors.bottom: page.bottom
        anchors.left: page.left; anchors.leftMargin: theme.paddingLarge
        anchors.right: page.right; anchors.rightMargin: theme.paddingMedium
        contentWidth: flickArea.width; contentHeight: textArea.height
        flickableDirection: Flickable.VerticalFlick
        clip: true
        TextArea {
            id: textArea
            readOnly: true
            width: flickArea.width
            text: CHANGELOG
            wrapMode: Text.Wrap
            color: theme.primaryColor
            font.pixelSize: theme.fontSizeLarge
        }
    }
}

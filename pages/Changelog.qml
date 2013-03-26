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
    TextArea {
        readOnly: true
        width: parent.width
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: CHANGELOG
        wrapMode: Text.Wrap
        color: theme.secondaryHighlightColor
        font.pixelSize: theme.fontSizeLarge
    }
}
}

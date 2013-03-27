import QtQuick 1.1
import Sailfish.Silica 1.0
import BlogViewer 1.0

Page {
    id: page
    property Post post

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: flickable.width

            PageHeader {
                title: qsTr("Article")
            }

            Item {
                width: parent.width
                height: label.height + 2 * theme.paddingMedium

                Label {
                    id: label
                    anchors.left: parent.left; anchors.leftMargin: theme.paddingMedium
                    anchors.right: parent.right; anchors.rightMargin: theme.paddingMedium
                    anchors.top: parent.top; anchors.topMargin: theme.paddingMedium
                    text: post.content
                    wrapMode: Text.WordWrap
                 }
            }

        }

    }


}

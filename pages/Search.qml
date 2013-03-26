import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: "About"
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem{
                text: "Recent Posts"
                onClicked: pageStack.push(Qt.resolvedUrl("Index.qml"))
            }
            MenuItem{
                text: "Search"
                //No onClicked as this causes recursive browsing
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: childrenRect.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            width: page.width
            spacing: theme.paddingLarge
            PageHeader {
                title: "Search"
            }
            Label {
                anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                text: "Hello Sailors"
                color: theme.secondaryHighlightColor
                font.pixelSize: theme.fontSizeLarge
            }
        }
    }
}



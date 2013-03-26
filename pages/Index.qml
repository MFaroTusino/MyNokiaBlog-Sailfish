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
                text: "Refresh posts"
               // onClicked: //refresh()
            }
            MenuItem{
                text: "Search"
                onClicked: pageStack.push(Qt.resolvedUrl("Search.qml"))
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
                title: "Recent Posts"
            }
            Label { 
                anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                text: "List of recent posts go here"
                color: theme.secondaryHighlightColor
                font.pixelSize: theme.fontSizeLarge
            }
        }
    }
}



import QtQuick 1.1
import Sailfish.Silica 1.0
import BlogViewer 1.0

Page {
    id: page

    PostModel {
        id: postModel
        Component.onCompleted: load("http://unleashthephones.com/api/get_recent_posts/")
        onErrorChanged: console.debug(error)
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView {
        id: view
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Recent Posts")
        }
        model: postModel
        delegate: BackgroundItem {
            onClicked: pageStack.push(Qt.resolvedUrl("PostPage.qml"), {post: model.post})

            Label {
                textFormat : Text.RichText
                anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                anchors.right: parent.right; anchors.rightMargin: theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                text: model.post.title
                truncationMode: TruncationMode.Fade
            }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem{
                text: qsTr("Search")
                onClicked: pageStack.push(Qt.resolvedUrl("Search.qml"))
            }
            MenuItem{
                text: qsTr("Reload")
                onClicked: postModel.load("http://unleashthephones.com/api/get_recent_posts/")
            }
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("More")
                onClicked: postModel.loadMore("http://unleashthephones.com/api/get_recent_posts/")
            }

            MenuItem {
                text: qsTr("Back to top")
                onClicked: view.scrollToTop()
            }
        }

        VerticalScrollDecorator {flickable: view}
    }
}



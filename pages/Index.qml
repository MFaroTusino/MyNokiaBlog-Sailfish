import QtQuick 1.1
import Sailfish.Silica 1.0
import BlogViewer 1.0

Page {
    id: page

    PostModel {
        id: postModel
        api: "http://unleashthephones.com/api"
        method: "get_recent_posts"
        Component.onCompleted: load()
        onErrorChanged: console.debug(error)
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView {
        id: view
        anchors.fill: parent
        interactive: !postModel.loading
        opacity: !postModel.loading ? 1 : 0.5
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
                onClicked: postModel.load()
            }
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("More")
                onClicked: postModel.loadMore()
            }

            MenuItem {
                text: qsTr("Back to top")
                onClicked: view.scrollToTop()
            }
        }

        VerticalScrollDecorator {flickable: view}
    }

    ProgressCircle {
        id: progress
        visible: postModel.loading
        anchors.centerIn: parent
        value: postModel.progress
        onVisibleChanged: {
            progress.value = 0
        }

        Timer {
            interval: 16
            repeat: true
            running: progress.visible
            onTriggered: progress.value = (progress.value + 0.005) % 1.0
        }
    }
}



import QtQuick 1.1
import Sailfish.Silica 1.0
import BlogViewer 1.0

Page {
    id: page
    property Post post

// onPostChanged: console.debug(post.content)

    TextArea {
        readOnly: true
        anchors.fill: parent
        text: post.content
     }
}

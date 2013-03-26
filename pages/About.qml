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
                //No onClicked action as this would cause recusrive browsing
            }
            MenuItem{
                text: "Recent Posts"
                onClicked: pageStack.push(Qt.resolvedUrl("Index.qml"))
            }

            MenuItem{
                text: "Search"
                onClicked: pageStack.push(Qt.resolvedUrl("Search.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: childrenRect.height

    ListModel {
        id: modelContacts
        ListElement {
            elementID: "twitter"
            service: "Twitter"
            second: "@MFaroTusino"
            url: "https://twitter.com/MFaroTusino"

        }
        ListElement {
            elementID: "email"
            service: "Email"
            second: "email"
            url: "mailto://mfaro-tusino@live.com"

        }
    }
    ListModel {
        id: modelThanks
        ListElement{
            elementID: "Lucien"
            name: "Lucien Xu"
            twitter: "@SfietKonstantin"
            url: "http://twitter/sfietkonstantin"
        }
    }

    PageHeader {
        id: header
        title: qsTr("About")
    }

    Label {
        id: createdBy
        anchors.top: header.bottom
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: qsTr("Created by: ")
        color: theme.primaryColor
        font.pixelSize: theme.fontSizeLarge
    }
    Label {
        id: creator
        anchors.top: createdBy.bottom; anchors.topMargin: theme.paddingSmall
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: "Michael Faro-Tusino"
        color: theme.highlightColor
        font.pixelSize: theme.fontSizeSmall
    }
    Label {
        id: version
        anchors.top: creator.bottom; anchors.topMargin: theme.paddingLarge
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: qsTr("Version:")
        color: theme.primaryColor
        font.pixelSize: theme.fontSizeLarge
    }

   Label {
        id: versionNumber
        anchors.top: version.bottom; anchors.topMargin: theme.paddingSmall
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: "0.0.1~a1"
        color: theme.highlightColor
        font.pixelSize: theme.fontSizeSmall
        MouseArea { anchors.fill: versionNumber; onClicked: pageStack.push(Qt.resolvedUrl("Changelog.qml"))}
    }


    Label {
        id: contactUs
        anchors.top: versionNumber.bottom; anchors.topMargin: theme.paddingLarge
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: qsTr("Contact us")
        color: theme.primaryColor
        font.pixelSize: theme.fontSizeLarge
    }

    Column {
        id: contacts
        width: page.width
        anchors.top: contactUs.bottom
        Repeater {
            model: modelContacts
            delegate: BackgroundItem {
                id: contactsBackground
                width: page.width
                onClicked: Qt.openUrlExternally(model.url)

                Label {
                    id: contactLabel
                    anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter
                    text: contactsBackground.pressed ? model.second : model.service
                    color: theme.highlightColor

                }
            }
        }
    }

    Label{
        id: specialThanks
        anchors.top: contacts.bottom
        anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
        text: qsTr("Special Thanks")
        color: theme.primaryColor
        font.pixelSize: theme.fontSizeLarge
    }

    Column {
        id: thanks
        width: page.width
        anchors.top: specialThanks.bottom
        Repeater {
            model: modelThanks
            delegate: BackgroundItem {
                id: thanksBackground
                width: page.width
                onClicked: Qt.openUrlExternally(model.url)

                Label {
                    id: thanksLabel
                    anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter
                    text: thanksBackground.pressed ? model.twitter : model.name
                    color: theme.highlightColor

                }
            }
        }
    }
}
}

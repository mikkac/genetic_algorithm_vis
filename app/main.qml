import QtQuick
import QtQuick.Controls 6.3

Window {
    id: window
    width: 1024
    height: 720
    visible: true
    title: qsTr("Genetic Algorithm Visualization")

    Row {
        id: row
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: rectangle
            width: 700
            color: "#c73939"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            anchors.bottomMargin: 0
        }
        Column {
            id: column
            width: 200
            height: 400
            leftPadding: 10
            topPadding: 30
            spacing: 10

            Label {
                id: label1
                text: qsTr("Options")
                font.family: "Ubuntu"
                font.pointSize: 20
                font.bold: true
            }

            Grid {
                id: grid
                width: 200
                height: 400
                spacing: 20
                verticalItemAlignment: Grid.AlignVCenter
                horizontalItemAlignment: Grid.AlignHCenter
                columns: 2

                Label {
                    id: label
                    text: qsTr("Label")
                }

                Button {
                    id: button
                    text: qsTr("Button")
                }
            }
        }
    }
}

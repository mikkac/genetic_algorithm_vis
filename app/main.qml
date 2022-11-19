import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts
import QtCharts 2.4

Window {
    id: window
    width: 1024
    height: 720
    visible: true
    title: qsTr("Genetic Algorithm Visualization")
    property bool lightTheme: true
    Material.theme: lightTheme ? Material.Light : Material.Dark
    Material.background: lightTheme ? backgroundGray : backgroundBlue
    Material.foreground: lightTheme ? "black" : "white"
    Material.accent: Material.Blue
    Material.primary: lightTheme ?  lightGray : darkBlue
    readonly property int minimumWidth: 1280
    readonly property int minimumHeight: 1024
    readonly property int headerHeight: 100
    readonly property int sideMargin: 100

    // Common colors
    readonly property color noVideoColor: "#1A1E22"
    readonly property color mainAccent: "#FFAB91"

    // Dark theme
    readonly property color backgroundBlue: "#343B4D"
    readonly property color darkBlue: "#222834"

    // Light theme
    readonly property color backgroundGray: "#f2efed"
    readonly property color lightGray: "#bdbdbd"

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: 0

        ChartView {
            title: "Line"
            width: 640
            height: 480
            antialiasing: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            theme: ChartView.ChartThemeBlueNcs

            LineSeries {
                name: "LineSeries"
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1.1; y: 2.1 }
                XYPoint { x: 1.9; y: 3.3 }
                XYPoint { x: 2.1; y: 2.1 }
                XYPoint { x: 2.9; y: 4.9 }
                XYPoint { x: 3.4; y: 3.0 }
                XYPoint { x: 4.1; y: 3.3 }
            }
        }
        ColumnLayout {
            id: column
            width: 200
            height: 400
            Layout.bottomMargin: 2
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 10
            Label {
                id: label1
                text: qsTr("Genetic Algorithm")
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                font.family: "Ubuntu"
                font.pointSize: 20
                font.bold: true
            }
            Grid {
                id: grid
                width: 200
                height: 400
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
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
                    width: 130
                    text: qsTr("START")
                    highlighted: true
                    flat: false
                }

                Label {
                    id: label2
                    text: qsTr("Label")
                }

                Slider {
                    id: slider
                    wheelEnabled: true
                    value: 0.5
                }
            }

        }
    }
}

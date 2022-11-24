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
    Material.primary: lightTheme ? lightGray : darkBlue
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

        Connections {
            target: AlgorithmDataModel
            function onDataChanged() {
                console.log(AlgorithmDataModel.data.length)
                lineSeries.removePoints(0, lineSeries.count)
                for (var i = 0; i < AlgorithmDataModel.data.length; i++) {
                    lineSeries.append(AlgorithmDataModel.data[i].x,
                                      AlgorithmDataModel.data[i].y)
                    console.log(AlgorithmDataModel.data[i].x,
                                AlgorithmDataModel.data[i].y)
                }
            }
        }

        ChartView {
            id: chartView
            width: 640
            height: 480
            antialiasing: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            theme: ChartView.ChartThemeBlueNcs

            ValueAxis {
                id: axisY
                min: 0
                max: 300000
                gridVisible: true
            }

            ValueAxis {
                id: axisX
                min: 0
                max: 300
                gridVisible: true
                tickCount: 5
            }

            LineSeries {
                id: lineSeries
                name: "signal 1"
                axisX: axisX
                axisY: axisY
            }
        }

        ColumnLayout {
            id: column
            width: 200
            height: 600
            visible: true
            clip: false
            Layout.bottomMargin: 2
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 30
            Label {
                id: label1
                width: 200
                text: qsTr("Genetic Algorithm")
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.family: "Ubuntu"
                font.pointSize: 20
                font.bold: true
            }
            Button {
                id: button
                width: 200
                text: qsTr("START")
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                highlighted: true
                flat: false
                onClicked: AlgorithmDataModel.slotGenerateData()
            }

            Row {
                id: row1
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.fillHeight: false
                Label {
                    id: label2
                    text: qsTr("Step (s)")
                    //                    anchors.verticalCenter: parent.verticalCenter
                    clip: false
                }

                Slider {
                    id: slider
                    width: 180
                    //                    anchors.verticalCenter: parent.verticalCenter
                    //                    anchors.right: parent.right
                    //                    anchors.rightMargin: 0
                    wheelEnabled: true
                    value: 0.5
                }
            }
        }
    }
}

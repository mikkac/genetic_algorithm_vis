import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts
import QtCharts 2.4

ApplicationWindow {
    id: window
    readonly property int minimumWidth: 1024
    readonly property int minimumHeight: 720
    width: minimumWidth
    height: minimumHeight
    visible: true
    title: qsTr("Genetic Algorithm Visualization")

    Material.theme: Material.Light
    Material.accent: Material.Blue

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: 0

        Connections {
            target: AlgorithmDataModel
            function onSignalDataChanged() {
                runButton.enabled = true
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
            animationOptions: ChartView.AllAnimations
            LineSeries {
                id: serie1

                axisX: ValueAxis {
                    id: xAxis
                    min: AlgorithmDataModel.xMin
                    max: AlgorithmDataModel.xMax
                }

                axisY: ValueAxis {
                    id: yAxis
                    min: AlgorithmDataModel.yMin
                    max: AlgorithmDataModel.yMax
                }

                VXYModelMapper {
                    id: mapper
                    series: serie1
                    xColumn: 0
                    yColumn: 1
                    model: AlgorithmDataModel
                    Component.onCompleted: console.log("loaded VXYModelMapper: xColumn " + mapper.xColumn + " yColumn " + mapper.yColumn)
                }
            }

            //            ValueAxis {
            //                id: axisY
            //                min: 0
            //                max: 300000
            //                gridVisible: true
            //                tickCount: 10
            //            }

            //            ValueAxis {
            //                id: axisX
            //                min: 0
            //                max: 300
            //                gridVisible: true
            //                tickCount: 10
            //            }

            //            VXYModelMapper {
            //                id: mapper
            //                xColumn: 0
            //                yColumn: 1
            //                model: chartModel
            //            }

            //            LineSeries {
            //                id: lineSeries
            //                name: "signal 1"
            //                axisX: axisX
            //                axisY: axisY
            //            }
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
                id: runButton
                width: 200
                text: qsTr("START")
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                highlighted: true
                flat: false
                onClicked: {
                    runButton.enabled = false
                    AlgorithmController.slotRunAlgorithm()
                }
            }

            RowLayout {
                id: row1
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.fillHeight: false
                Label {
                    id: label2
                    text: qsTr("Step (s)")
                    Layout.fillWidth: true
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
                    Layout.fillWidth: true
                    value: 0.5
                }
            }
        }
    }
}

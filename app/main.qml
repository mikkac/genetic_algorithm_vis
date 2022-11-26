import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts
import QtCharts 2.4

Window {
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
                runButton.text = "Start"
            }
        }

        ChartView {
            id: chartView
            title: "Results"
            width: 640
            height: 480
            antialiasing: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            theme: ChartView.ChartThemeBlueNcs
            animationOptions: ChartView.AllAnimations
            LineSeries {
                id: avg
                name: "Avg"

                axisX: ValueAxis {
                    id: avgXAxis
                    titleText: "Steps"
                    min: AlgorithmDataModel.xMin
                    max: AlgorithmDataModel.xMax
                }

                axisY: ValueAxis {
                    id: avgYAxis
                    titleText: "Estimation Function Value"
                    min: AlgorithmDataModel.yMin
                    max: AlgorithmDataModel.yMax
                }

                VXYModelMapper {
                    id: avgMapper
                    series: avg
                    xColumn: 0
                    yColumn: 1
                    model: AlgorithmDataModel
                }
            }

            LineSeries {
                id: min
                name: "Min"

                VXYModelMapper {
                    id: minMapper
                    series: min
                    xColumn: 0
                    yColumn: 2
                    model: AlgorithmDataModel
                }
            }

            LineSeries {
                id: max
                name: "Max"

                VXYModelMapper {
                    id: maxMapper
                    series: max
                    xColumn: 0
                    yColumn: 3
                    model: AlgorithmDataModel
                }
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
                id: runButton
                width: 300
                text: qsTr("START")
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                highlighted: true
                flat: false
                onClicked: {
                    runButton.enabled = false
                    runButton.text = "Running..."
                    var populationSize = parseInt(populationInput.text)
                    var steps = parseInt(stepsInput.text)
                    var initialMin = parseInt(initialMinInput.text)
                    var initialMax = parseInt(initialMaxInput.text)
                    var mutationProbability = parseFloat(mutationProbInput.text)
                    var mutationBits = parseInt(mutationBitsInput.text)
                    var crossPos = parseInt(crossPosInput.text)
                    console.log(populationSize, steps, mutationProbability,
                                mutationBits, crossPos)
                    AlgorithmController.slotRunAlgorithm(populationSize, steps,
                                                         initialMin,
                                                         initialMax,
                                                         mutationProbability,
                                                         mutationBits, crossPos)
                }
            }

            GridLayout {
                id: configGrid
                columns: 2
                Layout.rightMargin: 30
                Layout.leftMargin: 30
                Layout.fillWidth: true
                Layout.fillHeight: false
                Label {
                    id: populationLabel
                    text: qsTr("Population size")
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: populationInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "100"
                }

                Label {
                    id: initialMinLabel
                    text: "Initial min. value"
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: initialMinInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "0"
                }

                Label {
                    id: initialMaxLabel
                    text: "Initial max. value"
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: initialMaxInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "10"
                }

                Label {
                    id: stepsLabel
                    text: qsTr("Steps")
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: stepsInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: qsTr("300")
                }

                Label {
                    id: mutationProbLabel
                    text: qsTr("Mutation probability")
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: mutationProbInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "0.01"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }

                Label {
                    id: mutationBitsLabel
                    text: qsTr("Number of mutated bits")
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: mutationBitsInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "4"
                }

                Label {
                    id: crossPosLabel
                    text: qsTr("Crossing position")
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    clip: false
                }

                TextField {
                    id: crossPosInput
                    width: 50
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "8"
                }
            }
        }
    }
}

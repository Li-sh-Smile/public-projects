import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick 2.12

Column {
    id: element
    MyMeter{
        id: myMeter
        maxValue: seeepSlider.maximumValue
        minValue: seeepSlider.minimumValue
        currentSpeed: seeepSlider.value
        currentOilQuantity: oilSlider.value
        currentWaterTemperature: waterTemperatureSlider.value+20
    }

    Item {
        height: 30
        anchors.right: myMeter.right
        anchors.left: myMeter.left
        Text {
            id: seeep
            text: qsTr("表速 ")+seeepSlider.value
            font.pointSize: 13
            anchors.verticalCenter: parent.verticalCenter
        }
        Slider {
            id: seeepSlider
            x: 100
            width: parent.width - 100
            height: 30
            stepSize: 1
            value: 5000
            maximumValue: 10000
            minimumValue: 0
        }
    }
    Item {
        height: 30
        anchors.right: myMeter.right
        anchors.left: myMeter.left
        Text {
            id: oil
            text: qsTr("油量 ")+oilSlider.value
            font.pointSize: 13
            anchors.verticalCenter: parent.verticalCenter
        }
        Slider {
            id: oilSlider
            x: 100
            width: parent.width - 100
            height: 30
            stepSize: 1
            value: 50
            maximumValue: 100
            minimumValue: 0
        }
    }
    Item {
        height: 30
        anchors.right: myMeter.right
        anchors.left: myMeter.left
        Text {
            id: waterTemperature
            text: qsTr("水温 ")+waterTemperatureSlider.value
            font.pointSize: 13
            anchors.verticalCenter: parent.verticalCenter
        }
        Slider {
            id: waterTemperatureSlider
            x: 100
            width: parent.width - 100
            height: 30
            stepSize: 1
            value: 50
            maximumValue: 100
            minimumValue: -20
        }
    }

    Row{
        Button{
            text: qsTr("无挡位")
            onClicked: myMeter.currenGear = -1
        }

        Button {
            text: qsTr("P档驻车")
            onClicked: myMeter.currenGear = 0
        }

        Button {
            text: qsTr("R档后退")
            onClicked: myMeter.currenGear = 1
        }

        Button {
            text: qsTr("N档空挡")
            onClicked: myMeter.currenGear = 2
        }

        Button {
            text: qsTr("D档前进")
            onClicked: myMeter.currenGear = 3
        }
    }
}











































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

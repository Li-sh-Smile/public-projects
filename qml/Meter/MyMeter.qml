import QtQuick 2.12

import "./DrawFun.js" as DrawFun

Rectangle {
    width: 400
    height: 400
    border.width: 2
    border.color: "gray"
    property real maxValue: 10000
    property real minValue: 0
    property real startAngle: 0.75
    property real endAngle: 0.25
    property real currentAngle: value/(maxValue-minValue)*2*0.75+startAngle
    property real value: 10000

    property int centreX : width/2
    property int centreY : height/2

    //速度
    property real currentSpeed: 10000
    //挡位
    property int currenGear: 1
    //油量
    property int currentOilQuantity: 100
    //水温
    property int currentWaterTemperature: 100

    onCurrentAngleChanged: canvas.requestPaint()
    onCurrenGearChanged: canvas.requestPaint()
    onCurrentOilQuantityChanged: canvas.requestPaint()
    onCurrentWaterTemperatureChanged: canvas.requestPaint()
    onCurrentSpeedChanged: {
        animationTimeAnimation.stop()
        animationTimeAnimation.from = value
        animationTimeAnimation.to = currentSpeed
        animationTimeAnimation.duration = Math.abs(currentSpeed - value)/(maxValue-minValue)*250    //250ms最小到最到动作时间
        animationTimeAnimation.start()
    }

    NumberAnimation on value {
        id: animationTimeAnimation
        from: currentSpeed
        to: currentSpeed
        duration: 50
        loops: 1//Animation.Infinite
        //running: true
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");


            ctx.clearRect(0, 0, width, height); //清除所有内容
            ctx.reset();

            //绘制背景12，4，36
            ctx.fillStyle = "rgb(12,4,36)";
            ctx.fillRect(0, 0, width, height);

            //绘制刻度盘
            DrawFun.drawDial(ctx);
            //绘制当前环
            DrawFun.drawCurrentRing(ctx);
            //绘制挡位
            DrawFun.drawGear(ctx);
            //绘制指针
            DrawFun.drawPointer(ctx);
            //绘制油量
            DrawFun.drawOilQuantity(ctx);
            //绘制水温
            DrawFun.drawWaterTemperature(ctx);

        }

    }
    Text {
        text: parent.currentSpeed
        font.bold: true
        font.pointSize: parent.height/12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/5
        verticalAlignment: Text.AlignTop
        color: "red"
    }
}


//绘制环形背景
function drawDial(ctx){
    ctx.beginPath()
    ctx.lineWidth = centreX/25;
    ctx.strokeStyle = "rgb(34,39,146)"

    //设置渐变颜色
    var linearGradient= ctx.createRadialGradient(centreX,centreY,width / 2.5+2,centreX,centreY,width / 2.5+ctx.lineWidth+2);
    linearGradient.addColorStop(0,"rgba(34,39,146,0)")
    linearGradient.addColorStop(0.5,"rgb(68,78,200)")
    linearGradient.addColorStop(1,"rgba(34,39,146,0)")
    ctx.strokeStyle=linearGradient;

    ctx.arc(centreX, centreY, width / 2.5+ctx.lineWidth/2+2, Math.PI * 0.75, Math.PI * 0.25, false);
    ctx.stroke();
    ctx.closePath();
}

//当前环形角度
function drawCurrentRing(ctx){
    ctx.beginPath();
    ctx.lineWidth = centreX/8;
    ctx.strokeStyle = "black"
    //设置渐变颜色
    var linearGradient= ctx.createRadialGradient(centreX,centreY,width / 2.5-ctx.lineWidth,centreX,centreY,width / 2.5);
    linearGradient.addColorStop(0,"blue")
    linearGradient.addColorStop(1,"red")
    ctx.strokeStyle=linearGradient;
    ctx.arc(centreX, centreY, width / 2.5-ctx.lineWidth/2, Math.PI * startAngle, Math.PI * (currentAngle>2?currentAngle-2:currentAngle), false);
    ctx.stroke();
    ctx.closePath();
    //console.log(startAngle,currentAngle)
}

//绘制指针
function drawPointer(ctx){
    ctx.save();
    //设置原点
    ctx.translate(centreX,centreY);
    //设置旋转角度
    ctx.rotate(Math.PI / 180 * (135+180*(currentAngle-startAngle)));

    //设置渐变颜色
    var linearGradient= ctx.createLinearGradient(0,-10,centreX/1.5*0.95,20);
    linearGradient.addColorStop(0,"blue")
    linearGradient.addColorStop(1,"red")
    ctx.fillStyle=linearGradient;

    //绘制指针
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(centreX/1.5*0.3, 0+10);
    ctx.lineTo(centreX/1.5*0.95, 0);
    ctx.lineTo(centreX/1.5*0.3, 0-10);

    //填充
    ctx.fill();
    ctx.closePath();
    ctx.restore();
}

//绘制挡位
function drawGear(ctx){

    ctx.lineWidth = centreY/15;
    ctx.beginPath();
    ctx.strokeStyle = currenGear===3?"#596DFF":"#232D6B";
    ctx.arc(centreX, centreY, width / 2.7, Math.PI * 0.31, Math.PI * 0.39, false);
    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();
    ctx.strokeStyle = currenGear===2?"#596DFF":"#232D6B";
    ctx.arc(centreX, centreY, width / 2.7, Math.PI * 0.41, Math.PI * 0.49, false);
    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();
    ctx.strokeStyle = currenGear===1?"#596DFF":"#232D6B";
    ctx.arc(centreX, centreY, width / 2.7, Math.PI * 0.51, Math.PI * 0.59, false);
    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();
    ctx.strokeStyle = currenGear===0?"#596DFF":"#232D6B";
    ctx.arc(centreX, centreY, width / 2.7, Math.PI * 0.61, Math.PI * 0.69, false);
    ctx.stroke();
    ctx.closePath();



    ctx.beginPath();
    ctx.font = centreX/10+"px sans-serif"
    ctx.fillStyle = currenGear===0?"#596DFF":"#232D6B";
    ctx.fillText("P",centreX-centreX*0.33,centreY+centreY*0.6);
    ctx.fillStyle = currenGear===1?"#596DFF":"#232D6B";
    ctx.fillText("R",centreX-centreX*0.15,centreY+centreY*0.67);
    ctx.fillStyle = currenGear===2?"#596DFF":"#232D6B";
    ctx.fillText("N",centreX+centreX*0.07,centreY+centreY*0.67);
    ctx.fillStyle = currenGear===3?"#596DFF":"#232D6B";
    ctx.fillText("D",centreX+centreX*0.27,centreY+centreY*0.6);
    ctx.closePath();
}

//绘制油量
function drawOilQuantity(ctx){
    var startAngle = 0.0
    var endAngle = 0.0
    var i = 0

    //画背景格
    for(i=0;i<5;i++){
        startAngle = Math.PI * 0.6 + Math.PI * (i*(0.4/5))
        endAngle = startAngle + Math.PI * (0.4/5/1.1)
        ctx.lineWidth = centreX/15;
        ctx.strokeStyle = "rgb(34,39,146)"
        ctx.beginPath()
        ctx.arc(centreX, centreY, width / 2.2, startAngle, endAngle, false);
        ctx.stroke();
        ctx.closePath();
    }

    //画当前油量
    for(i=0;i<5;i++){
        startAngle = Math.PI * 0.6 + Math.PI * (i*(0.4/5))
        if(currentOilQuantity-i*20 <= 20)
            endAngle = startAngle + Math.PI * (0.4/5/1.1)*((currentOilQuantity-i*20)/20)
        else
            endAngle = startAngle + Math.PI * (0.4/5/1.1)

        ctx.lineWidth = centreX/15;
        if(currentOilQuantity < 30)
            ctx.strokeStyle = "red"
        else
            ctx.strokeStyle = "rgb(89,190,255)"

        ctx.beginPath()
        ctx.arc(centreX, centreY, width / 2.2, startAngle, endAngle, false);
        ctx.stroke();
        ctx.closePath();

        if(currentOilQuantity-i*20 <= 20)
            break;
    }
}

//绘制水温
function drawWaterTemperature(ctx){
    var startAngle = 0.0
    var endAngle = 0.0
    var i = 0

    //画背景格
    for(i=0;i<6;i++){
        endAngle = Math.PI * 0.4 - Math.PI * (i*(0.4/6))
        startAngle = endAngle - Math.PI * (0.4/6/1.1)
        ctx.lineWidth = centreX/15;
        ctx.strokeStyle = "rgb(34,39,146)"
        ctx.beginPath()
        ctx.arc(centreX, centreY, width / 2.2, startAngle, endAngle, false);
        ctx.stroke();
        ctx.closePath();
    }

    //画当前水温
    for(i=0;i<6;i++){
        endAngle = Math.PI * 0.4 - Math.PI * (i*(0.4/6))
        if(currentWaterTemperature-i*20 <= 20)
            startAngle = endAngle - Math.PI * (0.4/6/1.1)*((currentWaterTemperature-i*20)/20)
        else
            startAngle = endAngle - Math.PI * (0.4/6/1.1)


        ctx.lineWidth = centreX/15;
        if(currentWaterTemperature > 100)
            ctx.strokeStyle = "red"
        else
            ctx.strokeStyle = "rgb(89,190,255)"

        ctx.beginPath()
        ctx.arc(centreX, centreY, width / 2.2, startAngle, endAngle, false);
        ctx.stroke();
        ctx.closePath();

        if(currentWaterTemperature-i*20 <= 20)
            break;
    }
}

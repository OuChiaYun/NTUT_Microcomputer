const express = require("express");
const app = express();

app.use(express.static('./public'));

app.get("/index", (req, res) => {
    controLED(req.query.LED, req.query.POWER, req.query.TIME)
    var _ck = ['','','',''];

if( (req.query.LED) !=' ' ){
    for (var i = 0; i < 4; i += 1)
    {
        if(req.query.LED[i] == 'LED1'){
            _ck[0] = 'checked';
        }
        if(req.query.LED[i] == 'LED2'){
            _ck[1] = 'checked';
        }
        if(req.query.LED[i] == 'LED3'){
            _ck[2] = 'checked';
        }
        if(req.query.LED[i] == 'LED4'){
            _ck[3] = 'checked';
        }
    }
}

var _POWER = ['','']
if(req.query.POWER != ''){
    if(req.query.POWER == 'on'){
        _POWER[0] ='checked';
    }else{
        _POWER[1] ='checked';
    }
}

var _TIME = ''
var _MODE = ''
if(req.query.TIME != ''){
    _TIME = 'value = "'+ req.query.TIME+'"'
    _MODE = 'Mode_Shine : ' + req.query.TIME;
}



    const dynamicContent = 
'</head ><body><p><h1><strong>Nodejs</strong></h1></p><hr />\
    <h2>LED Control Panel</h2><form action="./index" method="get"><input type="checkbox" name="LED" value="LED1" '+_ck[0]+'>LED1\
    <input type="checkbox" name="LED" value="LED2"'+_ck[1]+'>LED2\
    <br><input type="checkbox" name="LED" value="LED3"'+_ck[2]+'>LED3<input type="checkbox" name="LED" value="LED4" '+_ck[3]+'>LED4\
    <br><input type="radio" name="POWER" value="on" '+_POWER[0]+'>ON<input type="radio" name="POWER" value="off" '+_POWER[1]+'>OFF<br>\
    <input type="submit">\
    <p>'+req.query.LED + "  " +req.query.POWER +'</p>\
    <hr /><h2>LED Switch Frequency</h2><input type="text" name="TIME"'+_TIME+'><input type="submit" name="button" value="Mode_Shine"><br></form>\
    <p>'+_MODE+'</p></body></html>';
    
    res.send(dynamicContent); // 将动态内容发送回客户端
})

function controLED(LED, POWER, TIME) {
    let child_process = require("child_process");

    let process = child_process.execFile('sudo', [
        "./C++/gpio", LED, POWER, TIME
    ]);

    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
    })

    process.stdout.on('data', (data) => {
        console.log(`stderr: ${data}`);
    })

}

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
})


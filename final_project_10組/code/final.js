const express = require("express");
const nodemailer = require('nodemailer');
const app = express();

var str = ""
var foodName_list = ['', '', '', ''];

var led = ["LED1", "LED2", "LED3", "LED4"];
var status = ["off", "off", "off", "off"];

var open = 0;

app.use(express.static('./public'));

app.get("/index1", (req, res) => {

    console.log(req.query.foodName);
    console.log(req.query.allthing);

    for (var i = 0; i < 4; i++) {
        if (req.query.allthing[i] != 'x') {
            foodName_list[i] = req.query.allthing[i];
            status[i] = 'on';
            str += foodName_list[i] + ' ';
        } else {
            foodName_list[i] = ''
            status[i] = 'off';
        }
    }
    str += " : " + "put on the cook table" + '<br>';
    runSequence(led, status);

})

app.get("/index2", (req, res) => {

    console.log("i'm 2");
    console.log(req.query.cookway);
    console.log(req.query.time);
    state = "";

    for (var i = 0; i < 4; i++) {
        if (status[i] == 'on') {
            state += "1";
        } else {
            state += "0";
        }
    }

    if (req.query.cookway == 'cold') {

        runCook(["LED5", "LED6"], ["on", "off"]);
        str += req.query.cookway + " : " + req.query.time + " days " + '<br>';
    } else if (req.query.cookway == 'microwave') {
        runCook(["LED5", "LED6"], ["off", "on"]);
        str += req.query.cookway + " : " + req.query.time + " mins " + '<br>';
    } else {
        return;
    }
    let time = Math.floor(parseInt(req.query.time, 10) / 10);

    console.log(state);
    console.log(time.toString());
    cookLED(state, time.toString());
    console.log("finish");

})


app.get("/index3", (req, res) => {

    console.log("i'm 3");
    console.log(req.query.email);
    sendEmail();
})


app.get("/index4", (req, res) => {

    console.log("i'm 4");
    //res.send("hi");

    open = req.query.check;

    if (open == 1) {
        console.log("hihihi");
        open_carma();
        open = 0;
    }

    detect_adv().then(function (data) {
        res.send(data);
        //console.log(data);

    }).catch(function (err) {
        console.error(err);
        //res.status(500).send(err); 
    });
})


async function runSequence(LED, STATUS) {

    for (var i = 0; i < 4; i++) {

        console.log(LED[i]);
        console.log(STATUS[i]);
    }
    try {
        await insmod();
        await controLED(LED[0], STATUS[0]);
        await controLED(LED[1], STATUS[1]);
        await controLED(LED[2], STATUS[2]);
        await controLED(LED[3], STATUS[3]);
        await rmmod();
    } catch (error) {
        console.error(`Error: ${error.message}`);
    }
}

async function runCook(LED, STATUS) {


    for (var i = 0; i < 2; i++) {

        console.log(LED[i]);
        console.log(STATUS[i]);
    }

    try {
        await insmod();
        await controLED(LED[0], STATUS[0]);
        await controLED(LED[1], STATUS[1]);
        await rmmod();
    } catch (error) {
        console.error(`Error: ${error.message}`);
    }
}


async function insmod() {

    return new Promise((resolve, reject) => {

        const { exec } = require('child_process');

        const command = 'sudo insmod driver/demo.ko';

        exec(command, (error, stdout, stderr) => {
            if (error) {
                console.error(`error: ${error.message}`);
                return;
            }
            resolve();
        });

    });


}

async function rmmod() {

    return new Promise((resolve, reject) => {
        const { exec } = require('child_process');
        const command = 'sudo rmmod driver/demo.ko';

        exec(command, (error, stdout, stderr) => {
            if (error) {
                reject(error);
                return;
            }
            resolve();
        });
    });
}

async function controLED(LED, POWER) {
    return new Promise((resolve, reject) => {
        let child_process = require("child_process");

        let process = child_process.execFile('sudo', [
            "./driver/text.o", LED, POWER,
        ]);

        process.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        })

        process.stdout.on('data', (data) => {
            console.log(`stderr: ${data}`);
        })

        process.on('exit', (code) => {
            if (code === 0) {
                resolve();
            } else {
                reject(new Error(`Process exited with code ${code}`));
            }
        });
    });

}

function cookLED(state, time) {
    let child_process = require("child_process");

    let process = child_process.execFile('sudo', [
        "./lab7/mutex.o", state, time
    ]);
    console.log("ff");

    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
    })

    process.stdout.on('data', (data) => {
        console.log(`stderr: ${data}`);
    })

}

function detect_adv(state, time) {
    return new Promise(function (resolve, reject) {

        let child_process = require("child_process");
        let process = child_process.spawn('sudo', [
            'python',
            'python/lab5_1.py'
        ]);

        process.stdout.on('data', (data) => {
            console.log(`stdout:${data}`);
            resolve(data)

        });

        process.stderr.on('data', (data) => {
            console.error(`stderr:${data}`);
            reject(data)
        });

    })
}

function open_carma() {

    return new Promise((resolve, reject) => {
        const { spawn } = require('child_process');

        // 执行 nvgstcapture-1.0 --prev-res=3 命令
        const captureProcess = spawn('nvgstcapture-1.0', ['--prev-res=3']);

        // 监听子进程的输出
        captureProcess.stdout.on('data', (data) => {
            // 处理子进程的输出数据
            console.log(`输出：${data}`);
        });

        // 监听子进程的错误输出
        captureProcess.stderr.on('data', (data) => {
            // 处理子进程的错误输出
            console.error(`错误：${data}`);
        });

        // 监听子进程的退出事件
        captureProcess.on('exit', (code) => {
            console.log(`子进程退出，退出码：${code}`);
        });

        // 延迟发送输入字符 'j' 和 'q'
        setTimeout(() => {
            // 发送 'j' 到标准输入
            captureProcess.stdin.write('j\n');

            // 延迟发送 'q' 到标准输入
            setTimeout(() => {
                captureProcess.stdin.write('q\n');
            }, 1000);
        }, 1000);

    });
}


function sendEmail(content) {
    const transporter = nodemailer.createTransport({
        host: 'smtp.gmail.com',
        port: 465,
        auth: {
            user: 't110590450@ntut.org.tw',
            pass: 'bzsruovbewlthjfb',
        },
    });

    transporter.sendMail({
        from: 't110590450@ntut.org.tw',
        to: 't110590450@ntut.org.tw',
        subject: "your cook history",
        html: str,
    }).then(info => {
        //console.log({ info });
    }).catch(console.error);

    console.log("send finish");
}

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
})


const express = require("express");
const app = express();

app.use(express.static('./public'));

var mode = 0;
var a = "";
var b = "";
var c = "";
var time = 0;
app.get("/index", (req, res) => {


    if (req.query.MODE == "1") {
        mode = "1"
    }
    if (req.query.MODE == "0") {
        mode = "2"
    }

    if (mode == "1") {

        test().then(function (data) {
            res.send(data);

        }).catch(function (err) {
            console.error(err);
            //res.status(500).send(err); 
        });
    }
    if (mode == "2") {
        if (req.query.TIME == "") {
            if (req.query.LED == undefined) {
                a = "";
                b = "";
                c = "";
            } else {
                a = "";
                b = "";
                c = "";

                if (req.query.LED[0] == "0") {
                    a = "0";
                } else if (req.query.LED[0] == "1") {
                    a = "1";
                }
                if (req.query.LED[1] == "0") {
                    b = "0";
                } else if (req.query.LED[1] == "1") {
                    b = "1";
                }
                if (req.query.MODE2 == "ON") {
                    c = "1";
                } else if (req.query.MODE2 == "OFF") {
                    c = "0";
                }
                if (b == "") {
                    b = c;
                    c = "";
                }
                console.log(a);
                console.log(b);
                console.log(c);
                console.log(req.query.MODE2);

            }

            test2().then(function (data) {
                res.send(data);

            }).catch(function (err) {
                console.error(err);
                //res.status(500).send(err);
            });

        } else {
            time = req.query.TIME
            test3().then(function (data) {
                res.send(data);

            }).catch(function (err) {
                console.error(err);
                //res.status(500).send(err);
            });
        }

    }
    console.log(req.query.LED)
})

function test() {

    return new Promise(function (resolve, reject) {

        let child_process = require("child_process");
        let process = child_process.spawn('python', [
            "python/lab5_2.py", "0"
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


function test2() {

    return new Promise(function (resolve, reject) {

        let child_process = require("child_process");
        let process;
        if (c == "") {
            process = child_process.spawn('python', [
                "python/lab5_22.py", a, b
            ]);
        } else if (c != "") {

            process = child_process.spawn('python', [
                "python/lab5_22.py", a, b, c
            ]);

        }

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

function test3() {

    return new Promise(function (resolve, reject) {

        let child_process = require("child_process");
        let process = child_process.spawn('python', [
            "python/lab5_23.py", time
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

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
})


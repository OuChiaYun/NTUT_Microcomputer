#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(up()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(down()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_get_led_clicked()
{
    check_led();

}


void MainWindow::on_get_led_switch_clicked()
{
    q[0] =ui ->label_1;
    q[1] =ui->label_2;
    q[2] =ui->label_3;
    q[3] =ui->label_4;
    check_led();
    led_state[0] = 1;
    led_state[1] = 1;
    led_state[2] = 0;
    led_state[3] = 0;
    QString time;
    time = ui ->textEdit->toPlainText();
    n = time.toInt();
    ui ->textEdit->setPlainText("");
    QChar v = char(n+'0');
    ui ->label ->setText(v);


    timer->start(1000);

}

void MainWindow::up()
{
    if(n == 0){
        for(int i = 0;i<4;i++){
            led_state[i] = 0;
            q[i] ->setPixmap(pic_off);
        }
        timer2->stop();
        timer->stop();

    }else{
        timer->stop();
        for(int i = 0;i<4;i++){
            if(led_state[i]!= 0){
           // ui->label->setText(led[i]);
                q[i] ->setPixmap(pic);

            }else{
                q[i] ->setPixmap(pic_off);

            }
        }
        timer2->start(1000);
    }
}

void MainWindow::down()
{
    n-=1;
    QChar v = char(n+'0');
    ui ->label ->setText(v);
    timer2->stop();
    for(int i = 0;i<4;i++){
        if(led_state[i]== 0){
            q[i] ->setPixmap(pic);
            //ui->label->setText(led[i]);


        }else{
            q[i] ->setPixmap(pic_off);

        }
    }
    timer->start(1000);

}

void MainWindow::check_led()
{


    for (int i = 0;i<4;i++){
        led_state[i] = 0;
        //q[i]-> setPixmap(pic_off);
    }

    if(ui ->LED_1 ->isChecked()){
        led_state[0] = 396;
        ui ->label_1 -> setPixmap(pic);
    }else{
        ui ->label_1 -> setPixmap(pic_off);

    }

    if(ui ->LED_2 ->isChecked()){
        led_state[1] = 392;
        ui ->label_2 -> setPixmap(pic);
    }else{
        ui ->label_2 -> setPixmap(pic_off);

    }

    if(ui ->LED_3 ->isChecked()){
        led_state[2] = 255;
        ui ->label_3 -> setPixmap(pic);
    }else{
        ui ->label_3 -> setPixmap(pic_off);

    }

    if(ui ->LED_4 ->isChecked()){
        led_state[3] = 429;
        ui ->label_4 -> setPixmap(pic);
    }
    else{
            ui ->label_4 -> setPixmap(pic_off);

    }


}


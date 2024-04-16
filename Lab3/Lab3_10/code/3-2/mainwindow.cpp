#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(up()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(down()));
    all_set_exp_dir();
    speed = 1000-10*(ui->horizontalSlider->value());

}

MainWindow::~MainWindow()
{
    all_set_unexp();
    delete ui;
}


void MainWindow::on_get_led_clicked()
{
    check_led();
    for(int i = 0;i<4;i++){
        if(led_state[i] != 0){
            gpio_set_value(gpio_n[i],1);

        }else{
            gpio_set_value(gpio_n[i],0);
        }
    }

}


void MainWindow::on_get_led_switch_clicked()
{
    q[0] =ui ->label_1;
    q[1] =ui->label_2;
    q[2] =ui->label_3;
    q[3] =ui->label_4;
    qc[0] = ui->LED_1;
    qc[1] = ui->LED_2;
    qc[2] = ui->LED_3;
    qc[3] = ui->LED_4;

    check_led();

    led_state[0] = 1;
    led_state[1] = 1;
    led_state[2] = 0;
    led_state[3] = 0;
    flag = 0;




    timer->start(speed);

}

void MainWindow::on_switch_off_clicked()
{
        flag = 1;
                for(int i = 0;i<4;i++){
                    led_state[i] = 0;
                    gpio_set_value(gpio_n[i],0);
                    q[i] ->setPixmap(pic_off);
                    qc[i] ->setChecked(0);

                }
                speed =1000-( ui->horizontalSlider->value())*10;
                timer2->stop();
                timer->stop();

}


void MainWindow::up()
{

    timer->stop();
        for(int i = 0;i<4;i++){
            if(led_state[i]!= 0){
           // ui->label->setText(led[i]);
                q[i] ->setPixmap(pic);
                qc[i] ->setChecked(1);
                gpio_set_value(led[i],1);


            }else{
            q[i] ->setPixmap(pic_off);
            qc[i] ->setChecked(0);
            gpio_set_value(led[i],0);
        }
    }
    timer2->start(speed);


}

void MainWindow::down()
{

    timer2->stop();
    for(int i = 0;i<4;i++){
        if(led_state[i]== 0){
            q[i] ->setPixmap(pic);
            qc[i] ->setChecked(1);
            //ui->label->setText(led[i]);
            gpio_set_value(led[i],1);


        }else{
            qc[i] ->setChecked(0);
            q[i] ->setPixmap(pic_off);
            gpio_set_value(led[i],0);

        }
    }
    timer->start(speed);

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

void MainWindow::all_set_exp_dir(){
    for(int i = 0;i<4;i++){
        gpio_export(gpio_n[i]);
        gpio_set_dir(gpio_n[i],"out");
    }

}
void MainWindow::all_set_unexp(){
    for(int i = 0;i<4;i++){
        gpio_unexport(gpio_n[i]);
    }

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{


    speed =1000-(ui->horizontalSlider->value())*10;

}

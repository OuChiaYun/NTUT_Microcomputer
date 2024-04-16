#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <string>
#include <QLabel>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_get_led_clicked();

    void on_get_led_switch_clicked();

    void on_switch_off_clicked();


    void up();

    void down();

    void check_led();

    void all_set_exp_dir();

    void all_set_unexp();


    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    int led[4] = {396,392,255,429};
    int led_state[4] = {0,0,0,0};
    QPixmap pic = QPixmap("p2.png");
    QPixmap pic_off = QPixmap("");
//    Q qlabel[]= {};
    QLabel *q[4];
    QCheckBox *qc[4];
    int gpio_n[4] = {396,392,255,429};
    int n = 0;
    int flag = 0;
    int speed = 1000;

    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);

};

#endif // MAINWINDOW_H

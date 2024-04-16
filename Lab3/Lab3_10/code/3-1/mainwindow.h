#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <string>
#include <QLabel>

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

    void up();

    void down();

    void check_led();




private:
    Ui::MainWindow *ui;
    int led[4] = {396,392,255,429};
    int led_state[4] = {0,0,0,0};
    QPixmap pic = QPixmap("/home/nvidia/Downloads/p2.png");
    QPixmap pic_off = QPixmap("/home/nvidia/Downloads/p1.png");
//    Q qlabel[]= {};
    QLabel *q[4];

    int n = 0;

    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);

};

#endif // MAINWINDOW_H

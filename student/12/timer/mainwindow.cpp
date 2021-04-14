#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumberMin->setPalette(Qt::red);
    ui->lcdNumberSec->setPalette(Qt::green);
    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(runTheClock()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if(!startPressed){
        timer->start(1000);
    }
    startPressed=true;
}

void MainWindow::runTheClock()
{
    if(secs<60){
        ++secs;
    }
    else{
        secs=0;
        ++mins;
    }
    QString sec= QString::number(secs);
    QString min= QString::number(mins);
    ui->lcdNumberSec->display(sec);
    ui->lcdNumberMin->display(min);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
    startPressed=false;
}

void MainWindow::on_resetButton_clicked()
{
    on_stopButton_clicked();
    secs=0;
    mins=0;
    QString sec= QString::number(secs);
    QString min= QString::number(mins);
    ui->lcdNumberSec->display(sec);
    ui->lcdNumberMin->display(min);
}

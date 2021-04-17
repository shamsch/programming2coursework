#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    weightString= ui->weightLineEdit->text();
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    heightString= ui->heightLineEdit->text();
}

void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weightString= arg1;
}

void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    heightString=arg1;
}

void MainWindow::on_countButton_clicked()
{
    double height, weight, bmi;
    height= heightString.toDouble();
    weight= weightString.toDouble();
    height=height/100;
    bmi= (weight/(height*height));
    QString display = QString::number(bmi);
    ui->resultLabel->setText(display);
    if(bmi<18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if(bmi>=18.5 && bmi<=25.0){
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
    else{
        ui->infoTextBrowser->setText("You are overweight.");
    }

}

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


void MainWindow::on_amountOfCardLineEdit_editingFinished()
{
    amountOfCards= ui->amountOfCardLineEdit->text().toInt();
    qDebug() << amountOfCards;
}

void MainWindow::on_seedValueLineEdit_editingFinished()
{
    seedValue=ui->seedValueLineEdit->text().toInt();
    qDebug() << seedValue;
}

void MainWindow::on_numberOfPlayerLineEdit_editingFinished()
{
    numberOfPlayers=ui->numberOfPlayerLineEdit->text().toInt();
    qDebug() << numberOfPlayers;
}

void MainWindow::on_playerNameStringLineEdit_editingFinished()
{
    QString allPlayerString= ui->playerNameStringLineEdit->text();
    nameOfPlayer= allPlayerString.split(QString(" "));
    qDebug() << nameOfPlayer;
}


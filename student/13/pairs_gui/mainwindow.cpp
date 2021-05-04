#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "dialog.hh"
#include <QHBoxLayout>
#include <QPoint>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>

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


void MainWindow::validateData()
{
    if(amountOfCards%2==0 && amountOfCards!=0){
        if(numberOfPlayers>=1){
            if(nameOfPlayer.size()==numberOfPlayers){
                ui->gameStatusTextBrowser->setText("");
                findRowAndCol(amountOfCards,row,col);
                makeBoardGUI(row,col);
            }
            else{
                ui->gameStatusTextBrowser->setText("Error in players name, GAME CAN NOT START!");
            }
        }
        else{
            ui->gameStatusTextBrowser->setText("Error in number of players, GAME CAN NOT START!");
        }
    }
    else{
        ui->gameStatusTextBrowser->setText("Amount of cards not valid, GAME CAN NOT START!");
    }
}

void MainWindow::makeARandomString(int n)
{
    char starter='a';
    for(int i=0; i<n/2;i++){
        randomString+= (starter+i);
        randomString+= (starter+i);
    }
    std::random_shuffle(randomString.begin(),randomString.end());
}

void MainWindow::on_startGamePushButton_clicked()
{
    validateData();

}

void MainWindow::cardClicked()
{
    if(cardsOpen<2){
        QPushButton *button = (QPushButton *) sender();
         for(unsigned int i = 0; i < cardButton_.size(); ++i)
         {
             if(cardButton_.at(i)==button)
             {
                 QString text;
                 text= buttonWithLetters[cardButton_.at(i)];
                 button->setText(text);
             }
         }
         openCards.push_back(button);
         cardsOpen++;
    }
}

void MainWindow::makeBoardGUI(int noOfRow, int noOfCol)
{

    gameBoard = new Dialog(this);

    QWidget *widget= new QWidget(gameBoard);
    QGridLayout *layout= new QGridLayout(widget);

    for(int i=0;i<noOfRow;i++){
        for(int j=0; j<noOfCol; j++){
            QPushButton *button = new QPushButton("X",this);
            cardButton_.push_back(button);
            layout->addWidget(button, i,j);
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::cardClicked);
        }
    }
    QPushButton *nextTurn= new QPushButton("Next turn", this);
    layout->addWidget(nextTurn, noOfRow, noOfCol/2);
    gameBoard->show();
    makeARandomString(amountOfCards);
    for(unsigned long long int i=0; i<cardButton_.size(); i++){
        buttonWithLetters.insert({cardButton_.at(i),randomString.at(i)});
    }


}

void MainWindow::findRowAndCol(int number, int &row, int &col)
{

    for (int i = 1; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            row = i;
        }
    }
    col = number / row;
}


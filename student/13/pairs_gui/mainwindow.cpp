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

    this->setWindowTitle("Pairs game by Shamsur");
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


void MainWindow::on_playerNameStringLineEdit_editingFinished()
{
    QString allPlayerString= ui->playerNameStringLineEdit->text();
    nameOfPlayer= allPlayerString.split(QString(" "));
    qDebug() << nameOfPlayer;
}


void MainWindow::validateData()
{
    if(amountOfCards%2==0 && amountOfCards!=0){
        if(nameOfPlayer.size()==2){
            ui->startGamePushButton->setText("Game started");
            ui->startGamePushButton->setEnabled(false);
            ui->gameStatusTextBrowser->setText(nameOfPlayer[0]+" is in turn");
            cardsLeftToPlay=amountOfCards;
            findRowAndCol(amountOfCards,row,col);
            makeBoardGUI(row,col);
        }
        else{
            ui->gameStatusTextBrowser->setText("Error in players name, GAME CAN NOT START!");
        }
    }
    else{
        ui->gameStatusTextBrowser->setText("Amount of cards not valid, GAME CAN NOT START!");
    }
}

void MainWindow::makeARandomString(int n)
{
    char starter='A';
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
        button->setStyleSheet("QPushButton { background-color: blue; }\n"
                  "QPushButton:enabled { background-color: rgb(0, 128, 0); }\n");
         for(unsigned int i = 0; i < cardButton_.size(); ++i)
         {
             if(cardButton_.at(i)==button)
             {
                 QString alphabet;
                 alphabet= buttonWithLetters[cardButton_.at(i)];
                 button->setText(alphabet);
             }
         }

         if (std::find(openCards.begin(), openCards.end(), button)
                 == openCards.end()) {
             openCards.push_back(button);
             cardsOpen++;
         }

    }
}

void MainWindow::nextTurnClicked()
{
    if(cardsOpen==2 && cardsLeftToPlay>0){
        if(buttonWithLetters[openCards.at(0)]==buttonWithLetters[openCards.at(1)]){
            matchFound=true;
            cardsLeftToPlay=cardsLeftToPlay-2;
            givePointToPlayerInTurn();
        }
        updatePlayerScore();
        ++playerInTurn;
        closeOpenCards();
    }
    if(cardsLeftToPlay==0){
        QPushButton *button = (QPushButton *) sender();
        button->setText("Check result!");
        button->setEnabled(false);
        announceWinner();
    }
}

void MainWindow::restartGameClicked()
{
    gameBoard->accept();
    ui->amountOfCardLineEdit->setText("");
    ui->playerNameStringLineEdit->setText("");
    ui->startGamePushButton->setEnabled(true);
    ui->gameStatusTextBrowser->setText("");
    ui->startGamePushButton->setText("Play again");
    cardsOpen=0;
    playerInTurn=1;
    playerOnePts=0;
    playerTwoPts=0;
    cardsOpen=0;
    randomString="";
    buttonWithLetters.clear();
    cardButton_.clear();
    openCards.clear();
}

void MainWindow::makeBoardGUI(int noOfRow, int noOfCol)
{

    gameBoard = new Dialog(this);

    QWidget *widget= new QWidget(gameBoard);
    QGridLayout *layout= new QGridLayout(widget);

    for(int i=0;i<noOfRow;i++){
        for(int j=0; j<noOfCol; j++){
            QPushButton *button = new QPushButton("X",this);

            //to give color
            button->setStyleSheet("QPushButton { background-color: grey; }\n"
                      "QPushButton:enabled { background-color: rgb(200,0,0); }\n");

            cardButton_.push_back(button);
            layout->addWidget(button, i,j);
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::cardClicked);
        }
    }


    QPushButton *nextTurn= new QPushButton("Next turn", this);
    layout->addWidget(nextTurn, noOfRow, noOfCol/2);
    connect(nextTurn, &QPushButton::clicked,
            this, &MainWindow::nextTurnClicked);

    QPushButton *restartGame= new QPushButton("Restart?", this);
    layout->addWidget(restartGame, noOfRow+1, noOfCol/2);
    connect(restartGame, &QPushButton::clicked, this, &MainWindow::restartGameClicked);

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

void MainWindow::givePointToPlayerInTurn()
{
    if(playerInTurn%2==0){
        ++playerTwoPts;
    }
    else{
        ++playerOnePts;
    }
}

void MainWindow::closeOpenCards()
{
    for(auto openCard: openCards){
        if(matchFound){
            openCard->setText("X");
            openCard->setStyleSheet("QPushButton { background-color: black; }\n"
                          "QPushButton:enabled { background-color: rgb(0, 128, 128); }\n");
            openCard->setEnabled(false);
        }
        else{
            openCard->setText("X");
            openCard->setStyleSheet("QPushButton { background-color: grey; }\n"
                          "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        }

    }

    openCards.clear();
    cardsOpen=0;

    if(matchFound){
        matchFound=false;
    }
}

void MainWindow::updatePlayerScore()
{
    QString player1=nameOfPlayer[0];
    player1+="'s score stands at ";
    player1+=QString::number(playerOnePts);
    QString player2=nameOfPlayer[1];
    player2+="'s score stands at ";
    player2+=QString::number(playerTwoPts);
    if(playerInTurn%2==0){
        inTurn= nameOfPlayer[0]+" is in turn";
    }
    else{
         inTurn= nameOfPlayer[1]+" is in turn";
    }
    QString textToBeDisplayed= inTurn+ "\n"+ player1+ "\n" + player2;
    ui->gameStatusTextBrowser->setText(textToBeDisplayed);

}

void MainWindow::announceWinner()
{
    if(playerOnePts>playerTwoPts){
        ui->gameStatusTextBrowser->setText("Congrats, "+ nameOfPlayer[0] + "! You have won.");
    }
    else if(playerTwoPts>playerOnePts){
        ui->gameStatusTextBrowser->setText("Congrats, "+ nameOfPlayer[1] + "! You have won.");
    }
    else{
        ui->gameStatusTextBrowser->setText("It's a draw, bois! :))");
    }
}


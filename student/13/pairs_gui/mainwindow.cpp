#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "dialog.hh"
#include <QGridLayout>
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
    // qDebug() << amountOfCards;
}


void MainWindow::on_playerNameStringLineEdit_editingFinished()
{
    QString allPlayerString= ui->playerNameStringLineEdit->text();
    nameOfPlayer= allPlayerString.split(QString(" "));
    // qDebug() << nameOfPlayer;
}

// This method checks if the pre-game data is valid or not
void MainWindow::validateData()
{
    if(amountOfCards%2==0 && amountOfCards!=0){
        if(nameOfPlayer.size()==2){
            ui->startGamePushButton->setText("Game started");

            //disabling the button after game start

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

// This method essentially make a string with N (cards) number of letter and randomly suffles them
void MainWindow::makeARandomString(int n)
{
    char starter='A';
    for(int i=0; i<n/2;i++){
        //adding the same letter twice so they are always in pair
        randomString+= (starter+i);
        randomString+= (starter+i);
    }
    //for the purpose of randomness
    std::random_shuffle(randomString.begin(),randomString.end());
}

// This method triggers the game
void MainWindow::on_startGamePushButton_clicked()
{
    validateData();
}

// This method checks which card is pressed
void MainWindow::cardClicked()
{
    if(cardsOpen<2){
        //finding the button which has been clicked
        QPushButton *button = (QPushButton *) sender();

        //changing style
        button->setStyleSheet("QPushButton { background-color: blue; }\n"
                  "QPushButton:enabled { background-color: rgb(0, 128, 0); }\n");
         for(unsigned int i = 0; i < cardButton_.size(); ++i)
         {
             if(cardButton_.at(i)==button)
             {
                 //getting the character behind the button
                 QString alphabet;
                 alphabet= buttonWithLetters[cardButton_.at(i)];
                 button->setText(alphabet);
             }
         }

         // this will prevent the bug of pressing the same button twice and finding a match
         if (std::find(openCards.begin(), openCards.end(), button)
                 == openCards.end()) {
             openCards.push_back(button);
             cardsOpen++;
         }

    }
}

// This method moves the game forwards by giving the next player the turn

void MainWindow::nextTurnClicked()
{
    //checks for match
    if(cardsOpen==2 && cardsLeftToPlay>0){
        if(buttonWithLetters[openCards.at(0)]
                ==buttonWithLetters[openCards.at(1)]){
            matchFound=true;
            cardsLeftToPlay=cardsLeftToPlay-2;
            givePointToPlayerInTurn();
        }
        updatePlayerScore();
        ++playerInTurn;
        closeOpenCards();
    }

    // when all cards have been played
    if(cardsLeftToPlay==0){
        QPushButton *button = (QPushButton *) sender();
        button->setText("Check result!");
        button->setEnabled(false);
        announceWinner();
    }
}

// This method resets the game and sets all value to default
void MainWindow::restartGameClicked()
{
    // closing the window
    gameBoard->accept();

    //reseting all values for a new game
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
    playerOneCollection.clear();
    playerTwoCollection.clear();
}

//This method creates the dialog window of the cards namely gameboard
void MainWindow::makeBoardGUI(int noOfRow, int noOfCol)
{
    // a new dialog window
    gameBoard = new Dialog(this);

    QWidget *widget= new QWidget(gameBoard);
    QGridLayout *layout= new QGridLayout(widget);

    //placing the buttons with loop
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

    //the other two buttons for game running purposes
    QPushButton *nextTurn= new QPushButton("Next turn", this);
    layout->addWidget(nextTurn, noOfRow, noOfCol/2);
    connect(nextTurn, &QPushButton::clicked,
            this, &MainWindow::nextTurnClicked);

    QPushButton *restartGame= new QPushButton("Restart?", this);
    layout->addWidget(restartGame, noOfRow+1, noOfCol/2);
    connect(restartGame, &QPushButton::clicked, this, &MainWindow::restartGameClicked);

    gameBoard->show();

    makeARandomString(amountOfCards);

    //assigning random letter (but in pair) to each buttons
    for(unsigned long long int i=0; i<cardButton_.size(); i++){
        buttonWithLetters.insert({cardButton_.at(i),randomString.at(i)});
    }


}

// Calculates the closest factor for row and colum, number being the number of cards
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

// Gives point to the player who has found a match
void MainWindow::givePointToPlayerInTurn()
{
    if(playerInTurn%2==0){
        ++playerTwoPts;

        //keeping track of cards collected
        char collectedCard= buttonWithLetters[openCards.at(0)];
        playerTwoCollection.push_back(collectedCard);
    }
    else{
        ++playerOnePts;

        char collectedCard= buttonWithLetters[openCards.at(0)];
        playerOneCollection.push_back(collectedCard);
    }
}

// Closes open card and changes styles if match found
void MainWindow::closeOpenCards()
{
    for(auto openCard: openCards){
        if(matchFound){
            //changing the style and making button disable upon match found
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

    // reseting for next turn
    openCards.clear();
    cardsOpen=0;

    //seting match to deafult
    if(matchFound){
        matchFound=false;
    }
}

// Updataes the player score in the gameStatus area
void MainWindow::updatePlayerScore()
{
    //gets the score
    QString player1=nameOfPlayer[0];
    player1+="'s score stands at ";
    player1+=QString::number(playerOnePts);

    //gets the cards
    QString cardsCollectedP1="cards collected by "+ nameOfPlayer[0]+ " : ";
    for(auto card: playerOneCollection){
        cardsCollectedP1+= QChar::fromLatin1(card);
        cardsCollectedP1+=" ";
    }

    QString player2=nameOfPlayer[1];
    player2+="'s score stands at ";
    player2+=QString::number(playerTwoPts);

    QString cardsCollectedP2="cards collected by "+ nameOfPlayer[1]+ " : ";
    for(auto card: playerTwoCollection){
        cardsCollectedP2+= QChar::fromLatin1(card);
        cardsCollectedP2+=" ";
    }

    //finds the player in turn
    if(playerInTurn%2==0){
        inTurn= nameOfPlayer[0]+" is in turn";
    }
    else{
         inTurn= nameOfPlayer[1]+" is in turn";
    }

    //display accordingly
    QString textToBeDisplayed= inTurn+ "\n"+ player1+ "\n" + cardsCollectedP1 +
            "\n" + player2 + "\n" +cardsCollectedP2;

    ui->gameStatusTextBrowser->setText(textToBeDisplayed);

}

// Finds the result of the game and updates it in the gameStatus area
void MainWindow::announceWinner()
{
    //finds the winner
    QString text = ui->gameStatusTextBrowser->toPlainText();
    if(playerOnePts>playerTwoPts){

        ui->gameStatusTextBrowser->setText(text+"\nCONGRATS, "+ nameOfPlayer[0] + "! You have won.");
    }
    else if(playerTwoPts>playerOnePts){
        ui->gameStatusTextBrowser->setText(text+"\nCONGRATS, "+ nameOfPlayer[1] + "! You have won.");
    }
    else{
        ui->gameStatusTextBrowser->setText(text+"\nIt's a draw, bois! :))");
    }
}


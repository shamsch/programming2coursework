#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <QPushButton>
#include <dialog.hh>
#include <string>
#include <algorithm>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_amountOfCardLineEdit_editingFinished();

    void on_playerNameStringLineEdit_editingFinished();

    void on_startGamePushButton_clicked();

    void cardClicked();

    void nextTurnClicked();

    void restartGameClicked();

private:
    Ui::MainWindow *ui;
    Dialog *gameBoard;

    int amountOfCards=0;
    int row=0;
    int col=0;
    int cardsOpen=0;
    int playerInTurn=1;
    int playerOnePts=0;
    int playerTwoPts=0;
    int cardsLeftToPlay;

    QStringList nameOfPlayer;
    QString inTurn="";

    std::string randomString="";

    std::vector<QPushButton*> cardButton_;
    std::vector<QPushButton*> openCards;
    std::map<QPushButton*, char> buttonWithLetters;

    void makeBoardGUI(int noOfRow, int noOfCol);

    void validateData();

    void makeARandomString(int n);

    void findRowAndCol(int number, int &row, int &col);

    void givePointToPlayerInTurn();
    void closeOpenCards();
    void updatePlayerScore();
    void announceWinner();

    bool gameStarted=false;
    bool matchFound= false;
};
#endif // MAINWINDOW_HH

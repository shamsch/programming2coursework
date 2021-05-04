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

    void on_seedValueLineEdit_editingFinished();

    void on_numberOfPlayerLineEdit_editingFinished();

    void on_playerNameStringLineEdit_editingFinished();

    void on_startGamePushButton_clicked();

    void cardClicked();

private:
    Ui::MainWindow *ui;
    Dialog *gameBoard;

    int amountOfCards=0;
    int seedValue =0;
    int numberOfPlayers=0;
    int row=0;
    int col=0;
    int cardsOpen=0;

    QStringList nameOfPlayer;

    std::string randomString="";

    std::vector<QPushButton*> cardButton_;
    std::vector<QPushButton*> openCards;
    std::map<QPushButton*, char> buttonWithLetters;

    void makeBoardGUI(int noOfRow, int noOfCol);

    void validateData();

    void makeARandomString(int n);

    void findRowAndCol(int number, int &row, int &col);

    bool gameStarted=false;
};
#endif // MAINWINDOW_HH

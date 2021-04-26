#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
    int amountOfCards=0;
    int seedValue =0;
    int numberOfPlayers=0;
    QStringList nameOfPlayer;
};
#endif // MAINWINDOW_HH

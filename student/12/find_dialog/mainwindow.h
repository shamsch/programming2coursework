#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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

    void on_findPushButton_clicked();

    void on_keyLineEdit_editingFinished();

    void on_fileLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QString nameOfTheFile="";
    QString wordToFind="";
    bool fileNotFound=false;
    bool wordNotFound=true;
    void setDefaultBoolVal();
};
#endif // MAINWINDOW_H

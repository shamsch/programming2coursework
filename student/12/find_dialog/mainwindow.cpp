#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

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


void MainWindow::on_findPushButton_clicked()
{
    on_fileLineEdit_editingFinished();
    on_keyLineEdit_editingFinished();
    setDefaultBoolVal();

    QFile file(nameOfTheFile);


    if(!file.open(QFile::ReadOnly| QFile::Text)){
        fileNotFound=true;
        ui->textBrowser->setText("File not found");
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd()){
        QString line= in.readLine();
        QStringList words= line.split(" ");
        if(ui->matchCheckBox->isChecked()){
            for(const auto & word: words){
                if(word==wordToFind){
                    wordNotFound=false;
                    break;
                }
            }
        }
        else{
            wordToFind= wordToFind.toUpper();
            for(auto &word: words){
                word= word.toUpper();
                if(word==wordToFind){
                    wordNotFound=false;
                    break;
                }
            }
        }

    }

    file.close();

    ui->textBrowser->setText("");

    if(!(fileNotFound) && wordToFind==""){
        ui->textBrowser->setText("File found");
    }
    else if(wordNotFound){
        ui->textBrowser->setText("Word not found");
    }
    else{
        ui->textBrowser->setText("Word found");
    }

}



void MainWindow::on_keyLineEdit_editingFinished()
{
    wordToFind= ui->keyLineEdit->text();
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    nameOfTheFile= ui->fileLineEdit->text();
}

void MainWindow::setDefaultBoolVal()
{
     fileNotFound=false;
     wordNotFound=true;

}

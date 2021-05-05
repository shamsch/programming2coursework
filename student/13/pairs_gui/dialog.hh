#ifndef DIALOG_HH
#define DIALOG_HH

//Author
// * Name: Shamsur Raza Chowdhury
// * Student number: 050359798
// * UserID: rvshch
// * E-Mail: shamsurraza.chowdhury@tuni.fi


#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_HH

/* Pairs
 *
 * Desc:
 * This program generates a pairs (memory) game with GUI. The game has a variant
 * number of cards and allows two players. The card is randomly placed in the game board.
 * On each turn, the player in turn presses the card. After that the given cards will be turned as
 * visible and the score is updated. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 * The cards are described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (X), and a removed one as a black disabled button.
 * Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 *
 * Program author
 * Name: Shamsur Raza Chowdhury
 * Student number: 050359798
 * UserID: rvshch
 * E-Mail: shamsurraza.chowdhury@tuni.fi
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

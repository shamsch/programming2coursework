/* Pairs
 *
 * Desc:
 *  This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 *  On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 *
 * Program author ( Fill with your own info )
 * Name: Shamsur Raza Chowdhury
 * Student number: 050359798
 * UserID: rvshch 
 * E-Mail: shamsurraza.chowdhury@tuni.fi
 *
 * Notes about the program and it's implementation:
 * It was a rather difficult and time consmuing project for a first one, which only makes me wonder what is to come. I implemented it by myself. 
 * */

#include <iostream>
#include <vector>
#include <random>
#include "player.hh"
#include "card.hh"

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string &str)
{
    bool is_numeric = true;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        if (not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if (is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type &g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for (unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for (unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type &g_board, unsigned int start)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Starting from the given value
    for (unsigned int i = start; i < rows * columns; ++i)
    {
        if (g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }

    // Continuing from the beginning
    for (unsigned int i = 0; i < start; ++i)
    {
        if (g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type &g_board, int seed)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);

    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for (unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {

        // Adding two identical cards (pairs) in the game board
        for (unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for (unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints a variable-length game board with borders.
void print(const Game_board_type &g_board)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for (unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for (unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for (unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int &smaller_factor, unsigned int &bigger_factor)
{
    unsigned int product = 0;
    while (not(product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for (unsigned int i = 1; i * i <= product; ++i)
    {
        if (product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Self-made functions

// This function is used for separating a string using space as a separator and then pushing each section to a string vector
void convert_string_to_strVector(vector<string> &x, string y)
{
    string add = "";
    for (string::size_type i = 0; i < y.length(); i++)
    {
        if (y[i] == ' ')
        {
            x.push_back(add);
            add = "";
        }
        else
        {
            add += y[i];
        }
    }
    // Any residue after the last space being taken care of
    if (add != "")
    {
        x.push_back(add);
    }
}

//This function serves the purpose of asking user to input number of players and their names. Also, it validates the data and then creates necessary Player object and stores it
void askNumberAndNameOfPlayer(vector<Player> &playerVect)
{
    vector<string> nameOfThePlayers;
    unsigned int numberOfPlayer = 0;
    // Taking input for the number of players in the game and also validating the it in the loop
    while (numberOfPlayer < 1)
    {
        cout << INPUT_AMOUNT_OF_PLAYERS;
        string temp;
        getline(cin, temp);
        numberOfPlayer = stoi_with_check(temp);
    }

    nameOfThePlayers.clear();
    string temp = "";
    bool condition = true;
    //Taking input for the name of the player and also using a self made function which then validates the data
    while (condition)
    {
        cout << "List " << numberOfPlayer << " players: ";
        getline(cin, temp);
        convert_string_to_strVector(nameOfThePlayers, temp);
        if (nameOfThePlayers.size() >= numberOfPlayer)
        {
            condition = false;
        }
    }
    // Once ready, creating Player object whose consturctor takes a string input for name of the player and then pushing it to a Player vector
    playerVect.clear();
    for (auto i : nameOfThePlayers)
    {
        Player adding(i);
        playerVect.push_back(adding);
    }
}

//This function takes the coordinate input and checks the validity
void inputCard(unsigned int &x1, unsigned int &x2, unsigned int &y1, unsigned int &y2, bool &quit, vector<Player> &players, unsigned int &nowPlaying, unsigned int &row, unsigned int &column, bool &input)
{
    string playerInTurn = players.at(nowPlaying).get_name();
    quit = false;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    vector<unsigned int> keepTheCoordinate;
    string inputCordinate = "";
    cout << playerInTurn << ": " << INPUT_CARDS;
    getline(cin, inputCordinate);
    keepTheCoordinate.clear();
    //In the case of quitting the function stops here
    if (inputCordinate == "q")
    {
        quit = true;
        input = true;
        return;
    }
    //Otherwise it temporarily stores the coordinate systematically in an integar vector for validation
    else
    {
        string temp = "";
        unsigned int num = 0;
        for (string::size_type i = 0; i < inputCordinate.length(); ++i)
        {
            if (inputCordinate[i] == ' ')
            {
                num = stoi_with_check(temp);
                keepTheCoordinate.push_back(num);
                temp = "";
            }
            else
            {
                temp += inputCordinate[i];
            }
        }
        if (temp != "")
        {
            num = stoi_with_check(temp);
            keepTheCoordinate.push_back(num);
            temp = "";
        }
    }
    // This condition checks the validity of the coordinate inserted. I am aware it breaks a style rule, but I couldn't afford to fix it due to lack of time.
    bool condition = ((keepTheCoordinate.at(0) != keepTheCoordinate.at(2)) || (keepTheCoordinate.at(1) != keepTheCoordinate.at(3))) && (keepTheCoordinate.at(0) > 0) && (keepTheCoordinate.at(1) > 0) && (keepTheCoordinate.at(2) > 0) && (keepTheCoordinate.at(3) > 0) && (keepTheCoordinate.at(0) <= column) && (keepTheCoordinate.at(2) <= column) && (keepTheCoordinate.at(1) <= row) && (keepTheCoordinate.at(3) <= row);
    if (!quit && keepTheCoordinate.size() == 4)
    {
        if (condition)
        {
            x1 = keepTheCoordinate.at(0);
            x2 = keepTheCoordinate.at(2);
            y1 = keepTheCoordinate.at(1);
            y2 = keepTheCoordinate.at(3);
            input = true;
        }
        else
        {
            cout << INVALID_CARD << endl;
        }
    }
    else if (keepTheCoordinate.size() != 4)
    {
        cout << INVALID_CARD << endl;
    }
}

//This function essentially runs the program by turning card and finding match
void turnCard(vector<Player> &players, Game_board_type &gameBoard, bool &quitStatus)
{
    unsigned int x1, x2, y1, y2, rows, columns, whoseTurn, numberOfPlayers;
    static unsigned int turnCounter = 0;
    char letter_1, letter_2;
    bool inputSuccess = false;
    rows = gameBoard.size();
    if (rows > 0)
    {
        columns = gameBoard.at(0).size();
    }
    numberOfPlayers = players.size();
    //Finding out whose turn it is
    whoseTurn = turnCounter % numberOfPlayers;
    //Taking input using a defined function
    while (!inputSuccess)
    {
        inputCard(x1, x2, y1, y2, quitStatus, players, whoseTurn, rows, columns, inputSuccess);
    }
    //Finding the characters for those coordinate, checking for match, and updating number of pairs for the player
    if (!quitStatus)
    {
        //This substraction of one allows us to adjust for the vector index starting from zero
        x1--;
        x2--;
        y1--;
        y2--;
        letter_1 = gameBoard.at(y1).at(x1).get_letter();
        letter_2 = gameBoard.at(y2).at(x2).get_letter();
        if (letter_1 != EMPTY_CHAR && letter_2 != EMPTY_CHAR)
        {
            gameBoard.at(y1).at(x1).set_visibility(OPEN);
            gameBoard.at(y2).at(x2).set_visibility(OPEN);
            print(gameBoard);
            if (letter_1 == letter_2)
            {
                cout << FOUND << endl;
                //Using method from player.hh to update score
                players[whoseTurn].add_card(gameBoard.at(y1).at(x1));
                players[whoseTurn].add_card(gameBoard.at(y2).at(x2));
            }
            else
            {
                cout << NOT_FOUND << endl;
                gameBoard.at(y1).at(x1).set_visibility(HIDDEN);
                gameBoard.at(y2).at(x2).set_visibility(HIDDEN);
                turnCounter += 1;
            }
            for (auto ele : players)
            {
                ele.print();
            }
            print(gameBoard);
        }
        else
        {
            cout << INVALID_CARD << endl;
        }
    }
}

//This function checks if there is still any non-empty card left so as to continue the game or not
bool allCardsEmpty(Game_board_type game_board)
{
    bool allCardsEmpty = true;
    unsigned int row, columns;
    row = game_board.size();
    if (row > 0)
    {
        columns = game_board.at(0).size();
    }
    if (row > 0 && columns > 0)
    {
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int k = 0; k < columns; k++)
            {
                //Any non-empty card results in the function returning false hence continuing the game
                if (game_board.at(i).at(k).get_letter() != EMPTY_CHAR)
                {
                    allCardsEmpty = false;
                }
            }
        }
    }
    return allCardsEmpty;
}

//This function finds the winner and print necessary statement at the end of the game
void determineWinner(vector<Player> players)
{
    unsigned int numOfPlayers = players.size();
    unsigned int winnerCounter = 0;
    string nameOfTheWinner = "";
    unsigned maxPoint = 0;

    if (numOfPlayers > 0)
    {
        //Checking the max point or maximum number of point any player got
        for (unsigned int i = 0; i < numOfPlayers; i++)
        {
            if (players.at(i).number_of_pairs() > maxPoint)
            {
                maxPoint = players.at(i).number_of_pairs();
            }
        }
        //Finding out the name of who got the max point
        for (auto k : players)
        {
            if (k.number_of_pairs() == maxPoint)
            {
                if (winnerCounter == 0)
                {
                    nameOfTheWinner = k.get_name();
                }
                winnerCounter += 1;
            }
        }
        //If that is the only person then s/he wins.
        if (winnerCounter == 1)
        {
            cout << nameOfTheWinner << " has won with " << maxPoint << " pairs." << endl;
        }
        //Else it's a tie
        else if (winnerCounter > 1)
        {
            cout << "Tie of " << winnerCounter << " players with " << maxPoint << " pairs." << endl;
        }
    }
}

int main()
{
    Game_board_type game_board;
    vector<Player> playerVect;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // More code
    bool quitStatus = false;
    //Asking for number of playrs and their name
    askNumberAndNameOfPlayer(playerVect);
    //Printing the board once
    print(game_board);

    //Games continues so long it has not been quit or there is still cards left to be played
    while (quitStatus == false && allCardsEmpty(game_board) == false)
    {
        turnCard(playerVect, game_board, quitStatus);
    }
    //Game over and determine the winner
    if (allCardsEmpty(game_board) && quitStatus == false)
    {
        cout << "Game over!" << endl;
        determineWinner(playerVect);
    }

    //If quit, give a message and return with EXIT_SUCCESS
    if (quitStatus)
    {
        cout << GIVING_UP << endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

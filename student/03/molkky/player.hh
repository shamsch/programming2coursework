#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
    Player(string playerName);
    string get_name() const;
    void add_points(int pts);
    bool has_won();
    int get_points() const;

private:
    string playerName_;
    int points_ = 0;
    bool won_ = false;
};

#endif
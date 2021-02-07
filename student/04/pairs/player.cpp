/*
Program author ( Fill with your own info )
 * Name: Shamsur Raza Chowdhury
 * Student number:050359798
 * UserID: rvshch 
 * E-Mail: shamsurraza.chowdhury@tuni.fi
*/

#include "player.hh"
#include <iostream>
#include <vector>


// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.

Player::Player(const std::string& name) : name_(name){
    
}

std::string Player::get_name() const {
    return name_;
}

unsigned int Player::number_of_pairs() const {
    return numberOfPairs_/2;
}

void Player::add_card(Card& card) {
    card.remove_from_game_board();
    numberOfPairs_+=1;
}

void Player::print() const {
   std::cout<<"*** "<<name_<<" has "<<numberOfPairs_/2<<" pair(s)."<<std::endl;
}

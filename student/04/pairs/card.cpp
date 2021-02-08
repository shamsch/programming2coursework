/*
Program author ( Fill with your own info )
 * Name: Shamsur Raza Chowdhury
 * Student number:050359798
 * UserID: rvshch 
 * E-Mail: shamsurraza.chowdhury@tuni.fi
*/

#include "card.hh"
#include <iostream>

Card::Card():
    letter_(EMPTY_CHAR), visibility_(EMPTY)
{

}

Card::Card(const char c):
    letter_(c), visibility_(HIDDEN)
{

}

void Card::set_letter(const char c)
{
    letter_ = c;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::get_letter() const
{
    return letter_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}

void Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;
    }
    else // if(visibility_ == EMPTY)
    {
        std::cout << "Cannot turn an empty place." << std::endl;
    }
}

void Card::print() const
{
    // Write implementation here
    if (visibility_ == OPEN)
    {
        std::cout<<letter_;
    }
    else if (visibility_ == HIDDEN){
        std::cout<<HIDDEN_CHAR;
    }
    else{
        std::cout<<EMPTY_CHAR;
    }
    
}

void Card::remove_from_game_board()
{
    visibility_ = EMPTY;
    set_letter(EMPTY_CHAR);
}

#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(std::string playerName):playerName_(playerName){

}

string Player::get_name() const{
    return playerName_;
}

void Player::add_points(int pts){
    points_+=pts;
    if (points_>50){
        points_=25;
        cout<<playerName_<<" gets penalty points!"<<endl;
    }
}

bool Player::has_won(){
    if(points_==50){
        won_= true;
    }
    else{
        won_=false;
    }
    return won_;
}

int Player::get_points() const{
    return points_;
}
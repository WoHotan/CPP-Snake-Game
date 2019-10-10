#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <locale>
#include <algorithm>

using namespace std;
class Player{
    
private:
        std::string _playerName;

public:
        Player();
        string getName(){ return playerName; }
        bool continueGame();
        void input();     
}
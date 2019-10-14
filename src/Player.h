#ifndef PLAYER_H
#define PLAYER_H

#include <string>


using namespace std;
class Player{
    
private:
        string _playerName;

public:
        Player();
        string getName(){ return _playerName; }
        bool continueGame();
        void upperCase(string &option);     
};

#endif
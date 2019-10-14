#include "Player.h"
#include <iostream>
#include <locale>
#include <algorithm>

Player::Player(){
    // input player name;
    string name;
    cout << "Player name: " << endl;
    cin >> name;
    _playerName = name;
}

void Player::upperCase(string  &t){
    
}

bool Player::continueGame(){
    // if play continue the game after gaime over or not
    while(true){
        string option;
        cout << "Play again?(yes/no): " << endl;
        // get player input
        cin >> option;
        transform(option.begin(), option.end(), option.begin(), ::toupper);
        if((option == "yes") || (option == "y") || (option == "\n")){
            return true;
        }
        else if ((option == "no") || (option == "n")){
            return false;
        }
        else{
            cout << "Incorrect input. Please try again." << endl;
            continue;
        }

    }
}

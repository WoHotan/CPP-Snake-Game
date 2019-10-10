#include "Player.h"
#include <iostream>
#include <locale>
#include <algorithm>

using namespace std;
Player::Player(){
    // input player name;
    string name;
    cout << "Player name: "; << endl;
    input<string>(name);
    _playerName = name;
}

void Player::input(string &t){
    char c;
    cin.get(c);
    if(c != "\n"){
        cin.putback(c);
        cin >> t;
        cin.get();
    }
}
bool Player::continueGame(){
    while(true){
        string option;
        cout << "Play again?(yes/no): "; << endl;
        input<string>(option);
        transform(option.begin(), option.end(), [](char& c) {tolower(c)});
        if((option == "yes") || (option == "y")){
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

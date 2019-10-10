Player::Player(){
    // input player name;
    string name;
    cout << "Player name: "; << endl;
    input<string>(name);
    _playerName = name;
}

template <typename T>
void Player::input(T &t){
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

#include "GameData.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

GameData::GameData(){
    openFile();
    file.seekg(0, ios::end);
    if(file.tellg() == 0){
        file << "Player Score Size\n";
    }
    cloaseFile();
}

void GameData::writeFile(string name, int sore, int size){
    //write player's name/sore/size
    openFile();
    file << name << " " << sore << " " << size << endl;
    cloaseFile(); 

}

void GameData::sorteData(){
    // sort the data via sore
    vector<tuple<int, int, string>> data;
    openFile();
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        istringstream linestream(line);
        vector<string> lineData;
        string meg;
        
    }
    
}
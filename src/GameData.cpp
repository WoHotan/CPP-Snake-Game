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
    closeFile();
}

void GameData::writeFile(string name, int sore, int size){
    //write player's name/sore/size
    openFile();
    file << name << " " << sore << " " << size << endl;
    closeFile(); 

}

void GameData::sortData(){
    // sort the data via sore
    vector<tuple<int, int, string>> data;
    openFile();
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        istringstream linestream(line);
        vector<string> lineData;
        string info;
        // add player/sore/size to vector
        while(getline(linestream, info, ' ')) {
            lineData.push_back(info);
        }
        // add tuples(sore, size, name) to vector<tuple>
        data.push_back(make_tuple(stoi(lineData[1]), stoi(lineData[2]), lineData[0]));
        
    }
    closeFile();
    // sort tuple via score;
    sort(data.begin(), data.end());
    // store to data file
    file.open("game_data.txt", fstream::out | fstream::trunc);
    // title
    file << "Player Score Size" << endl;
    for(int i = data.size(); i > 0; i--){
        // write name score size to file
        file << get<2>(data[i - 1]) << " " << get<0>(data[i - 1]) << " " << get<1>(data[i - 1]) << "\n";
    }
    closeFile();
    
}

void GameData::openFile(){
    // open a file
    file.open("game_data.txt", fstream::in | fstream::out | fstream::app);
}

void GameData::closeFile(){
    file.close();
}

void GameData::topScore3(){
    // print top 3 player'scores to the screen
    int i = 0;
    string line;
    sortData();
    openFile();
    //ignore title
    getline(file, line);
    //print top 3
    cout << "*****************************************" << endl;
    cout << "Top 3 player: " << "scores: " << "size: " << endl;
    while(getline(file, line) && (i < 5)){
        istringstream linestream(line);
        vector<string> lineData;
        string info;
        // add player score and size to vector
        while(getline(linestream, info, ' ')){
            lineData.push_back(info);
        }
        i++;
        cout << i << "-" + lineData[0] + ": Score " + lineData[1] + "- Snake Size " + lineData[2] << endl;
        
    } 
    cout << "*****************************************" << endl;
}
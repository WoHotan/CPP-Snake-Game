#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <fstream>
#include <string>
#include <tuple>

using namespace std;

class GameData
{
private:
    fstream file;
public:
    GameData();
    void writeFile(string name, int score, int size);
    //void writeFile(string name, int score, int size, string rewrite);
    void openFile();
    void closeFile();
    void sortData();
    void topScore3();
    string getHighestScore();
};
#endif
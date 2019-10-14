#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Player.h"
#include "GameData.h"

using namespace std;
int main() {
  constexpr size_t kFramesPerSecond{60};
  constexpr size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr size_t kScreenWidth{640};
  constexpr size_t kScreenHeight{640};
  constexpr size_t kGridWidth{32};
  constexpr size_t kGridHeight{32};
  
  GameData data;
  Player player;
  while (true)
  {
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);
    game.Run(controller, renderer, kMsPerFrame, player);
    // get palyer game dada
    string name = player.getName();
    int score = game.GetScore();
    int size = game.GetSize();
    // Print player game data
    cout << "Game has terminated successfully!\n";
    cout << "Score: " << game.GetScore() << "\n";
    cout << "Size: " << game.GetSize() << "\n";
    // write player game data
    data.writeFile(name, score, size);
    // kill render
    renderer.~Renderer();
    // play again or not
    if(! player.continueGame()){
      break;
    }
  }
  data.topScore3();
  return 0;
}
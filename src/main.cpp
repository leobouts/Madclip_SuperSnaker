#include <iostream>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int Game::food_counter = 0;

int main() {

  int user_chose = 0;

  std::cout << "======Welcome to SuperSnaker=======" << std::endl;
  std::cout << "1. Play" << std::endl;
  std::cout << "2. View $$ Score" << std::endl;
  std::cout << "3. show this menu" << std::endl;
  std::cout << "4. Exit" << std::endl;
  
  std::cout << "===================================" << std::endl;
  std::cout << "Please Choose an Option..." << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  while(1){
    
    std::cin >> user_chose;
    
    char c ;

    if(!(user_chose) || ( std::cin.get(c) && !std::isspace(c) || user_chose < 1))
    {

      std::cout << "-----------------------------------" << std::endl;
      std::cout << "Please enter a valid option" << std::endl;
      std::cout << "(insert 3 to list options)" << std::endl;
      std::cout << "-----------------------------------" << std::endl;
      std::cin.clear();
      std::cin.ignore( 500, '\n' );

    }
    else if(user_chose ==1)
    {

      constexpr std::size_t kFramesPerSecond{60};
      constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
      constexpr std::size_t kScreenWidth{640};
      constexpr std::size_t kScreenHeight{640};
      constexpr std::size_t kGridWidth{10};
      constexpr std::size_t kGridHeight{10};

      Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      Controller controller;
      Game game(kGridWidth, kGridHeight);
      game.Run(controller, renderer, kMsPerFrame);

      std::cout << "Game has terminated successfully!\n";
      std::cout << "Score: " << game.GetScore() << "\n";
      std::cout << "Size: " << game.GetSize() << "\n";
      std::cout << "-----------------------------------" << std::endl;
      std::cout << "Please input your next option..." << std::endl;
      std::cout << "-----------------------------------" << std::endl;

    }
    else if (user_chose==2)
    {

      std::ifstream input("../score.txt");
      std::string tempScore="";

      int highScore = 0 ;

      input >> tempScore;
      
      if(tempScore!="")
      {
        highScore = std::stoi(tempScore);
      }

      std::cout << "High Score: " << highScore << std::endl;
      std::cout << "-----------------------------------" << std::endl;
      std::cout << "Please input your next option..." << std::endl;
      std::cout << "-----------------------------------" << std::endl;


    }
    else if (user_chose == 3)
    {
      
      std::cout << "###################################" << std::endl;
      std::cout << "Available Options:" << std::endl;
      std::cout << "1. Play" << std::endl;
      std::cout << "2. View $$ Score" << std::endl;
      std::cout << "3. show this menu" << std::endl;
      std::cout << "4. Exit" << std::endl;
      std::cout << "###################################" << std::endl;
      std::cout << "Please Choose an Option..." << std::endl;
      std::cout << "-----------------------------------" << std::endl;
    }
    else if (user_chose == 4)
    {
      std::cout << "Don't forget to hustle..."<<std::endl;
      std::cout << "===================================" << std::endl;

      return 0;
    }
    else
    {
      std::cout << "-----------------------------------" << std::endl;
      std::cout << "Please enter a valid option" << std::endl;
      std::cout << "(insert 3 to list options)" << std::endl;
      std::cout << "-----------------------------------" << std::endl;
    }
  }

  return 0;
}

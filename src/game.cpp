#include "game.h"
#include <iostream>
#include <fstream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {

  //Read the high score
  std::ifstream input("../score.txt");
  std::string tempScore="";

  input >> tempScore;

  if(tempScore == "")
  {
    high_score = 0;
  }
  else
  {
    high_score = std::stoi(tempScore);
  }

  input.close();

  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, high_score);
      frame_count = 0;
      title_timestamp = frame_end;

      //save current score
      std::ofstream output("../score.txt");
      output << high_score;
      output.close();
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      if(Game::food_counter != 0 && Game::food_counter%4 == 0)
      {
        points = 4;
      }
      else if(Game::food_counter != 0 && Game::food_counter%9 == 0)
      {
        points = 9;
      }
      else
      {
        points = 1;
      }

      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    
    score+= points;

    //update highscore
    if(score > high_score) 
      high_score = score; 

    Game::food_counter++;

    PlaceFood();

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.005;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
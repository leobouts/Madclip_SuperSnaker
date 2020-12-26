#include "renderer.h"
#include "game.h"
#include <iostream>
#include <string>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  double degrees;
  block.w = screen_width / (grid_width);
  block.h = screen_height / (grid_height);

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  block.x = food.x * block.w;
  block.y = food.y * block.h;


  //rendering special food
  if(Game::food_counter !=0 && Game::food_counter%4 == 0){
    SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/kotero.bmp")), NULL, &block);
  }
  else if (Game::food_counter !=0 && Game::food_counter%9 == 0)
  {
    SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/elikoptero.bmp")), NULL, &block);
  }
  else
  {
    SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/cash.bmp")), NULL, &block);
  } 

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 234, 170, 0, 255);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;

  if (snake.alive) {

      
    switch (snake.direction) 
    {
      case Snake::Direction::kUp:
        SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/madclip-top.bmp")), NULL, &block);
        break;
      case Snake::Direction::kRight:
        SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/madclip-right.bmp")), NULL, &block);
        break;
      case Snake::Direction::kDown:
        SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/madclip-down.bmp")), NULL, &block);
        break;
      case Snake::Direction::kLeft:
        SDL_RenderCopy(sdl_renderer,SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP("../resources/madclip-left.bmp")), NULL, &block);
        break;
    }
    
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }


  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}



void Renderer::UpdateWindowTitle(int score, int fps, int high_score) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

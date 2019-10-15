#include "renderer.h"
#include <iostream>

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

  // Initialize font
  if(TTF_Init() < 0){
    cerr << "SDL Font could not initialize." << endl;
    cerr << "TTF_Error: " << TTF_GetError() << endl;
  }
  sdl_font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSansBold.ttf", 60);
  if(nullptr == sdl_font){
    cerr << "SDL Font could not loaded." << endl;
    cerr << "TTF_Error: " << TTF_GetError() << endl;
  }
}

Renderer::~Renderer() {
  TTF_CloseFont(sdl_font);
  TTF_Quit();
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Set color to black
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0x00);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

int Renderer::RenderMenu(std::string str) {
  Uint32 time;
  int x, y;
  const int NUMMENU = 2;
  const char *labels[NUMMENU];
  labels[0] = str.c_str();
  labels[1] = "Quit";
  SDL_Surface *s_menus[NUMMENU];
  SDL_Texture *t_menus[NUMMENU];
  bool selected[NUMMENU] = {0, 0};
  SDL_Color White = {255, 255, 255, 0};
  SDL_Color Red = {255, 0, 0, 0};
  SDL_Surface *screen = SDL_GetWindowSurface(sdl_window);

  s_menus[0] = TTF_RenderText_Solid(sdl_font, labels[0], White);
  s_menus[1] = TTF_RenderText_Solid(sdl_font, labels[1], White);

  t_menus[0] = SDL_CreateTextureFromSurface(sdl_renderer, s_menus[0]);
  t_menus[1] = SDL_CreateTextureFromSurface(sdl_renderer, s_menus[1]);

  SDL_Rect pos[NUMMENU];
  pos[0].x = screen->w/2 - s_menus[0]->w/2;
  pos[0].y = screen->h/2 - s_menus[0]->h;
  pos[0].w = s_menus[0]->w;
  pos[0].h = s_menus[0]->h;
  pos[1].x = screen->w/2 - s_menus[0]->w/2;
  pos[1].y = screen->h/2 + s_menus[0]->h;
  pos[1].w = s_menus[1]->w;
  pos[1].h = s_menus[1]->h;

  SDL_Event event;
  while(1)
  {
    time = SDL_GetTicks();
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          for (int i = 0; i < NUMMENU; i++) {
            SDL_FreeSurface(s_menus[i]);
            SDL_DestroyTexture(t_menus[i]);
          }
          return 1;
        case SDL_MOUSEMOTION:
          x = event.motion.x;
          y = event.motion.y;
          for(int i = 0; i < NUMMENU; i += 1) {
            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
            {
              if(!selected[i])
              {
                selected[i] = 1;
                SDL_FreeSurface(s_menus[i]);
                SDL_DestroyTexture(t_menus[i]);
                s_menus[i] = TTF_RenderText_Solid(sdl_font, labels[i], Red);
                t_menus[i] = SDL_CreateTextureFromSurface(sdl_renderer, s_menus[i]);
              }
            }
            else
            {
              if(selected[i])
              {
                selected[i] = 0;
                SDL_FreeSurface(s_menus[i]);
                SDL_DestroyTexture(t_menus[i]);
                s_menus[i] = TTF_RenderText_Solid(sdl_font, labels[i], White);
                t_menus[i] = SDL_CreateTextureFromSurface(sdl_renderer, s_menus[i]);
              }
            }
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          x = event.button.x;
          y = event.button.y;
          for(int i = 0; i < NUMMENU; i += 1) {
            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
            {
              for (int i = 0; i < NUMMENU; i++) {
                SDL_FreeSurface(s_menus[i]);
                SDL_DestroyTexture(t_menus[i]);
              }
              return i;
            }
          }
          break;
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE)
          {
            for (int i = 0; i < NUMMENU; i++) {
              SDL_FreeSurface(s_menus[i]);
              SDL_DestroyTexture(t_menus[i]);
            }
            return 0;
          }
      }
    }

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdl_renderer);

    // Render menu items
    for (int i = 0; i < NUMMENU; i++) {
      SDL_RenderCopy(sdl_renderer, t_menus[i], NULL, &pos[i]);
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);

    if(1000/30 > (SDL_GetTicks()-time))
      SDL_Delay(1000/30 - (SDL_GetTicks()-time));
  }
}

void Renderer::UpdateWindowTitle(int score, int fps, string userName) {
  string title{"Player: " + userName + "  Snake Score: " + std::to_string(score) + "  FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

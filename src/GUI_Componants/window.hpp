#pragma once

// Import
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <string>

namespace GUI_COMP {
class Window {
private:
  int x, y, w, h;
  std::string title;
  SDL_Window* win;
  SDL_Renderer* ren;

public: // Constructors and Destructor
  // Partal constructor no x and y
  Window(int w, int h, std::string title)
      : x(0), y(0), w(w), h(h), title(title),
        win(SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN)),
        ren(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) {
    if (!win || !ren) {
      std::cerr << "Error creating window and/or renderer : " << SDL_GetError()
                << std::endl;
      SDL_Quit();
      std::exit(1);
    }
  }

  // Partial with no x, y or title
  Window(int w, int h)
      : x(0), y(0), w(w), h(h), title("GUI++"),
        win(SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN)),
        ren(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) {
    if (!win || !ren) {
      std::cerr << "Error creating window and/or renderer : " << SDL_GetError()
                << std::endl;
      SDL_Quit();
      std::exit(1);
    }
  }

  // Partial with only title
  Window(std::string title)
      : x(0), y(0), w(200), h(200), title(title),
        win(SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN)),
        ren(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) {
    if (!win || !ren) {
      std::cerr << "Error creating window and/or renderer : " << SDL_GetError()
                << std::endl;
      SDL_Quit();
      std::exit(1);
    }
  }

  // Full constructor
  Window(int x, int y, int w, int h, std::string title)
      : x(x), y(y), w(w), h(h), title(title),
        win(SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN)),
        ren(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) {
    if (!win || !ren) {
      std::cerr << "Error creating window and/or renderer : " << SDL_GetError()
                << std::endl;
      SDL_Quit();
      std::exit(1);
    }
  }

  // Destructor
  ~Window() {
    if (win) {
      SDL_DestroyWindow(win);
    }

    if (ren) {
      SDL_DestroyRenderer(ren);
    }
  }

public: // The window commands
  void renderLoop() {
    SDL_Event e;
    bool run = true;

    while (run) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          run = false;
        }
      }

      SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
      SDL_RenderClear(ren);
      // Put shit here

      // End of shit
      SDL_RenderPresent(ren);
      SDL_Delay(16); // TODO Later make fps ajustable
    }
  }
};
} // namespace GUI_COMP

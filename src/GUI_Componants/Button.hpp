#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

namespace GUICOMP {
class Button {
private:
  int x, y, w, h;
  const char* text;
  SDL_Color buttonColor;
  TTF_Font* textFont;

  SDL_Color textColor = {0, 0, 0, 255};

  // Cached texture
  SDL_Texture* cached_texture;

public:
  // Partial without text
  Button(int x, int y, int w, int h, SDL_Color buttonColor, TTF_Font* font)
      : x(x), y(y), w(w), h(h), text(" "), buttonColor(buttonColor), textFont(font),
        cached_texture(nullptr) {}

  // Full constructor
  Button(int x, int y, int w, int h, std::string t, SDL_Color buttonColor,
         TTF_Font* font)
      : x(x), y(y), w(w), h(h), text(t.c_str()), buttonColor(buttonColor),
        textFont(font), cached_texture(nullptr) {}

  // Destructor
  ~Button() {
    if (textFont) {
      TTF_CloseFont(textFont);
    }

    if (cached_texture) {
      SDL_DestroyTexture(cached_texture);
    }
  }

  void createTexture(SDL_Renderer* ren) {

  }

  void render(SDL_Renderer* ren) {

  }
};
} // namespace GUICOMP

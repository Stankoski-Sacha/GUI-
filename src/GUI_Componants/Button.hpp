#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <optional>
#include <string>

namespace GUICOMP {
class Button {
private:
  int x, y, w, h;
  std::optional<std::string> text = std::nullopt;
  SDL_Color buttonColor;
  TTF_Font* textFont;

  SDL_Color textColor = {0, 0, 0, 255};

  // Cached texture
  SDL_Texture* cached_texture;

public:
  // Partial constructor without text or x,y
  Button(int w, int h, SDL_Color buttonColor, TTF_Font* font)
      : x(0), y(0), w(w), h(h), buttonColor(buttonColor), textFont(font),
        cached_texture(nullptr) {}

  // Partial without text
  Button(int x, int y, int w, int h, SDL_Color buttonColor, TTF_Font* font)
      : x(x), y(y), w(w), h(h), buttonColor(buttonColor), textFont(font),
        cached_texture(nullptr) {}

  // Partial constructor with only text
  Button(int w, int h, std::string text, SDL_Color buttonColor, TTF_Font* font)
      : x(0), y(0), w(w), h(h), text(text), buttonColor(buttonColor),
        textFont(font), cached_texture(nullptr) {}

  // Full constructor
  Button(int x, int y, int w, int h, std::string text, SDL_Color buttonColor,
         TTF_Font* font)
      : x(x), y(y), w(w), h(h), text(text), buttonColor(buttonColor),
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
};
} // namespace GUICOMP

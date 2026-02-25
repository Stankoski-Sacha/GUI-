#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
private:
  int x, y, w, h;
  std::string text;
  SDL_Color buttonColor = {255,255,255,255};
  TTF_Font* textFont;

  SDL_Color textColor = {255, 255, 255, 255};

  // Cached texture
  SDL_Texture* cached_texture;

public:
  // Partial without text
  Button(int x, int y, int w, int h, TTF_Font* font)
      : x(x), y(y), w(w), h(h), text(" "), textFont(font), cached_texture(nullptr) {}

  // Full constructor
  Button(int x, int y, int w, int h, std::string t, TTF_Font* font)
      : x(x), y(y), w(w), h(h), text(t), textFont(font), cached_texture(nullptr) {}

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
	SDL_Surface* surf = TTF_RenderText_Solid(textFont, text.c_str(), textColor);
	cached_texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
  }

  void render(SDL_Renderer* ren) {
	if (not cached_texture) { createTexture(ren); }
	
	SDL_Rect renderRect = {x, y, w, h};
	SDL_RenderCopy(ren, cached_texture, nullptr, &renderRect);
  }
};


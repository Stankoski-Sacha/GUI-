#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
private:
  int x, y, w, h;
  std::string text;
  SDL_Color buttonColor = {100,100,100,255};
  TTF_Font* textFont;

  SDL_Color textColor = {0, 0, 0, 255};

  // Size integer for the texture not the other
  int textW = 0, textH = 0;

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
   	if (cached_texture) {
	       SDL_DestroyTexture(cached_texture);
	}	       
  }

  void createTexture(SDL_Renderer* ren) {
	SDL_Surface* surf = TTF_RenderText_Solid(textFont, text.c_str(), textColor);
	cached_texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_QueryTexture(cached_texture, NULL, NULL, &textW, &textH);
	SDL_FreeSurface(surf);
  }

  void render(SDL_Renderer* ren) {
	if (not cached_texture) { createTexture(ren); }

	if (textW > w) w = textW;
	if (textH > h) h = textH;
	
	SDL_Rect colorRect = {x, y, w, h};
	SDL_Rect textureRect = {x, y, textW, textH};
	SDL_SetRenderDrawColor(ren, 100,100,100,255);
	SDL_RenderFillRect(ren, &colorRect);
	SDL_RenderCopy(ren, cached_texture, nullptr, &textureRect);
  }
};


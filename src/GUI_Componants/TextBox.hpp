#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <optional>
#include <iostream>

class TextBox {
private:
	std::string text;
	int x, y, w, h;
	bool editable;
	TTF_Font* font;

	// Cached texture to avoid recreating a not changed texture
	SDL_Texture* cached_texture;
	
public:
	// Partial constructor without the text 
	TextBox(int x, int y, int w, int h, bool edit, TTF_Font* font) :
		text(" "), x(x), y(y), w(w), h(h), editable(edit), font(font),
		cached_texture(nullptr) {}

	// Full constructor 
	TextBox(std::string text, int x, int y, int w, int h, bool edit, TTF_Font* font) :
		text(text), x(x), y(y), w(w), h(h), editable(edit), font(font),
		cached_texture(nullptr) {}

	// Destructor 
	~TextBox() {
		if (cached_texture) {
			SDL_DestroyTexture(cached_texture);
		}
	}

	void createTexture(SDL_Renderer* ren) {

	}

	void render(SDL_Renderer* ren) {

	}

};

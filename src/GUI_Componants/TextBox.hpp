#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextBox {
private:
	std::string text;
	int x, y, w, h;
	bool editable;
	TTF_Font* font;

	// Cached texture to avoid recreating a not changed texture
	SDL_Texture* cached_texture;

	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Color bgColor = {100, 100, 100, 255};

	bool editMode = false;
	int textW = 0, textH = 0;
	
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
		SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), textColor);
		cached_texture = SDL_CreateTextureFromSurface(ren, surf);
		SDL_QueryTexture(cached_texture, NULL, NULL, &textW, &textH);
		SDL_FreeSurface(surf);
	}

	void render(SDL_Renderer* ren) {
		if (not cached_texture) {
			createTexture(ren);
		}

		SDL_Rect colorRect = {x, y, w, h};
		SDL_Rect textureRect = {x, y, textW, textH};
		SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderFillRect(ren, &colorRect);
		SDL_RenderCopy(ren, cached_texture, NULL, &textureRect);
	}

	void handleInput(SDL_Renderer* ren, SDL_Event e) {
		if (not editable) {
			return;
		}

		if (editMode) {
			SDL_StartTextInput();
		}		

		if (!editMode) {
			SDL_StopTextInput();
		}
	}

	bool isInside(int mx, int my) {
		return (mx >= x && mx <= x + w &&
            my >= y && my <= y + h);
	}

	void toggleEdit() {
		editable = !editable;
	}
};


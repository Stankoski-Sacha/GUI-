#include <SDL2/SDL.h>
#include <string>

class CheckBox {
private:
	int x, y, w, h;
	bool isChecked = false;

	// Color of the surround of the button
	SDL_Color borderColor = {0, 0, 0, 255};
	SDL_Color white = {255, 255, 255, 255};

	// The rectangles
	SDL_Rect outsideRect = {x, y, w, h};
	SDL_Rect insideRect = {x - static_cast<int>(x / 10), 
			y - static_cast<int>(y / 10), w - static_cast<int>(w / 10),
			h - static_cast<int>(h / 10)
	};

public:	
	CheckBox(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	~CheckBox() = default;
	
	void render(SDL_Renderer* ren) {
		SDL_SetRenderDrawColor(ren, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderFillRect(ren, &outsideRect);
		SDL_SetRenderDrawColor(ren, white.r, white.g, white.b, white.a);
		SDL_RenderFillRect(ren, &insideRect);

	}

	void switchBox(SDL_Renderer* ren) {
		if (isChecked) {
			// Remove them
			SDL_SetRenderDrawColor(ren, white.r, white.g, white.b, white.a);
			SDL_RenderDrawLine(ren, x, y, x+w, y+h);
			SDL_RenderDrawLine(ren, x+w, y+w, x+h, y+h);
			return;
		}

		// Add the lines 
		SDL_SetRenderDrawColor(ren, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderDrawLine(ren, x, y, x+w, y+h);
		SDL_RenderDrawLine(ren, x+w, y+w, x+h, y+h);


	}

	bool isInside(int mx, int my) const {
		return (mx >= x && mx <= x + w &&
            my >= y && my <= y + h);
	}
};

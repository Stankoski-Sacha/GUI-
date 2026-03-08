#include <SDL2/SDL.h>


class CheckBox {
private:
	int x, y, w, h;
	bool isChecked = false;

	// Color of the surround of the button
	SDL_Color borderColor = {0, 0, 0, 255};
	SDL_Color white = {255, 255, 255, 255};

	SDL_Rect outsideRect;
	SDL_Rect insideRect;

public:	
	CheckBox(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
		// The rectangles
		outsideRect = {x, y, w, h};
		constexpr float innerRatio = 0.75f;   // 75% to have a cool checkbox

		int innerW = static_cast<int>(w * innerRatio);
		int innerH = static_cast<int>(h * innerRatio);

		// center it
		int offsetX = (w - innerW) / 2;
		int offsetY = (h - innerH) / 2;

		insideRect = {x + offsetX, y + offsetY, innerW, innerH};
	}


	~CheckBox() = default;
	
	void render(SDL_Renderer* ren) {
	    SDL_SetRenderDrawColor(ren, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	    SDL_RenderFillRect(ren, &outsideRect);

	    SDL_SetRenderDrawColor(ren, white.r, white.g, white.b, white.a);
	    SDL_RenderFillRect(ren, &insideRect);

	    if (isChecked) {
		SDL_SetRenderDrawColor(ren, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderDrawLine(ren, x, y, x+w, y+h);
		SDL_RenderDrawLine(ren, x+w, y, x, y+h);
	    }
	}

	void switchBox(SDL_Renderer* ren) {
		isChecked = !isChecked;
	}

	bool isInside(int mx, int my) const {
		return (mx >= x && mx <= x + w &&
            my >= y && my <= y + h);
	}
};

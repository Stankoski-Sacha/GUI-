#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

class Slider {
private:
	int x, y, w, h;
	TTF_Font* font;

	int minVal, maxVal;
	
	// SDL Element constants 
	SDL_Color borderColor = {0, 0, 0, 255}; // Black border 
	SDL_Color insideColor = {255, 255, 255, 255}; // White color for the sliding area 
	SDL_Color sliderColor = {100, 100, 100, 255}; // Gray for the slider you slide 
	SDL_Rect outlineRect, insideRect;
	int innerW = 0, innerH = 0;

	// Slider variables 
	int centerX = 0, centerY = 0, sliderRadius = 0;
	bool isClicked = false;
	
	// Cached texture 
	SDL_Texture* cached_texture;

public:
	Slider(int x, int y, int w, int h, TTF_Font* f, int min, int max) : 
		x(x), y(y), w(w), h(h), font(f), minVal(min), maxVal(max), 
		cached_texture(nullptr) 
	{
		outlineRect = {x, y, w, h};
		auto innerRatio = 0.8f;

		innerW = static_cast<int>(w * innerRatio);
		innerH = static_cast<int>(h * innerRatio);

		int offsetX = (w - innerW) / 2;
		int offsetY = (h - innerH) / 2;

		insideRect = {offsetX, offsetY, innerW, innerH};

		centerX = insideRect.x + insideRect.w / 2; 
		centerY = insideRect.y + insideRect.h / 2;
		sliderRadius = std::min(insideRect.w, insideRect.h) / 2;
	}

	~Slider() {
		if (cached_texture) {
			SDL_DestroyTexture(cached_texture);
		}
	}

	void render(SDL_Renderer* ren) {
		SDL_SetRenderDrawColor(ren, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderFillRect(ren, &outlineRect);
		SDL_SetRenderDrawColor(ren, insideColor.r, insideColor.g, insideColor.b, insideColor.a);
		SDL_RenderFillRect(ren, &insideRect);

		SDL_SetRenderDrawColor(ren, sliderColor.r, sliderColor.g, sliderColor.b, sliderColor.a);
		drawCircle(ren, centerX, centerY, sliderRadius);	
		
		// TODO Check if the isChecked then move the circle to the pos of the mouse 
		// but not more then the offsetX and offsetY
	}

	void drawCircle(SDL_Renderer* ren, int centerX, int centerY, int radius) {
	    const int diameter = radius * 2;
	    int x = radius - 1;
	    int y = 0;
	    int tx = 1;
	    int ty = 1;
	    int error = tx - diameter;

	    while (x >= y) {
		// Draw horizontal spans instead of individual points
		SDL_RenderDrawLine(ren, centerX - x, centerY + y, centerX + x, centerY + y);
		SDL_RenderDrawLine(ren, centerX - x, centerY - y, centerX + x, centerY - y);
		SDL_RenderDrawLine(ren, centerX - y, centerY + x, centerX + y, centerY + x);
		SDL_RenderDrawLine(ren, centerX - y, centerY - x, centerX + y, centerY - x);

		if (error <= 0) {
		    ++y;
		    error += ty;
		    ty += 2;
		}
		if (error > 0) {
		    --x;
		    tx += 2;
		    error += (tx - diameter);
		}
	    }
	}	

	void switchSliderSelect() {
		isClicked = !isClicked;
	}

	bool isInside(int mx, int my) {
		return (mx >= x && mx <= x + w &&
            my >= y && my <= y + h);
	}


};

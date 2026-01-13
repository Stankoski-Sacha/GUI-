module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <print>
#include <string>
#include <vector>

export module Window;

export namespace GUI_COMP {
class Window {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::string name;
  int x, y, w, h;
  TTF_Font *font;
  Uint32 FLAGS;

  // Elements inside the window

public:
  Window(int x, int y, int w, int h, std::string name, Uint32 FLAGS)
      : window(nullptr), renderer(nullptr), name(name), x(x), y(y), w(w), h(h),
        font(nullptr), FLAGS(FLAGS) {
    window = SDL_CreateWindow(name.c_str(), x, y, w, h, FLAGS);
    if (!window) {
      std::println("Error creating the window : {}", SDL_GetError());
      window = nullptr;
    }

    renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED, -1);
    if (!renderer) {
      std::println("Error creating the renderer : {}", SDL_GetError());
      renderer = nullptr;
    }
  }

  ~Window() {
    if (window) {
      SDL_DestroyWindow(window);
    }

    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }

    if (font) {
      TTF_CloseFont(font);
    }
  }

  // To get the window in order to place objects inside of it
  SDL_Window *getWindow() const { return window; }

  // Main render loop of a Window, where objects are drawn and updated
  void mainRenderLoop() {}
};

} // namespace GUI_COMP

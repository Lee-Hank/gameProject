#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Graphics {
public:
    static bool init(const char* title, int width, int height);
    static void clear();
    static void present();
    static void cleanup();

    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);

    static void renderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    static SDL_Renderer* getRenderer();

private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;
};

#endif

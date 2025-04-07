#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class Graphics {
public:

    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);

    static void drawBorder(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color);

    static void drawPath(SDL_Renderer* renderer, const std::vector<std::pair<int, int>>& path,
                         int cellSize, int offsetX, int offsetY, SDL_Color color);

private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;
};

#endif

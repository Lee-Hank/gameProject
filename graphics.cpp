#include "Graphics.h"

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;

SDL_Texture* Graphics::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    return IMG_LoadTexture(renderer, path.c_str());
}

void Graphics::drawBorder(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::drawPath(SDL_Renderer* renderer, const std::vector<std::pair<int, int>>& path,
                        int cellSize, int offsetX, int offsetY, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int x1 = offsetX + (path[i].second - 1) * cellSize + cellSize / 2;
        int y1 = offsetY + (path[i].first - 1) * cellSize + cellSize / 2;
        int x2 = offsetX + (path[i + 1].second - 1) * cellSize + cellSize / 2;
        int y2 = offsetY + (path[i + 1].first - 1) * cellSize + cellSize / 2;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

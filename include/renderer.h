#ifndef RENDERER_H
#define RENDERER_H

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <string>

class Renderer {
public:
    int WIDTH;
    int HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Renderer(std::string title, int width, int height, int background[4]);
    void render();
    ~Renderer();

    void setPixel(int x, int y, int color[4]);

    void drawLine(int x0, int y0, int x1, int y1, int color[4]);

    void drawSquare(int x, int y, int side, int color[4], bool fill);

    void drawRectangle(int x, int y, int length, int breadth, int color[4], bool fill);

    void shrinkfitPoint(int &x, int &y);

    int randX();
    int randY();

private:
    SDL_Surface* surface;
    SDL_Texture* texture;
};

#endif

#include <renderer.h>
#include <random>


Renderer::Renderer(std::string title, int width, int height, int background[4]) {
    Renderer::WIDTH = width;
    Renderer::HEIGHT = height;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);

    if (surface) {
        for (int y = 0; y < surface->h; y++) {
            for (int x = 0; x < surface->w; x++) {
                Uint32* pixel = (Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x * sizeof(Uint32));
                *pixel = SDL_MapRGBA(surface->format, background[0], background[1], background[2], background[3]);
            }
        }
    }
}

void Renderer::render() {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    Renderer::~Renderer();
}

Renderer::~Renderer() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::setPixel(int x, int y, int color[4]) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        Uint32* pixel = (Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x * sizeof(Uint32));
        *pixel = SDL_MapRGBA(surface->format, color[0], color[1], color[2], color[3]);
    }
}

void Renderer::drawLine(int x0, int y0, int x1, int y1, int color[4]) {
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;

    int error = dx + dy, e2, x2, y2;

    while (true) {
        setPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1) break;

        e2 = 2*error;
        if (e2 >= dy) {
            if (x0 == x1) break;
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) break;
            error += dx;
            y0 += sy;
        }
    }
}

void Renderer::drawSquare(int x, int y, int side, int color[4], bool fill) {
    drawLine(x, y, x+side, y, color);
    drawLine(x, y, x, y+side, color);
    drawLine(x+side, y, x+side, y+side, color);
    drawLine(x, y+side, x+side, y+side, color);

    if (fill) {
        for (int i = x+1; i < x+side; i++) {
            drawLine(i, y+1, i, y+side-1, color);
        }
    }
}

void Renderer::drawRectangle(int x, int y, int length, int breadth, int color[4], bool fill) {
    drawLine(x, y, x+length, y, color);
    drawLine(x, y, x, y+breadth, color);
    drawLine(x+length, y, x+length, y+breadth, color);
    drawLine(x, y+breadth, x+length, y+breadth, color);

    if (fill) {
        for (int i = x+1; i < x+length; i++) {
            drawLine(i, y+1, i, y+breadth-1, color);
        }
    }
}

void Renderer::shrinkfitPoint(int &x, int &y) {
    x = std::min(std::max(0, x), WIDTH);
    y = std::min(std::max(0, y), HEIGHT);
}

int Renderer::randX() {
    return rand() % WIDTH;
}

int Renderer::randY() {
    return rand() % HEIGHT;
}

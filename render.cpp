#include <iostream>
#include <renderer.h>


int main() {
    int black[4] = {0, 0, 0, 255};
    int white[4] = {255, 255, 255, 255};
    int red[4] = {255, 0, 0, 255};
    int green[4] = {0, 255, 0, 255};
    int blue[4] = {0, 0, 255, 255};

    Renderer renderer("Drawing some shit", 800, 600, black);
    renderer.drawLine(100, 100, 700, 350, white);
    renderer.drawLine(669, 126, 88, 420, red);
    renderer.drawSquare(200, 188, 169, green, true);
    renderer.drawRectangle(350, 350, 325, 150, blue, false);
    renderer.render();

    return 0;
}

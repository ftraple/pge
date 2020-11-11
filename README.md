# PGE - Pixel Game Engine

PGE is a simple, fast cross-platform 2D game engine. It provides access to windowing, graphics, audio and controllers. It is written in C.

## Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include <pge/pixel-game-engine.h>

int main() {
    // Create window
    int width = 160;
    int height = 120;
    int pixel_scale = 4;
    int fps = 60;
    if (!pge_window_create("PGE - Pixel Example", width, height, pixel_scale, fps, false)) {
        printf("%s\n", pge_pge_get_error());
        return EXIT_FAILURE;
    }
    // Game loop - randomly draw pixels
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        // Set random color
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_current_color(color);
        // Draw pixel
        int x1 = rand() % width;
        int y1 = rand() % height;
        pge_draw_point(x1, y1);
        // Update window
        pge_window_show();
    }
    // Destroy window
    pge_window_destroy();
    return EXIT_SUCCESS;
}
```

## Dependencies

[SDL](https://www.libsdl.org/download-2.0.php) - [SDL_image](https://www.libsdl.org/projects/SDL_image/) - [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/) - [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)

## How To Install

```bash
git clone git@github.com:ftraple/pge.git
cd pge
mkdir build
cd build
cmake ..
make
sudo make install
```

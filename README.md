# PGE - Pixel Game Engine

PGE is a simple, fast cross-platform 2D game engine. It provides access to windowing, graphics, audio, and controllers. It is written in C.

## Content

1. [Example](#example)
2. [How to Install](#how_to_install)
    1. [Linux Installation](#linux_installation) :heavy_check_mark:
    2. [Windows Installation](#windows_installation)
    3. [Mac Installation](#mac_installation)

## Example <a name="example"></a>

```c++
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    int screen_width = 160;
    int screeen_height = 120;
    int pixel_scale = 4;
    int max_fps = 60;
    bool full_screen = false;
    if (!pge_window_create("PGE - Pixel Example",
                           screen_width, screeen_height,
                           pixel_scale, max_fps, full_screen)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop - randomly draw pixels
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        // Set random color
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_set_current_color(color);
        // Draw pixel
        int x1 = rand() % screen_width;
        int y1 = rand() % screeen_height;
        pge_draw_pixel(x1, y1);
        // Update window
        pge_window_draw();
    }
    // Destroy window
    pge_window_destroy();
    return EXIT_SUCCESS;
}
```

## How To Install <a name="how_to_install"></a>

You can check the dependencies websites for detailed information.

[SDL](https://www.libsdl.org/download-2.0.php) - [SDL_image](https://www.libsdl.org/projects/SDL_image/) - [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/) - [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)

### Linux Instalation <a name="linux_installation"></a>

First, it is necessary to install all the dependencies to compile the PGE library.

```bash
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-ttf-dev
sudo apt install libsdl2-mixer-dev
```

Then we need to download, compile, and install the library.

```bash
git clone git@github.com:ftraple/pge.git
cd pge
mkdir build
cd build
cmake ..
make
sudo make install
```

### Windows Instalation <a name="windows_installation"></a>

Soon...

### Mac Instalation <a name="mac_installation"></a>

Soon...

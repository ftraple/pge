#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    if (!pge_window_create("PGE - Sound Example", 640, 480, 1, 60, false)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Load sound
    pge_SoundObj music = pge_sound_load("../../../examples/resources/sound/power_pellet.wav");
    if (!music) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop
    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);
        // Select Sound
        pge_draw_set_current_color(PGE_COLOR_BROWN);
        pge_draw_text(10, 10, 2, "Press Button:\nA = play   B = stop\nX = pause  Y = resume");
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_A) &&
            pge_sound_status(music) == PGE_AUDIO_STATUS_STOPED) {
            printf("PGE_CONTROLLER_BUTTON_A - play\n");
            pge_sound_play(music, true);
        }
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_B) &&
            pge_sound_status(music) == PGE_AUDIO_STATUS_PLAYING) {
            printf("PGE_CONTROLLER_BUTTON_B - stop\n");
            pge_sound_stop(music);
        }
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_X) &&
            pge_sound_status(music) == PGE_AUDIO_STATUS_PLAYING) {
            printf("PGE_CONTROLLER_BUTTON_X - pause\n");
            pge_sound_pause(music);
        }
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_Y) &&
            pge_sound_status(music) == PGE_AUDIO_STATUS_PAUSED) {
            printf("PGE_CONTROLLER_BUTTON_Y - resume\n");
            pge_sound_resume(music);
        }
        // Update window
        pge_window_draw();
    }
    // Destroy
    pge_sound_unload(music);
    pge_window_destroy();
    return EXIT_SUCCESS;
}
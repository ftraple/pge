#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Mapping SNES USB gamepad (Add before crate the window)
    char* snes_map = "030000001f08000001e4000010010000,USB gamepad,a:b1,b:b2,x:b0,y:b3,back:b8,start:b9,leftshoulder:b4,rightshoulder:b5,leftx:a0,lefty:a1,rightx:a3,righty:a4";
    int result = pge_controller_add_mapping(snes_map);
    if (pge_controller_add_mapping(snes_map) == -1) {
        printf("Fail to add a new controller mapping.\n");
    }

    // Create window
    int pixel_scale = 2;
    int screen_width = 640 / pixel_scale;
    int screen_height = 480 / pixel_scale;
    if (!pge_window_create("PGE - Music Example", screen_width, screen_height, pixel_scale, 60, false)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Load music
    pge_MusicObj music = pge_music_load("../../../examples/resources/music/gs-16b-2c-44100hz.mp3");
    if (!music) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop
    int controller_id = 0;
    while (pge_window_is_running()) {
        // Capture events
        pge_Event event;
        while (pge_event_wait(&event)) {
            if (event.type == PGE_EVENT_CONTROLLER_DEVICE_ADDED) {
                controller_id = event.controller_device.id;
            }
        }
        // Select Music
        pge_window_clear(PGE_COLOR_BLACK);
        pge_draw_set_current_color(PGE_COLOR_BROWN);
        pge_draw_text(screen_width / 2, screen_height / 2, 2, PGE_ALIGN_CENTER_CENTER, "Press Button:\nA = play   B = stop\nX = pause  Y = resume");
        if (pge_controller_is_active(controller_id)) {
            if (pge_controller_button(controller_id, PGE_CONTROLLER_BUTTON_A) &&
                pge_music_status(music) == PGE_AUDIO_STATUS_STOPED) {
                printf("Controller [%d] Button A - play\n", controller_id);
                pge_music_play(music, true);
            }
            if (pge_controller_button(controller_id, PGE_CONTROLLER_BUTTON_B) &&
                pge_music_status(music) == PGE_AUDIO_STATUS_PLAYING) {
                printf("Controller [%d] Button B - stop\n", controller_id);
                pge_music_stop(music);
            }
            if (pge_controller_button(controller_id, PGE_CONTROLLER_BUTTON_X) &&
                pge_music_status(music) == PGE_AUDIO_STATUS_PLAYING) {
                printf("Controller [%d] Button X - pause\n", controller_id);
                pge_music_pause(music);
            }
            if (pge_controller_button(controller_id, PGE_CONTROLLER_BUTTON_Y) &&
                pge_music_status(music) == PGE_AUDIO_STATUS_PAUSED) {
                printf("Controller [%d] Button Y - resume\n", controller_id);
                pge_music_resume(music);
            }
        }
        // Update window
        pge_window_draw();
    }
    // Destroy
    pge_music_unload(music);
    pge_window_destroy();
    return EXIT_SUCCESS;
}
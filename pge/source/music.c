#include "defines.h"
#include "pixel-game-engine.h"

extern pge_Window *window;

struct pge_Music_t {
    Mix_Music *sdl_music;
};

pge_MusicObj pge_music_load(const char *file_name) {
    pge_MusicObj music_obj = (pge_MusicObj)malloc(sizeof(struct pge_Music_t));
    if (!music_obj) {
        pge_set_error_message("Fail to allocate music memory.");
        return NULL;
    }
    music_obj->sdl_music = Mix_LoadMUS(file_name);
    if (!music_obj->sdl_music) {
        pge_set_error_message("Fail to load music: %s", Mix_GetError());
        return NULL;
    }
    return music_obj;
}

void pge_music_unload(pge_MusicObj music_obj) {
    if (music_obj == NULL) return;
    Mix_FreeMusic(music_obj->sdl_music);
    free(music_obj);
}

void pge_music_play(pge_MusicObj music_obj, bool loop) {
    if (music_obj == NULL) return;
    int loop_num = 1;
    if (loop) loop_num = -1;
    if (Mix_PlayMusic(music_obj->sdl_music, loop_num) == -1) {
        pge_set_error_message("Fail to play the music: %s", Mix_GetError());
    }
}

void pge_music_stop() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
    Mix_HaltMusic();
}

void pge_music_pause() {
    Mix_PauseMusic();
}

void pge_music_resume() {
    Mix_ResumeMusic();
}

pge_AudioStatus pge_music_status() {
    if (Mix_PausedMusic()) {
        return PGE_AUDIO_STATUS_PAUSED;
    }
    if (Mix_PlayingMusic()) {
        return PGE_AUDIO_STATUS_PLAYING;
    }
    return PGE_AUDIO_STATUS_STOPED;
}

void pge_music_volume(int volume) {
    Mix_VolumeMusic(volume);
}

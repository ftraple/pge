#include "defines.h"
#include "pixel-game-engine.h"

extern pge_Window *window;

struct pge_Sound_t {
    Mix_Chunk *sdl_sound;
    int channel;
};

pge_SoundObj pge_sound_load(const char *file_name) {
    pge_SoundObj sound_obj = (pge_SoundObj)malloc(sizeof(struct pge_Sound_t));
    if (!sound_obj) {
        pge_set_error_message("Fail to allocate sound memory.");
        return NULL;
    }
    sound_obj->sdl_sound = Mix_LoadWAV(file_name);
    if (!sound_obj->sdl_sound) {
        pge_set_error_message("Fail to load sound: %s", Mix_GetError());
        return NULL;
    }
    sound_obj->channel = -1;
    return sound_obj;
}

void pge_sound_unload(pge_SoundObj sound_obj) {
    if (sound_obj == NULL) return;
    Mix_FreeChunk(sound_obj->sdl_sound);
    free(sound_obj);
}

void pge_sound_play(pge_SoundObj sound_obj, bool loop) {
    if (sound_obj == NULL) return;
    int loop_num = 1;
    if (loop) loop_num = -1;
    sound_obj->channel = Mix_PlayChannel(-1, sound_obj->sdl_sound, loop_num);
    if (sound_obj->channel == -1) {
        pge_set_error_message("Fail to play the sound: %s", Mix_GetError());
    }
}

void pge_sound_stop(pge_SoundObj sound_obj) {
    if (sound_obj == NULL) return;
    if (Mix_Paused(sound_obj->channel)) {
        Mix_Resume(sound_obj->channel);
    }
    Mix_HaltChannel(sound_obj->channel);
}

void pge_sound_pause(pge_SoundObj sound_obj) {
    if (sound_obj == NULL) return;
    Mix_Pause(sound_obj->channel);
}

void pge_sound_resume(pge_SoundObj sound_obj) {
    if (sound_obj == NULL) return;
    Mix_Resume(sound_obj->channel);
}

pge_AudioStatus pge_sound_status(pge_SoundObj sound_obj) {
    if (sound_obj == NULL) return PGE_AUDIO_STATUS_STOPED;
    if (Mix_Paused(sound_obj->channel)) {
        return PGE_AUDIO_STATUS_PAUSED;
    }
    if (Mix_Playing(sound_obj->channel)) {
        return PGE_AUDIO_STATUS_PLAYING;
    }
    return PGE_AUDIO_STATUS_STOPED;
}

void pge_sound_volume(pge_SoundObj sound_obj, int volume) {
    if (sound_obj == NULL) return;
    Mix_Volume(sound_obj->channel, volume);
}

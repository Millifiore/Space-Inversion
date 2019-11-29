#pragma once
#include "headers.h"

class Jukebox {
    private:
        map<string, Mix_Music *> music;
        map<string, Mix_Chunk *> sound_effects;
    public:
        int music_volume = 80;
        bool music_paused = false;
        bool effects_paused = false;
        int sound_effect_volume = 40;

        Jukebox();
        ~Jukebox();

        Mix_Music * LoadMusic(string, string filepath = "resources/sounds/music/");
        Mix_Chunk * LoadSoundEffect(string, string filepath = "resources/sounds/effects/");
        bool PlayMusic(string music = "", int loop = -1);
        bool PlaySoundEffect(string, int loop = 0);
        void PauseMusic();
        void PauseSoundEffects();
        void ResumeMusic();
        void ResumeSoundEffects();
        void StopMusic();
        void StopSoundEffects();

        void SetMusicVolume(int);
        void SetSoundEffectVolume(int);
};
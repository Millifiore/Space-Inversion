#include "jukebox.h"

Jukebox::Jukebox(){

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);

    music["title"] = LoadMusic("title_theme.wav");
    music["stage_music"] = LoadMusic("stage_music.wav");

    sound_effects["blast"] = LoadSoundEffect("blast_effect.wav");
    sound_effects["dying"] = LoadSoundEffect("explosion_effect.wav");
}

Jukebox::~Jukebox(){
    StopMusic();
    for (auto const &song : music){
        Mix_FreeMusic(song.second);
    }
    music.clear();

    StopSoundEffects();
    for (auto const &effect : sound_effects){
        Mix_FreeChunk(effect.second);
    }
    sound_effects.clear();
}

Mix_Music * Jukebox::LoadMusic(string song, string filepath){
    string path = filepath + song;
    return Mix_LoadMUS(path.c_str());
}

Mix_Chunk * Jukebox::LoadSoundEffect(string effect, string filepath){
    string path = filepath + effect;
    return Mix_LoadWAV(path.c_str());
}

bool Jukebox::PlayMusic(string music, int loop){
    Mix_VolumeMusic((music_volume/100)*MIX_MAX_VOLUME);
    if (!Mix_PlayingMusic()){
        if (Mix_PlayMusic(this->music[music], loop) != -1){
            return true;
        }
    }  
    return false;
}

bool Jukebox::PlaySoundEffect(string effect, int loop){
    if (Mix_VolumeChunk(sound_effects[effect], (sound_effect_volume/100)*MIX_MAX_VOLUME)){
        Mix_PlayChannel(-1, sound_effects[effect], loop);
        return true;
    }
    return false;
}

void Jukebox::PauseMusic(){
    if (!music_paused){
        Mix_PauseMusic();
        music_paused = true;
    } 
}

void Jukebox::PauseSoundEffects(){
    if (!effects_paused){
        Mix_Pause(-1);
        effects_paused = true;
    }
}

void Jukebox::ResumeMusic(){
    if (music_paused){
        Mix_ResumeMusic();
        music_paused = false;
    }
}

void Jukebox::ResumeSoundEffects(){
    if (effects_paused){
        Mix_Resume(-1);
        effects_paused = false;
    }
}

void Jukebox::StopMusic(){
    Mix_HaltMusic();
    music_paused = false;
}

void Jukebox::StopSoundEffects(){
    Mix_HaltChannel(-1);
    effects_paused = false;
}

void Jukebox::SetMusicVolume(int volume){
    music_volume = volume;
}

void Jukebox::SetSoundEffectVolume(int volume){
    sound_effect_volume = volume;
}



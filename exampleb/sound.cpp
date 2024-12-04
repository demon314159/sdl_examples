//
// sound.cpp
//

#include "sound.h"
#include <windows.h>
#include <stdio.h>

Sound::Sound()
    : m_sounds(0)
{
    for (int i = 0; i < MAX_SOUNDS; i++) {
        m_sound[i] = NULL;
    }
}

Sound::~Sound()
{
    for (int i = 0; i < m_sounds; i++) {
        Mix_FreeChunk(m_sound[i]);
    }
}

void Sound::initialize()
{
    if (Mix_Init(0) < 0) {
        printf("Mixer Initialization Error: %s\n", Mix_GetError());
        exit(0);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 1024) < 0) {
        printf("Mixer Open Error: %s\n", Mix_GetError());
        exit(0);
    }
    add("sound1.wav"); // SOUND_ID_THOUSANDS_CHIME
    add("sound2.wav"); // SOUND_ID_HUNDREDS_CHIME
    add("sound3.wav"); // SOUND_ID_TENS_CHIME
    add("knocker.wav"); // SOUND_ID_KNOCKER
}

int Sound::sounds() const
{
    return m_sounds;
}

void Sound::add(const char* file_name)
{
    if (m_sounds < MAX_SOUNDS) {
        int length;

        void* pdata = load_from_resource(file_name, &length);
        SDL_RWops* rw;
        rw = SDL_RWFromMem(pdata, length);


        Mix_Chunk* p = Mix_LoadWAV_RW(rw, 0);

        SDL_FreeRW(rw);

        if (!p) {
            printf("Mixer LoadWAV Error: %s\n", Mix_GetError());
            exit(0);
        }
        m_sound[m_sounds] = p;
        ++m_sounds;
    }
}

//void Sound::add(const char* file_name)
//{
//    if (m_sounds < MAX_SOUNDS) {
//        Mix_Chunk* p = Mix_LoadWAV(file_name);
//        if (!p) {
//            printf("Mixer LoadWAV Error: %s\n", Mix_GetError());
//            exit(0);
//        }
//        m_sound[m_sounds] = p;
//        ++m_sounds;
//    }
//}

void Sound::play(int sound_id)
{
    if (sound_id < m_sounds) {
        Mix_PlayChannel(-1, m_sound[sound_id], 0);
    }
}

void* Sound::load_from_resource(const char* fname, int* length)
{
    HRSRC res = FindResource(NULL, fname, "CUSTOM");
    *length = ::SizeofResource(NULL, res);
    HGLOBAL res_data = ::LoadResource(NULL, res);
    return ::LockResource(res_data);
}

void Sound::testy()
{
    char* buf = new char[100];

    SDL_RWops * rw;
    rw = SDL_RWFromMem(buf, 100);

    delete [] buf;
}

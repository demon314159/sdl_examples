//
// sound.h
//

#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL_mixer.h>

#define MAX_SOUNDS 10

class Sound
{
public:
    Sound();
    ~Sound();

    void initialize();
    int sounds() const;
    void play(int sound_id);

private:
    int m_sounds;
    Mix_Chunk* m_sound[MAX_SOUNDS];
    void add(const char* file_name);
};

#endif // _SOUND_H_

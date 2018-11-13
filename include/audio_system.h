#ifndef _AUDIO_SYSTEM_H
#define _AUDIO_SYSTEM_H

#include <vector>
#include "audio_buffer.h"
#include "audio_source.h"

//class AudioBuffer;  // from "audio_buffer.h"
//class AudioSource;  // from "audio_source.h"

class AudioSystem
{
public:
    static std::vector<AudioSource*> audioSources;
    static std::vector<AudioBuffer*> audioBuffers;

    static void Init();
    static void Deinit();
    static void DeleteAllBuffers();
    static void DeleteAllSources();

    static void Update();
    static void Suspend();
    static void Resume();

    static void CheckErrorAL();

private:
    AudioSystem() {}
    ~AudioSystem() {}
};

#endif // _AUDIO_SYSTEM_H

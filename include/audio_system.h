#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <vector>

class AudioBuffer;  // from "audio_buffer.h"
class AudioSource;  // from "audio_source.h"

class AudioSystem
{
public:
    static std::vector<AudioSource*> audioSources;
    static std::vector<AudioBuffer*> audioBuffers;

    static void Init();
    static void Deinit();

    static void SetListenerPosition   (float* position);
    static void SetListenerOrientation(float* orientation);
    static void SetListenerVelocity   (float* velocity);

    static void GetListenerPosition   (float* position);
    static void GetListenerOrientation(float* orientation);
    static void GetListenerVelocity   (float* velocity);

    static void Update();
    static void Suspend();
    static void Resume();

    static void CheckErrorAL();

private:
    static float m_listenerPos[3];
    static float m_listenerOri[6];
    static float m_listenerVel[3];
};

#endif // AUDIO_SYSTEM_H

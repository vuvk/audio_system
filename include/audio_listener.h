#ifndef _AUDIO_LISTENER_H
#define _AUDIO_LISTENER_H

class AudioListener
{
public:
    static void Init();

    static void SetPosition   (const float* position);
    static void SetOrientation(const float* orientation);
    static void SetVelocity   (const float* velocity);
    static void SetPosition   (float x, float y, float z);
    static void SetOrientation(float tX, float tY, float tZ,
                               float uX, float uY, float uZ);
    static void SetVelocity   (float x, float y, float z);

    static void GetPosition   (float* position);
    static void GetOrientation(float* orientation);
    static void GetVelocity   (float* velocity);

private:
    AudioListener() {}
    ~AudioListener() {}

    static float m_listenerPos[3];
    static float m_listenerOri[6];
    static float m_listenerVel[3];
};

#endif // _AUDIO_LISTENER_H

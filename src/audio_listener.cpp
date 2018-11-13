#include <cstring>
#include "alure.h"
#include "audio_listener.h"


float AudioListener::m_listenerPos[3] = {};
float AudioListener::m_listenerOri[6] = {0, 0, -1, 0, 1, 0};
float AudioListener::m_listenerVel[3] = {};


void AudioListener::Init()
{
    SetPosition   ( 0.0,  0.0,  0.0 );
    SetOrientation( 0.0,  0.0, -1.0,
                    0.0,  1.0,  0.0 );
    SetVelocity   ( 0.0,  0.0,  0.0 );
}

void AudioListener::SetPosition(float* position)
{
    memcpy(m_listenerPos, position, sizeof(float) * 3);
    alListenerfv(AL_POSITION, position);
}

void AudioListener::SetOrientation(float* orientation)
{
    memcpy(m_listenerOri, orientation, sizeof(float) * 6);
    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioListener::SetVelocity(float* velocity)
{
    memcpy(m_listenerVel, velocity, sizeof(float) * 3);
    alListenerfv(AL_VELOCITY, velocity);
}

void AudioListener::SetPosition(float x, float y, float z)
{
    m_listenerPos[0] = x;
    m_listenerPos[1] = y;
    m_listenerPos[2] = z;
    alListenerfv(AL_POSITION, m_listenerPos);
}

void AudioListener::SetOrientation(float tX, float tY, float tZ,
                                   float uX, float uY, float uZ)
{
    m_listenerOri[0] = tX;
    m_listenerOri[1] = tY;
    m_listenerOri[2] = tZ;
    m_listenerOri[3] = uX;
    m_listenerOri[4] = uY;
    m_listenerOri[5] = uZ;
    alListenerfv(AL_ORIENTATION, m_listenerOri);
}

void AudioListener::SetVelocity(float x, float y, float z)
{
    m_listenerVel[0] = x;
    m_listenerVel[1] = y;
    m_listenerVel[2] = z;
    alListenerfv(AL_VELOCITY, m_listenerVel);
}

void AudioListener::GetPosition(float* position)
{
    if (position)
    {
        memcpy(position, m_listenerPos, 3 * sizeof(float));
    }
}

void AudioListener::GetOrientation(float* orientation)
{
    if (orientation)
    {
        memcpy(orientation, m_listenerOri, 6 * sizeof(float));
    }
}

void AudioListener::GetVelocity (float* velocity)
{
    if (velocity)
    {
        memcpy(velocity, m_listenerVel, 3 * sizeof(float));
    }
}
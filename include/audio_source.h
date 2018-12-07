#ifndef _AUDIO_SOURCE_H
#define _AUDIO_SOURCE_H

#include "AL/al.h"
#include "AL/alure.h"
#include "audio_buffer.h"
//#include "audio_system.h"

#define STREAM_BUFFER_SIZE 65535    // size of chunk in bytes
#define BUFFERS_NUM 16              // count of chunks
//#define STREAM_LENGTH_MS 250000   // size of chunk in msec
#define SOUND_FONT_NAME "sound_font.sf2"    // name of soundfont (*.sf2) for playing MIDI

class AudioSource
{
public:
    AudioSource(AudioBuffer* buffer = nullptr);
    virtual ~AudioSource();

    virtual void setBuffer(AudioBuffer* buffer);
    virtual void unsetBuffer();
    virtual AudioBuffer* getBuffer();

    virtual void setLooping(bool isLoop);
    virtual void setPitch(float pitch);
    virtual void setGain(float gain);
    virtual void setPosition(float* position);
    virtual void setPosition(float x, float y, float z);
    virtual void setRelative(bool isRelative = false);
    virtual void setVelocity(float* velocity);
    virtual void setVelocity(float x, float y, float z);


    /*
        Reset all attributes to their default value
        Can be called only if the sound is inactive
    */
    virtual void reset();

    virtual void play(bool isLoop = false);
    virtual void pause();
    virtual void resume();
    virtual void stop();
    virtual void update();

    virtual bool isRelative();
    virtual bool isActive();
    virtual bool isInactive();
    virtual bool isPlaying();
    virtual bool isLooping();
    virtual bool isPaused();
    virtual bool isStopped();

protected:
    ALuint m_source;
    ALuint m_streamBuffer[BUFFERS_NUM];
    bool   m_isLoop = false;
    AudioBuffer* m_audioBuffer = nullptr; // current source of pcm data
    alureStream* m_stream = nullptr;
};

#endif // _AUDIO_SOURCE_H

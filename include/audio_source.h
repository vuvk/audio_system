#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include "AL/al.h"
#include "AL/alure.h"
#include "audio_buffer.h"
#include "audio_system.h"

#define STREAM_BUFFER_SIZE 65535    // size of chunk in bytes
#define BUFFERS_NUM 16              // count of chunks
//#define STREAM_LENGTH_MS 250000   // size of chunk in msec
#define SOUND_FONT_NAME "sound_font.sf2"    // name of soundfont (*.sf2) for playing MIDI

class AudioSource
{
public:
    AudioSource(AudioBuffer* buffer = nullptr);
    ~AudioSource();

    void setBuffer(AudioBuffer* buffer);
    void unsetBuffer();

    void setLooping(bool isLoop);
    void setGain(float gain);
    void setPosition(float* position);
    void setPosition(float x, float y, float z);
    void setRelative(bool isRelative = false);

    /*
        Reset all attributes to their default value
        Can be called only if the sound is inactive
    */
    void reset();

    void play(bool isLoop = false);
    void pause();
    void resume();
    void stop();
    void update();

    bool isRelative();
    bool isActive();
    bool isInactive();
    bool isPlaying();
    bool isLooping();
    bool isPaused();
    bool isStopped();

private:
    ALuint m_source;
    ALuint m_streamBuffer[BUFFERS_NUM];
    bool   m_isLoop = false;
    AudioBuffer* m_audioBuffer = nullptr; // current source of pcm data
    alureStream* m_stream = nullptr;
};


#endif // AUDIO_SOURCE_H

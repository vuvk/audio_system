#include "audio_source.h"


static void eos_callback(void* userdata, ALuint source)
{
    AudioSource* audioSource = static_cast<AudioSource*>(userdata);

    if (audioSource->isLooping())
    {
        audioSource->stop();
        audioSource->play(true);
    }
}


AudioSource::AudioSource(AudioBuffer* buffer)
{
    alGenSources(1, &m_source);
    if (buffer)
        setBuffer(buffer);
    AudioSystem::audioSources.push_back(this);
}

AudioSource::~AudioSource()
{
    unsetBuffer();
    alDeleteSources(1, &m_source);

    for (std::vector<AudioSource*>::iterator it = AudioSystem::audioSources.begin();
         it != AudioSystem::audioSources.end();
         ++it)
    {
        if (*it == this)
        {
            *it = AudioSystem::audioSources.back();
            AudioSystem::audioSources.pop_back();
            break;
        }
    }
}

void AudioSource::setBuffer(AudioBuffer* buffer)
{
    unsetBuffer();

    this->m_audioBuffer = buffer;

    if (buffer->isStreamed())
    {
        m_stream = alureCreateStreamFromFile(buffer->getFileName().c_str(), STREAM_BUFFER_SIZE, BUFFERS_NUM, m_streamBuffer);
        if (!m_stream)
        {
            std::cout << "Could not create a stream!" << std::endl;
            std::cout << "Error: " << alureGetErrorString() << std::endl;
        }

        // patchset for playing midi
        if (!alureSetStreamPatchset(m_stream, SOUND_FONT_NAME))
        {
            std::cout << "Could not load sound font '" << SOUND_FONT_NAME << "'!" << std::endl;
            std::cout << "Error: " << alureGetErrorString() << std::endl;
        }
    }
    else
    {
        alSourcei(m_source, AL_BUFFER, buffer->getBuffer());
    }
}

void AudioSource::unsetBuffer()
{
    stop();

    if (m_audioBuffer)
        m_audioBuffer = nullptr;

    if (m_stream)
    {
        alureDestroyStream(m_stream, BUFFERS_NUM, m_streamBuffer);
        memset(m_streamBuffer, 0, sizeof(m_streamBuffer));
    }
    else
    {
        alSourcei(m_source, AL_BUFFER, 0);
    }
}

void AudioSource::setLooping(bool isLoop)
{
    m_isLoop = isLoop;
}

void AudioSource::setGain(float gain)
{
    alSourcef(m_source, AL_GAIN, gain);
}

void AudioSource::setPosition(float* position)
{
    alSourcefv(m_source, AL_POSITION, position);
}

void AudioSource::setPosition(float x, float y, float z)
{
    float position[3] = {x, y, z};
    alSourcefv(m_source, AL_POSITION, position);
}

void AudioSource::setRelative(bool isRelative)
{
    if (isRelative)
        alSourcei(m_source, AL_SOURCE_RELATIVE, AL_TRUE);
    else
        alSourcei(m_source, AL_SOURCE_RELATIVE, AL_FALSE);
}

void AudioSource::reset()
{
    alSource3f(m_source, AL_POSITION, 0, 0, 0);
    alSourcei (m_source, AL_LOOPING, AL_FALSE);
    alSourcef (m_source, AL_GAIN, 1.0f);
    alSourcei (m_source, AL_BUFFER, AL_NONE);
    alSourcei (m_source, AL_SOURCE_RELATIVE, AL_FALSE);
    m_isLoop = false;
}

void AudioSource::play(bool isLoop)
{
    this->m_isLoop = isLoop;

    if (m_stream)
    {
        alureRewindStream(m_stream);
        alurePlaySourceStream(m_source, m_stream, BUFFERS_NUM, 0, eos_callback, this);
    }
    else
        alurePlaySource(m_source, eos_callback, this);
}

void AudioSource::pause()
{
    alurePauseSource(m_source);
}

void AudioSource::resume()
{
    if (isPaused())
        alureResumeSource(m_source);
}

void AudioSource::stop()
{
    alureStopSource(m_source, 0);
    m_isLoop = false;
}

bool AudioSource::isRelative()
{
    ALint value;
    alGetSourcei(m_source, AL_SOURCE_RELATIVE, &value);
    return (value == AL_TRUE);
}

bool AudioSource::isActive()
{
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING || state == AL_PAUSED;
}

bool AudioSource::isInactive()
{
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_INITIAL || state == AL_STOPPED;
}

bool AudioSource::isPlaying()
{
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool AudioSource::isLooping()
{
    return m_isLoop;
}

bool AudioSource::isPaused()
{
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool AudioSource::isStopped()
{
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_STOPPED;
}

void AudioSource::update()
{
    /*
    if (m_audioBuffer)
    {
        if (m_isLoop && isStopped())
        {
            if (m_stream)
                alureRewindStream(m_stream);
            play(true);
        }
    }
    */
}

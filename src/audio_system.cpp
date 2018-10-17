#include <cstring>
#include "audio_system.h"
#include "file_system.h"
#include "audio_source.h"
#include "AL/alure.h"

float AudioSystem::m_listenerPos[3] = {};
float AudioSystem::m_listenerOri[6] = {0, 0, -1, 0, 1, 0};
float AudioSystem::m_listenerVel[3] = {};
std::vector<AudioSource*> AudioSystem::audioSources;
std::vector<AudioBuffer*> AudioSystem::audioBuffers;

using namespace FileSystem;


void* open_callback(const char* fileName, ALuint mode)
{
    if (!File::exists(fileName))
        return nullptr;

    return static_cast<void*>(new File(fileName));
}

void close_callback(void* handle)
{
    if (!handle)
        return;
    File* file = static_cast<File*>(handle);
    file->close();
}

ALsizei read_callback(void* handle, ALubyte* buffer, ALuint bytes)
{
    if (!handle)
        return -1;
    File* file = static_cast<File*>(handle);
    return file->read((char*)buffer, bytes);
}

ALsizei write_callback(void* handle, const ALubyte* buffer, ALuint bytes)
{
    if (!handle)
        return -1;
    File* file = static_cast<File*>(handle);
    return file->write((const char*)buffer, bytes);
}

alureInt64 seek_callback(void* handle, alureInt64 offset, int whence)
{
    if (!handle)
        return -1;
    File* file = static_cast<File*>(handle);

    switch (whence)
    {
        case SEEK_SET:
            break;

        case SEEK_END:
            offset = file->size() - offset;
            break;

        case SEEK_CUR:
            offset = file->tell() + offset;
            break;
    }

    /* return -1 if error */
    if (file->seek(offset) == 0)
        return -1;

    /* return new pos */
    return offset;
}


void AudioSystem::Init()
{

    std::cout << "Initializing OpenAL..." << std::endl;

    if (!alureInitDevice(nullptr, nullptr))
    {
        std::cout << "Failed to open OpenAL device: " << alureGetErrorString() << std::endl;
        CheckErrorAL();
        return;
    }

    // print all available devices
    ALsizei count;
    const char** devices = alureGetDeviceNames(true, &count);
    if (count == 0)
    {
        std::cout << "No devices available!" << alureGetErrorString() << std::endl;
        CheckErrorAL();
        Deinit();
        return;
    }
    std::cout << "OpenAL devices:" << std::endl;
    for (int i = 0; i < count; ++i)
        std::cout << "\t" << devices[i] << std::endl;

    // info
    ALuint major, minor;
    alureGetVersion(&major, &minor);
    std::cout << "OpenAL context version: " << major << "." << minor << std::endl;

    std::cout << "OpenAL vendor: "   << alGetString(AL_VENDOR)   << std::endl;
    std::cout << "OpenAL version: "  << alGetString(AL_VERSION)  << std::endl;
    std::cout << "OpenAL renderer: " << alGetString(AL_RENDERER) << std::endl;

    //alureStreamSizeIsMicroSec(AL_TRUE);

    alureSetIOCallbacks(open_callback,
                        close_callback,
                        read_callback,
                        write_callback,
                        seek_callback);

}

void AudioSystem::Deinit()
{
    std:: cout << "Shutting down OpenAL..." << std::endl;

    for (auto source : audioSources)
        delete source;
    audioSources.clear();

    for (auto buffer : audioBuffers)
        delete buffer;
    audioBuffers.clear();

    alureShutdownDevice();
}

void AudioSystem::SetListenerPosition(float* position)
{
    memcpy(m_listenerPos, position, sizeof(float) * 3);
    alListenerfv(AL_POSITION, m_listenerPos);
}

void AudioSystem::SetListenerOrientation(float* orientation)
{
    memcpy(m_listenerOri, orientation, sizeof(float) * 6);
    alListenerfv(AL_ORIENTATION, m_listenerOri);
}

void AudioSystem::SetListenerVelocity(float* velocity)
{
    memcpy(m_listenerVel, velocity, sizeof(float) * 3);
    alListenerfv(AL_VELOCITY, m_listenerVel);
}

void AudioSystem::SetListenerPosition(float x, float y, float z)
{
    m_listenerPos[0] = x;
    m_listenerPos[1] = y;
    m_listenerPos[2] = z;
    alListenerfv(AL_POSITION, m_listenerPos);
}

void AudioSystem::SetListenerOrientation(float tX, float tY, float tZ,
                                         float uX, float uY, float uZ)
{
    m_listenerOri[0] = tX;
    m_listenerOri[1] = tY;
    m_listenerOri[2] = tZ;
    m_listenerOri[3] = uX;
    m_listenerOri[4] = uY;
    m_listenerOri[5] = uZ;
    alListenerfv(AL_VELOCITY, m_listenerVel);
}

void AudioSystem::SetListenerVelocity(float x, float y, float z)
{
    m_listenerVel[0] = x;
    m_listenerVel[1] = y;
    m_listenerVel[2] = z;
    alListenerfv(AL_VELOCITY, m_listenerVel);
}

void AudioSystem::GetListenerPosition(float* position)
{
    if (position)
    {
        memcpy(position, m_listenerPos, 3 * sizeof(float));
    }
}

void AudioSystem::GetListenerOrientation(float* orientation)
{
    if (orientation)
    {
        memcpy(orientation, m_listenerOri, 6 * sizeof(float));
    }
}

void AudioSystem::GetListenerVelocity (float* velocity)
{
    if (velocity)
    {
        memcpy(velocity, m_listenerVel, 3 * sizeof(float));
    }
}

void AudioSystem::Update()
{
    alureUpdate();

    for (auto source : audioSources)
    {
        source->update();
        if (!source->isRelative())
        {
            source->setPosition(m_listenerPos);
        }
    }

    CheckErrorAL();
}

void AudioSystem::Suspend()
{
    for (auto source : audioSources)
    {
        if (source->isActive())
        {
            source->pause();
        }
    }
}

void AudioSystem::Resume()
{
    for (auto source : audioSources)
    {
        if (source->isPaused())
        {
            source->play();
        }
    }
}

void AudioSystem::CheckErrorAL()
{
    ALenum errorCode = alGetError();
    if (errorCode != AL_NO_ERROR)
    {
        std::cout << "OpenAL error " << errorCode << ": " << alGetString(errorCode) << std::endl;
    }
}

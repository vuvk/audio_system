#include "audio_buffer.h"
#include "audio_source.h"
#include "audio_system.h"

AudioBuffer::AudioBuffer(const std::string& fileName, bool isStreamed)
{
    AudioSystem::audioBuffers.push_back(this);
    load(fileName, isStreamed);
}

AudioBuffer::~AudioBuffer()
{
    unload();
	
	/* unset current buffer from sources which use it */
	for (std::vector<AudioSource*>::iterator it = AudioSystem::audioSources.begin();
		 it != AudioSystem::audioSources.end();
		 ++it)
	{
		if ((*it)->getBuffer() == this)
			(*it)->unsetBuffer();
	}
	
	/* delete it from list of buffers */
    for (std::vector<AudioBuffer*>::iterator it = AudioSystem::audioBuffers.begin();
         it != AudioSystem::audioBuffers.end();
         ++it)
    {
        if (*it == this)
        {
            *it = AudioSystem::audioBuffers.back();
            AudioSystem::audioBuffers.pop_back();
            break;
        }
    }
	
	AudioSystem::CheckErrorAL();
}

void AudioBuffer::load(const std::string& fileName, bool isStreamed)
{
    unload();

    if (!File::exists(fileName))
    {
        std::cout << "The sound file is not exists: " << fileName << std::endl;
        return;
    }

    if (!isStreamed)
    {
        m_buffer = alureCreateBufferFromFile(fileName.c_str());
        if(!m_buffer)
        {
            std::cout << "Could not load " << fileName << ": " << alureGetErrorString() << std::endl;
			AudioSystem::CheckErrorAL();
            return;
        }
    }

    this->m_isStreamed = isStreamed;
    this->m_fileName   = fileName;
}

void AudioBuffer::unload()
{
    if (m_buffer)
    {
        alDeleteBuffers(1, &m_buffer);
        m_buffer = 0;
    }

    m_fileName = "";
    m_isStreamed = false;
}

bool AudioBuffer::isLoaded()
{
    return (m_buffer || m_fileName != "");
}

ALuint AudioBuffer::getBuffer()
{
    return m_buffer;
}

const std::string AudioBuffer::getFileName()
{
    return m_fileName;
}

bool AudioBuffer::isStreamed()
{
    return this->m_isStreamed;
}



extern "C"
{

void* AudioBufferCreate(const char* fileName, bool isStreamed)
{
    return new AudioBuffer(fileName, isStreamed);
}

void AudioBufferDestroy(void** audioBuffer)
{
    delete ((AudioBuffer*)*audioBuffer);
    *audioBuffer = nullptr;
}

void AudioBufferLoad(const void* audioBuffer, const char* fileName, bool isStreamed)
{
    ((AudioBuffer*)(audioBuffer))->load(fileName, isStreamed);
}

void AudioBufferUnload(const void* audioBuffer)
{
    ((AudioBuffer*)(audioBuffer))->unload();
}

bool AudioBufferIsLoaded(const void* audioBuffer)
{
    return ((AudioBuffer*)(audioBuffer))->isLoaded();
}

ALuint AudioBufferGetBuffer(const void* audioBuffer)
{
    return ((AudioBuffer*)(audioBuffer))->getBuffer();
}

const char* AudioBufferGetFileName(const void* audioBuffer)
{
    return ((AudioBuffer*)(audioBuffer))->getFileName().c_str();
}

bool AudioBufferIsStreamed(const void* audioBuffer)
{
    return ((AudioBuffer*)(audioBuffer))->isStreamed();
}


}

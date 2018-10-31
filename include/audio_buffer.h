#ifndef _AUDIO_BUFFER_H
#define _AUDIO_BUFFER_H

#include <iostream>
#include <string>
#include <cstring>
#include "AL/al.h"
#include "AL/alure.h"
#include "file_system.h"


using namespace FileSystem;


class AudioBuffer
{
public:
    AudioBuffer(const std::string fileName, bool isStreamed = false);
    ~AudioBuffer();

    void load(const std::string fileName, bool isStreamed = false);
    void unload();

    ALuint getBuffer();
    const std::string getFileName();

    bool isStreamed();

protected:
    std::string m_fileName = "";
    ALuint m_buffer = 0;
    bool m_isStreamed = false;
};

#endif // _AUDIO_BUFFER_H

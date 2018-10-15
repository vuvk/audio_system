#include <iostream>
#include <cmath>
#include "audio_system.h"
#include "audio_source.h"
#include "audio_buffer.h"
#include "file_system.h"

using namespace FileSystem;

float position[3] = { 0, 0, -1 };
float angle = 0.0;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define RADIUS 1.5
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: sound_system <soundfile>" << std::endl;
        std::cout << "Press ENTER to continue..."      << std::endl;
        std::cin.ignore();
        return 1;
    }

    FileManager::Init(argv[0]);
    AudioSystem::Init();
    FileManager::Mount("./");
    FileManager::Mount("pack.zip");

    AudioBuffer* buffer = new AudioBuffer(argv[1], true);
    AudioSource* source = new AudioSource(buffer);

    source->setRelative(true);
    source->play(true);
    while (source->isActive())
    {
        alureSleep(0.125);
        AudioSystem::Update();

        angle += 5;
        if (angle > 360.0)
            angle -= 360.0;
        position[0] =  RADIUS * cos(DEG_TO_RAD(angle));
        position[2] = -RADIUS * sin(DEG_TO_RAD(angle));
        source->setPosition(position);
    }

    AudioSystem::Deinit();
    FileManager::Deinit();
    return 0;
}

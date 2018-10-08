#include <iostream>
#include <cmath>
#include <iomanip>
#include "file_system.h"

using namespace std;
using namespace FileSystem;

float position[3] = { 0, 0, -1 };
float angle = 0.0;
float listenerPosition[3] = {0, 0, 0};

#define RADIUS 1.5
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)

// Helper class+method to print the time with human-readable formatting.
struct PrettyTime {
    alure::Seconds mTime;
};
inline std::ostream &operator<<(std::ostream &os, const PrettyTime &rhs)
{
    using hours = std::chrono::hours;
    using minutes = std::chrono::minutes;
    using seconds = std::chrono::seconds;
    using centiseconds = std::chrono::duration<int64_t, std::ratio<1, 100>>;
    using std::chrono::duration_cast;

    centiseconds t = duration_cast<centiseconds>(rhs.mTime);
    if (t.count() < 0)
    {
        os << '-';
        t *= -1;
    }

    // Only handle up to hour formatting
    if(t >= hours(1))
        os << duration_cast<hours>(t).count() << 'h' << std::setfill('0') << std::setw(2)
           << duration_cast<minutes>(t).count() << 'm';
    else
        os << duration_cast<minutes>(t).count() << 'm' << std::setfill('0');
    os << std::setw(2) << (duration_cast<seconds>(t).count() % 60) << '.' << std::setw(2)
       << (t.count() % 100) << 's' << std::setw(0) << std::setfill(' ');
    return os;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: sound_system [filename] " << std::endl;
        return 1;
    }

    FileManager::Mount("pack.zip");
    if (!File::exists(argv[1]))
    {
        std::cerr << "File \"" << argv[1] << "\" doesn't exists!" << std::endl;
        return 2;
    }

    alure::FileIOFactory::set(alure::MakeUnique<FileManager>(argv[0]));

    alure::DeviceManager devMgr = alure::DeviceManager::getInstance();
    alure::Device dev = devMgr.openPlayback();
    std::cout << "Opened \"" << dev.getName() << "\"" << std::endl;

    alure::Context ctx = dev.createContext();
    alure::Context::MakeCurrent(ctx);

    alure::SharedPtr<alure::Decoder> decoder   = ctx.createDecoder(argv[1]);
    alure::Listener listener = ctx.getListener();
    listener.setPosition(listenerPosition);

    alure::Source source = ctx.createSource();
    source.play(decoder, 12000, 4);
    source.setRelative(true);
    source.setLooping(true);

    std::cout<< "Playing " << argv[1] << " ("
             << alure::GetSampleTypeName(decoder->getSampleType())<<", "
             << alure::GetChannelConfigName(decoder->getChannelConfig())<<", "
             << decoder->getFrequency()<<"hz)" <<std::endl;

    double invfreq = 1.0 / decoder->getFrequency();
    while (source.isPlaying())
    {
        angle += 1;
        if (angle > 360.0)
            angle -= 360.0;
        position[0] =  RADIUS * cos(DEG_TO_RAD(angle));
        position[2] = -RADIUS * sin(DEG_TO_RAD(angle));
        source.setPosition(position);

        std::cout<< "\r "<<PrettyTime{source.getSecOffset()}<<" / "<<
            PrettyTime{alure::Seconds(decoder->getLength()*invfreq)};
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        ctx.update();
    }
    std::cout<<std::endl;

    source.destroy();
    decoder.reset();

    alure::Context::MakeCurrent(nullptr);
    ctx.destroy();
    dev.close();
    FileManager::Deinit();

    return 0;
}

# Audio system
Audio system based on alure1.2 (OpenAL) with file system based on PhysFS. This system can play audio from buffers or stream, both from a folder and from archives directly.

### alure1.2 
Alure is a C++ 3D audio API. It uses OpenAL for audio rendering, and provides common higher-level features such as file loading and decoding, buffer caching, background streaming, and source management for virtually unlimited sound source handles.

Link : <https://repo.or.cz/alure.git/shortlog/refs/heads/alure-1.x>

### libPhysFS 
PhysicsFS is a library to provide abstract access to various archives. The programmer does not know and does not care where each of these files came from, and what sort of archive (if any) is storing them.

Link : <https://icculus.org/physfs/>

### Small info
Supported formats|
------------- |
WAV |
OGG |
FLAC|
MP3 |
XM, MPTM, IT, S3M |
MIDI |

> You can use another SoundFont to change the MIDI sound. 
> To do this, replace the file sound_font.fs2 (there are several versions in the "build" folder).

dependencies  |
------------- |
libalure |
libphysfs |
libopenal |
libfluidsynth |
libFLAC |
libsndfile |
libmodplug |
libmpg123 |
libogg |
libvorbis |
libvorbisfile |
libvorbisenc |

I used MSYS2 with mingw-w64 7.3 and cmake for create libraries in Windows.

For Ubuntu/Debian Linux:

```sh
$ sudo apt install libalure1 libalure-dev libphysfs1 libphysfs-dev libopenal1 libopenal-dev libfluidsynth1 libsndfile1 libmodplug1 libmpg123-0 libogg0 libvorbis0a libvorbisfile3 libvorbisenc2 libflac8
$ git clone https://github.com/vuvk/audio_system
$ cd audio_system/build
$ cmake ..
$ make
$ ./audio_system music.mid
```

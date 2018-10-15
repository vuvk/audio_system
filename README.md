# Audio system
Audio system based on alure1.2 (OpenAL) with file system based on PhysFS

### alure1.2 
Alure is a C++ 3D audio API. It uses OpenAL for audio rendering, and provides common higher-level features such as file loading and decoding, buffer caching, background streaming, and source management for virtually unlimited sound source handles.

Link : <https://repo.or.cz/alure.git/shortlog/refs/heads/alure-1.x>

### libPhysFS 
PhysicsFS is a library to provide abstract access to various archives. The programmer does not know and does not care where each of these files came from, and what sort of archive (if any) is storing them.

Link : <https://icculus.org/physfs/>

### Small info
dependencies  |
------------- |
libalure |
libphysfs |
libopenal |

I used MSYS2 with mingw-w64 7.3 and cmake for create libraries in Windows.

For Ubuntu/Debian Linux:

`$ sudo apt install libalure1 libalure-dev libphysfs1 libphysfs-dev libopenal1 libopenal-dev`

`$ git clone https://github.com/vuvk/audio_system`

`$ cd audio_system/build`

`$ ./cmake_prepare.sh`

`$ make`

`$ ./audio_system music.it`

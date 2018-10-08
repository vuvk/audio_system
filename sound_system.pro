TEMPLATE = app
CONFIG += console c++11 c++17
#CONFIG += static
#CONFIG += -static
#CONFIG += -static-libgcc -static-libstdc++
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/include/AL
INCLUDEPATH += $$PWD/include/alure

HEADERS += \
    include/file_system.h \
    include/alure/alure2.h

SOURCES += \
    src/main.cpp \
    src/file_system.cpp \

LIBS += -L$$PWD/lib/ -lalure2.dll
LIBS += $$PWD/build/debug/libalure2.dll
LIBS += $$PWD/build/debug/libopenal-1.dll
LIBS += $$PWD/build/debug/libphysfs.dll
LIBS += $$PWD/build/debug/libogg-0.dll
LIBS += $$PWD/build/debug/libvorbis-0.dll
LIBS += $$PWD/build/debug/libvorbisfile-3.dll


cmake_minimum_required(VERSION 2.8)

#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# Использовать 32- или 64-битную сборку?
#set(ARCH 32)
set(ARCH 64)

project(audio_system)

set(EXE_NAME "example")
set(LIB_NAME ${PROJECT_NAME})

# куда выплёвывать проект и расположение динамических либ
set(BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

# путь до инклудов
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories(
        "${INCLUDE_DIR}/"
        "${INCLUDE_DIR}/AL/"
        )

# инклуды
set(HEADERS
    "${INCLUDE_DIR}/audio_buffer.h"
    "${INCLUDE_DIR}/audio_source.h"
    "${INCLUDE_DIR}/audio_system.h"
    "${INCLUDE_DIR}/audio_listener.h"
    "${INCLUDE_DIR}/file_system.h"
    )

# Установить переменную с путем до src
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

# расположение статических библиотек
if (WIN32)
    if (ARCH EQUAL 32)
        set(LIBRARIES_DIR "${PROJECT_SOURCE_DIR}/lib/win32")
    endif(ARCH EQUAL 32)

    if (ARCH EQUAL 64)
        set(LIBRARIES_DIR "${PROJECT_SOURCE_DIR}/lib/win64")
    endif(ARCH EQUAL 64)
endif(WIN32)


# где находятся библиотеки для линковки
link_directories(
        ${LIBRARIES_DIR}
        ${BINARY_DIR}
        )

# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_EXE
#    "${SOURCE_DIR}/audio_system.cpp"
#    "${SOURCE_DIR}/audio_source.cpp"
#    "${SOURCE_DIR}/audio_buffer.cpp"
#    "${SOURCE_DIR}/audio_listener.cpp"
#    "${SOURCE_DIR}/file_system.cpp"
    "${SOURCE_DIR}/main.cpp"
    )

# Установка переменной со списком исходников для библиотеки
set(SOURCE_LIB
    "${SOURCE_DIR}/audio_system.cpp"
    "${SOURCE_DIR}/audio_source.cpp"
    "${SOURCE_DIR}/audio_buffer.cpp"
    "${SOURCE_DIR}/audio_listener.cpp"
    "${SOURCE_DIR}/file_system.cpp"
    )

# Создает библиотеку
add_library("${LIB_NAME}-static" ${SOURCE_LIB} ${HEADERS})
add_library(${LIB_NAME} SHARED   ${SOURCE_LIB} ${HEADERS})

# Создает исполняемый файл с именем проекта
add_executable(${EXE_NAME} ${SOURCE_EXE} ${HEADERS})

if (WIN32)
    set (ALURE_LIB ALURE32)
endif (WIN32)
if (UNIX)
    set (ALURE_LIB alure)
endif (UNIX)

# линковки
target_link_libraries(${LIB_NAME}
    physfs
    openal
    ${ALURE_LIB}
    )

target_link_libraries(${EXE_NAME}
    physfs
    openal
    ${ALURE_LIB}
    ${LIB_NAME}
    )

#ifndef AUDIO_SYSTEM_LIB_H
#define AUDIO_SYSTEM_LIB_H

#include <AL/al.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#if defined (WIN32) || defined (_WIN32)
#define DLL_EXPORT __attribute__ ((dllexport)) /**__stdcall*/
#else
#define DLL_EXPORT
#endif


/**
 * FileManager
 * */
DLL_EXPORT void FileManagerInit(const char* argv0);
DLL_EXPORT void FileManagerDeinit();

DLL_EXPORT bool FileManagerMount(const char* path, const char* mountPoint, int append);
DLL_EXPORT void FileManagerListDirectory(char** dir);
DLL_EXPORT const char* FileManagerGetBaseDir();

DLL_EXPORT bool FileManagerIsInitialized();


/**
 * AudioSystem's functions
 * */
DLL_EXPORT void AudioSystemInit();
DLL_EXPORT void AudioSystemDeinit();
DLL_EXPORT void AudioSystemDeleteAllBuffers();
DLL_EXPORT void AudioSystemDeleteAllSources();

DLL_EXPORT void AudioSystemUpdate();
DLL_EXPORT void AudioSystemSuspend();
DLL_EXPORT void AudioSystemResume();

DLL_EXPORT void AudioSystemCheckErrorAL();

/**
 * AudioBuffer's functions
 * */
DLL_EXPORT void* AudioBufferCreate(const char* fileName, bool isStreamed);
DLL_EXPORT void AudioBufferDestroy(void** audioBuffer);

DLL_EXPORT void AudioBufferLoad(const void* audioBuffer, const char* fileName, bool isStreamed);
DLL_EXPORT void AudioBufferUnload(const void* audioBuffer);
DLL_EXPORT bool AudioBufferIsLoaded(const void* audioBuffer);

DLL_EXPORT ALuint AudioBufferGetBuffer(const void* audioBuffer);
DLL_EXPORT const char* AudioBufferGetFileName(const void* audioBuffer);

DLL_EXPORT bool AudioBufferIsStreamed(const void* audioBuffer);


/**
 * AudioListener's functions
 * */
DLL_EXPORT void AudioListenerInit();

DLL_EXPORT void AudioListenerSetPosition3v   (const float* position);
DLL_EXPORT void AudioListenerSetOrientation6v(const float* orientation);
DLL_EXPORT void AudioListenerSetVelocity3v   (const float* velocity);
DLL_EXPORT void AudioListenerSetPosition3f   (float x, float y, float z);
DLL_EXPORT void AudioListenerSetOrientation6f(float tX, float tY, float tZ,
                                              float uX, float uY, float uZ);
DLL_EXPORT void AudioListenerSetVelocity3f   (float x, float y, float z);

DLL_EXPORT void AudioListenerGetPosition3v   (float* position);
DLL_EXPORT void AudioListenerGetOrientation6v(float* orientation);
DLL_EXPORT void AudioListenerGetVelocity3v   (float* velocity);


/**
 * AudioSource's functions
 * */
DLL_EXPORT void* AudioSourceCreate(const void* audioBuffer);
DLL_EXPORT void AudioSourceDestroy(void** audioSource);

DLL_EXPORT void AudioSourceSetBuffer(const void* audioSource, const void* audioBuffer);
DLL_EXPORT void AudioSourceUnsetBuffer(const void* audioSource);
DLL_EXPORT void* AudioSourceGetBuffer(const void* audioSource);

DLL_EXPORT void AudioSourceSetLooping(const void* audioSource, bool isLoop);
DLL_EXPORT void AudioSourceSetPitch(const void* audioSource, float pitch);
DLL_EXPORT void AudioSourceSetGain(const void* audioSource, float gain);
DLL_EXPORT void AudioSourceSetPosition3v(const void* audioSource, const float* position);
DLL_EXPORT void AudioSourceSetPosition3f(const void* audioSource, float x, float y, float z);
DLL_EXPORT void AudioSourceSetRelative(const void* audioSource, bool isRelative);
DLL_EXPORT void AudioSourceSetVelocity3v(const void* audioSource, const float* velocity);
DLL_EXPORT void AudioSourceSetVelocity3f(const void* audioSource, float x, float y, float z);

DLL_EXPORT void AudioSourceReset(const void* audioSource);

DLL_EXPORT void AudioSourcePlay(const void* audioSource, bool isLoop);
DLL_EXPORT void AudioSourcePause(const void* audioSource);
DLL_EXPORT void AudioSourceResume(const void* audioSource);
DLL_EXPORT void AudioSourceStop(const void* audioSource);
DLL_EXPORT void AudioSourceUpdate(const void* audioSource);

DLL_EXPORT bool AudioSourceIsRelative(const void* audioSource);
DLL_EXPORT bool AudioSourceIsActive(const void* audioSource);
DLL_EXPORT bool AudioSourceIsInactive(const void* audioSource);
DLL_EXPORT bool AudioSourceIsPlaying(const void* audioSource);
DLL_EXPORT bool AudioSourceIsLooping(const void* audioSource);
DLL_EXPORT bool AudioSourceIsPaused(const void* audioSource);
DLL_EXPORT bool AudioSourceIsStopped(const void* audioSource);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // AUDIO_SYSTEM_LIB_H

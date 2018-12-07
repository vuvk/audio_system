unit uAudioSystem;

interface
         
{$MODE Delphi}
{$MACRO ON}

(*
{$IFDEF Windows}
const
  AUDIO_SYSTEM_LIB = 'audio_system.dll';

{**
 * FileManager
 * *}
procedure FileManagerInit(argv0 : PChar); cdecl; external AUDIO_SYSTEM_LIB;
procedure FileManagerDeinit(); cdecl; external AUDIO_SYSTEM_LIB;
function  FileManagerMount(const path : PChar; const mountPoint : PChar = nil; append : Integer = 0) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
procedure FileManagerListDirectory(dir : PPChar); cdecl; external AUDIO_SYSTEM_LIB;
function  FileManagerGetBaseDir() : PChar; cdecl; external AUDIO_SYSTEM_LIB;
function  FileManagerIsInitialized() : Boolean; cdecl; external AUDIO_SYSTEM_LIB;

{**
 * AudioSystem's functions
 * *}
procedure AudioSystemInit(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemDeinit(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemDeleteAllBuffers(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemDeleteAllSources(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemUpdate(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemSuspend(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemResume(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSystemCheckErrorAL(); cdecl; external AUDIO_SYSTEM_LIB;

{**
 * AudioBuffer's functions
 * *}
function  AudioBufferCreate(const fileName : PChar; isStreamed : Boolean) : Pointer; cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioBufferDestroy(audioBuffer : PPointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioBufferLoad(const audioBuffer : Pointer; const fileName : PChar; isStreamed : Boolean); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioBufferUnload(const audioBuffer : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
function  AudioBufferGetBuffer(const audioBuffer : Pointer) : Cardinal; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioBufferGetFileName(const audioBuffer : Pointer) : PChar; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioBufferIsStreamed(const audioBuffer : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;

{**
 * AudioListener's functions
 * *}
procedure AudioListenerInit(); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetPosition3v   (const position : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetOrientation6v(const orientation : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetVelocity3v   (const velocity : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetPosition3f   (x, y, z : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetOrientation6f(tX, tY, tZ, uX, uY, uZ : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerSetVelocity3f   (x, y, z : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerGetPosition3v   (position : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerGetOrientation6v(orientation : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioListenerGetVelocity3v   (velocity : PSingle); cdecl; external AUDIO_SYSTEM_LIB;

{**
 * AudioSource's functions
 * *}
function  AudioSourceCreate(const audioBuffer : Pointer) : Pointer; cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceDestroy(audioSource : PPointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetBuffer(const audioSource : Pointer; audioBuffer : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceUnsetBuffer(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceGetBuffer(const audioSource : Pointer) : Pointer; cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetLooping(const audioSource : Pointer; isLoop : Boolean); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetPitch(const audioSource : Pointer; pitch : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetGain(const audioSource : Pointer; gain : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetPosition3v(const audioSource : Pointer; const position : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetPosition3f(const audioSource : Pointer; x, y, z : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetRelative(const audioSource : Pointer; isRelative : Boolean); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetVelocity3v(const audioSource : Pointer; const velocity : PSingle); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceSetVelocity3f(const audioSource : Pointer; x, y, z : Single); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceReset(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourcePlay(const audioSource : Pointer; isLoop : Boolean); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourcePause(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceResume(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceStop(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
procedure AudioSourceUpdate(const audioSource : Pointer); cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsRelative(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsActive(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsInactive(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsPlaying(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsLooping(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsPaused(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;
function  AudioSourceIsStopped(const audioSource : Pointer) : Boolean; cdecl; external AUDIO_SYSTEM_LIB;

{$ELSE}  
*) 
uses
  Dialogs,
  sysutils,
  dynlibs;
                             
const
{$IFDEF WIN64}
  AUDIO_SYSTEM_LIB = 'libs/win64/libaudio_system.dll';
{$ELSE}
  {$IFDEF WIN32}
    AUDIO_SYSTEM_LIB = 'libs/win32/libaudio_system.dll';
  {$ENDIF}
{$ENDIF}

{$IFDEF LINUX}
  {$IFDEF cpui386}
    AUDIO_SYSTEM_LIB = './libs/nix_i386/libaudio_system.so';
  {$ENDIF}
  {$IFDEF cpux86_64}
    AUDIO_SYSTEM_LIB = './libs/nix_x86_64/libaudio_system.so';
  {$ENDIF}
{$ENDIF}
            
{$IFDEF DARWIN}
  AUDIO_SYSTEM_LIB = './libs/macos/libaudio_system.dylib';
{$ENDIF}

var
  FileManagerInit : procedure(argv0 : PChar); cdecl;
  FileManagerDeinit : procedure(); cdecl;
  FileManagerMount : function(const path : PChar; const mountPoint : PChar; append : Integer) : Boolean; cdecl;
  FileManagerListDirectory : procedure(dir : PPChar); cdecl;
  FileManagerGetBaseDir : function() : PChar; cdecl;
  FileManagerIsInitialized : function() : Boolean; cdecl;

  AudioSystemInit : procedure(); cdecl;
  AudioSystemDeinit : procedure(); cdecl;
  AudioSystemDeleteAllBuffers : procedure(); cdecl;
  AudioSystemDeleteAllSources : procedure(); cdecl;
  AudioSystemUpdate : procedure(); cdecl;
  AudioSystemSuspend : procedure(); cdecl;
  AudioSystemResume : procedure(); cdecl;
  AudioSystemCheckErrorAL : procedure(); cdecl;

  AudioBufferCreate : function(const fileName : PChar; isStreamed : Boolean) : Pointer; cdecl;
  AudioBufferDestroy : procedure(audioBuffer : PPointer); cdecl;
  AudioBufferLoad : procedure(const audioBuffer : Pointer; const fileName : PChar; isStreamed : Boolean); cdecl;
  AudioBufferUnload : procedure(const audioBuffer : Pointer); cdecl;      
  AudioBufferIsLoaded : function(const audioBuffer : Pointer) : Boolean; cdecl;
  AudioBufferGetBuffer : function(const audioBuffer : Pointer) : Cardinal; cdecl;
  AudioBufferGetFileName : function(const audioBuffer : Pointer) : PChar; cdecl;
  AudioBufferIsStreamed : function(const audioBuffer : Pointer) : Boolean; cdecl;
                                                                               
  AudioListenerInit : procedure(); cdecl;
  AudioListenerSetPosition3v : procedure(const position : PSingle); cdecl;
  AudioListenerSetOrientation6v : procedure(const orientation : PSingle); cdecl;
  AudioListenerSetVelocity3v : procedure(const velocity : PSingle); cdecl;
  AudioListenerSetPosition3f : procedure(x, y, z : Single); cdecl;
  AudioListenerSetOrientation6f : procedure(tX, tY, tZ, uX, uY, uZ : Single); cdecl;
  AudioListenerSetVelocity3f : procedure(x, y, z : Single); cdecl;
  AudioListenerGetPosition3v : procedure(position : PSingle); cdecl;
  AudioListenerGetOrientation6v : procedure(orientation : PSingle); cdecl;
  AudioListenerGetVelocity3v : procedure(velocity : PSingle); cdecl;
       
  AudioSourceCreate : function(const audioBuffer : Pointer) : Pointer; cdecl;
  AudioSourceDestroy : procedure(audioSource : PPointer); cdecl;
  AudioSourceSetBuffer : procedure(const audioSource : Pointer; audioBuffer : Pointer); cdecl;
  AudioSourceUnsetBuffer : procedure(const audioSource : Pointer); cdecl;
  AudioSourceGetBuffer : function(const audioSource : Pointer) : Pointer; cdecl;
  AudioSourceSetLooping : procedure(const audioSource : Pointer; isLoop : Boolean); cdecl;
  AudioSourceSetPitch : procedure(const audioSource : Pointer; pitch : Single); cdecl;
  AudioSourceSetGain : procedure(const audioSource : Pointer; gain : Single); cdecl;
  AudioSourceSetPosition3v : procedure(const audioSource : Pointer; const position : PSingle); cdecl;
  AudioSourceSetPosition3f : procedure(const audioSource : Pointer; x, y, z : Single); cdecl;
  AudioSourceSetRelative : procedure(const audioSource : Pointer; isRelative : Boolean); cdecl;
  AudioSourceSetVelocity3v : procedure(const audioSource : Pointer; const velocity : PSingle); cdecl;
  AudioSourceSetVelocity3f : procedure(const audioSource : Pointer; x, y, z : Single); cdecl;
  AudioSourceReset : procedure(const audioSource : Pointer); cdecl;
  AudioSourcePlay : procedure(const audioSource : Pointer; isLoop : Boolean); cdecl;
  AudioSourcePause : procedure(const audioSource : Pointer); cdecl;
  AudioSourceResume : procedure(const audioSource : Pointer); cdecl;
  AudioSourceStop : procedure(const audioSource : Pointer); cdecl;
  AudioSourceUpdate : procedure(const audioSource : Pointer); cdecl;
  AudioSourceIsRelative : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsActive : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsInactive : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsPlaying : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsLooping : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsPaused : function(const audioSource : Pointer) : Boolean; cdecl;
  AudioSourceIsStopped : function(const audioSource : Pointer) : Boolean; cdecl;

var
  audioSysHandle : TLibHandle = 0;

procedure AudioSystemLoadLibrary();
procedure AudioSystemUnloadLibrary();

//{$ENDIF}

implementation

//{$IFNDEF Windows}
procedure AudioSystemLoadLibrary();
begin
  audioSysHandle := SafeLoadLibrary(AUDIO_SYSTEM_LIB);
  if (audioSysHandle = 0) then
    begin
      MessageDlg('Error load "' + AUDIO_SYSTEM_LIB +'"!', mtError, [mbOK], 0);
      exit;
    end;

  @FileManagerInit := GetProcAddress(audioSysHandle, 'FileManagerInit');
  @FileManagerDeinit := GetProcAddress(audioSysHandle, 'FileManagerDeinit');
  @FileManagerMount := GetProcAddress(audioSysHandle, 'FileManagerMount');
  @FileManagerListDirectory := GetProcAddress(audioSysHandle, 'FileManagerListDirectory');
  @FileManagerGetBaseDir := GetProcAddress(audioSysHandle, 'FileManagerGetBaseDir');
  @FileManagerIsInitialized := GetProcAddress(audioSysHandle, 'FileManagerIsInitialized');
                                                                                      
  @AudioSystemInit := GetProcAddress(audioSysHandle, 'AudioSystemInit');
  @AudioSystemDeinit := GetProcAddress(audioSysHandle, 'AudioSystemDeinit');
  @AudioSystemDeleteAllBuffers := GetProcAddress(audioSysHandle, 'AudioSystemDeleteAllBuffers');
  @AudioSystemDeleteAllSources := GetProcAddress(audioSysHandle, 'AudioSystemDeleteAllSources');
  @AudioSystemUpdate := GetProcAddress(audioSysHandle, 'AudioSystemUpdate');
  @AudioSystemSuspend := GetProcAddress(audioSysHandle, 'AudioSystemSuspend');
  @AudioSystemResume := GetProcAddress(audioSysHandle, 'AudioSystemResume');
  @AudioSystemCheckErrorAL := GetProcAddress(audioSysHandle, 'AudioSystemCheckErrorAL');

  @AudioBufferCreate := GetProcAddress(audioSysHandle, 'AudioBufferCreate');
  @AudioBufferDestroy := GetProcAddress(audioSysHandle, 'AudioBufferDestroy');
  @AudioBufferLoad := GetProcAddress(audioSysHandle, 'AudioBufferLoad');
  @AudioBufferUnload := GetProcAddress(audioSysHandle, 'AudioBufferUnload');
  @AudioBufferIsLoaded := GetProcAddress(audioSysHandle, 'AudioBufferIsLoaded');
  @AudioBufferGetBuffer := GetProcAddress(audioSysHandle, 'AudioBufferGetBuffer');
  @AudioBufferGetFileName := GetProcAddress(audioSysHandle, 'AudioBufferGetFileName');
  @AudioBufferIsStreamed := GetProcAddress(audioSysHandle, 'AudioBufferIsStreamed');
                                 
  @AudioListenerInit := GetProcAddress(audioSysHandle, 'AudioListenerInit');
  @AudioListenerSetPosition3v := GetProcAddress(audioSysHandle, 'AudioListenerSetPosition3v');
  @AudioListenerSetOrientation6v := GetProcAddress(audioSysHandle, 'AudioListenerSetOrientation6v');
  @AudioListenerSetVelocity3v := GetProcAddress(audioSysHandle, 'AudioListenerSetVelocity3v');
  @AudioListenerSetPosition3f := GetProcAddress(audioSysHandle, 'AudioListenerSetPosition3f');
  @AudioListenerSetOrientation6f := GetProcAddress(audioSysHandle, 'AudioListenerSetOrientation6f');
  @AudioListenerSetVelocity3f := GetProcAddress(audioSysHandle, 'AudioListenerSetVelocity3f');
  @AudioListenerGetPosition3v := GetProcAddress(audioSysHandle, 'AudioListenerGetPosition3v');
  @AudioListenerGetOrientation6v := GetProcAddress(audioSysHandle, 'AudioListenerGetOrientation6v');
  @AudioListenerGetVelocity3v := GetProcAddress(audioSysHandle, 'AudioListenerGetVelocity3v');
                                                                 
  @AudioSourceCreate := GetProcAddress(audioSysHandle, 'AudioSourceCreate');
  @AudioSourceDestroy := GetProcAddress(audioSysHandle, 'AudioSourceDestroy');
  @AudioSourceSetBuffer := GetProcAddress(audioSysHandle, 'AudioSourceSetBuffer');
  @AudioSourceUnsetBuffer := GetProcAddress(audioSysHandle, 'AudioSourceUnsetBuffer');
  @AudioSourceGetBuffer := GetProcAddress(audioSysHandle, 'AudioSourceGetBuffer');
  @AudioSourceSetLooping := GetProcAddress(audioSysHandle, 'AudioSourceSetLooping');
  @AudioSourceSetPitch := GetProcAddress(audioSysHandle, 'AudioSourceSetPitch');
  @AudioSourceSetGain := GetProcAddress(audioSysHandle, 'AudioSourceSetGain');
  @AudioSourceSetPosition3v := GetProcAddress(audioSysHandle, 'AudioSourceSetPosition3v');
  @AudioSourceSetPosition3f := GetProcAddress(audioSysHandle, 'AudioSourceSetPosition3f');
  @AudioSourceSetRelative := GetProcAddress(audioSysHandle, 'AudioSourceSetRelative');
  @AudioSourceSetVelocity3v := GetProcAddress(audioSysHandle, 'AudioSourceSetVelocity3v');    
  @AudioSourceSetVelocity3f := GetProcAddress(audioSysHandle, 'AudioSourceSetVelocity3f');
  @AudioSourceReset := GetProcAddress(audioSysHandle, 'AudioSourceReset');
  @AudioSourcePlay := GetProcAddress(audioSysHandle, 'AudioSourcePlay');
  @AudioSourcePause := GetProcAddress(audioSysHandle, 'AudioSourcePause');
  @AudioSourceResume := GetProcAddress(audioSysHandle, 'AudioSourceResume');
  @AudioSourceStop := GetProcAddress(audioSysHandle, 'AudioSourceStop');
  @AudioSourceUpdate := GetProcAddress(audioSysHandle, 'AudioSourceUpdate');
  @AudioSourceIsRelative := GetProcAddress(audioSysHandle, 'AudioSourceIsRelative');
  @AudioSourceIsActive := GetProcAddress(audioSysHandle, 'AudioSourceIsActive');
  @AudioSourceIsInactive := GetProcAddress(audioSysHandle, 'AudioSourceIsInactive');
  @AudioSourceIsPlaying := GetProcAddress(audioSysHandle, 'AudioSourceIsPlaying');
  @AudioSourceIsLooping := GetProcAddress(audioSysHandle, 'AudioSourceIsLooping');
  @AudioSourceIsPaused := GetProcAddress(audioSysHandle, 'AudioSourceIsPaused');
  @AudioSourceIsStopped := GetProcAddress(audioSysHandle, 'AudioSourceIsStopped');
end;

procedure AudioSystemUnloadLibrary();
begin
  FreeLibrary(audioSysHandle);
  audioSysHandle := 0;
              
  @FileManagerInit := nil;
  @FileManagerDeinit := nil;
  @FileManagerMount := nil;
  @FileManagerListDirectory := nil;
  @FileManagerGetBaseDir := nil;
  @FileManagerIsInitialized := nil;

  @AudioSystemInit := nil;
  @AudioSystemDeinit := nil;
  @AudioSystemDeleteAllBuffers := nil;
  @AudioSystemDeleteAllSources := nil;
  @AudioSystemUpdate := nil;
  @AudioSystemSuspend := nil;
  @AudioSystemResume := nil;
  @AudioSystemCheckErrorAL := nil;
                                    
  @AudioBufferCreate := nil;
  @AudioBufferDestroy := nil;
  @AudioBufferLoad := nil;
  @AudioBufferUnload := nil;
  @AudioBufferIsLoaded := nil;
  @AudioBufferGetBuffer := nil;
  @AudioBufferGetFileName := nil;
  @AudioBufferIsStreamed := nil;
                                     
  @AudioListenerInit := nil;
  @AudioListenerSetPosition3v := nil;
  @AudioListenerSetOrientation6v := nil;
  @AudioListenerSetVelocity3v := nil;
  @AudioListenerSetPosition3f := nil;
  @AudioListenerSetOrientation6f := nil;
  @AudioListenerSetVelocity3f := nil;
  @AudioListenerGetPosition3v := nil;
  @AudioListenerGetOrientation6v := nil;
  @AudioListenerGetVelocity3v := nil;
                                         
  @AudioSourceCreate := nil;
  @AudioSourceDestroy := nil;
  @AudioSourceSetBuffer := nil;
  @AudioSourceUnsetBuffer := nil;
  @AudioSourceGetBuffer := nil;
  @AudioSourceSetLooping := nil;
  @AudioSourceSetPitch := nil;
  @AudioSourceSetGain := nil;
  @AudioSourceSetPosition3v := nil;
  @AudioSourceSetPosition3f := nil;
  @AudioSourceSetRelative := nil;
  @AudioSourceSetVelocity3v := nil;   
  @AudioSourceSetVelocity3f := nil;
  @AudioSourceReset := nil;
  @AudioSourcePlay := nil;
  @AudioSourcePause := nil;
  @AudioSourceResume := nil;
  @AudioSourceStop := nil;
  @AudioSourceUpdate := nil;
  @AudioSourceIsRelative := nil;
  @AudioSourceIsActive := nil;
  @AudioSourceIsInactive := nil;
  @AudioSourceIsPlaying := nil;
  @AudioSourceIsLooping := nil;
  @AudioSourceIsPaused := nil;
  @AudioSourceIsStopped := nil;
end;    
//{$ENDIF}

end.

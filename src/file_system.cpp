#include <sstream>
#include <iostream>
#include "file_system.h"

using namespace FileSystem;

bool FileManager::isInit = false;

/**
 * File class
 * */

File::File(const std::string fileName, const std::string mode)
{
    open(fileName, mode);
}
File::~File()
{
    close();
}

bool File::exists(const std::string fileName)
{
    if (!FileManager::IsInitialized())
        FileManager::Init(nullptr);

    return (PHYSFS_exists(fileName.c_str()));
}
std::string File::extractExt(const std::string fileName, bool toLower)
{
    size_t pos = fileName.find_last_of(".");
    std::string ext = fileName.substr(pos, fileName.size() - pos);

    if (toLower)
    {
        for (std::string::iterator c = ext.begin(); c != ext.end(); ++c)
            *c = tolower(*c);
    }

    return ext;
}
int64_t File::size(const std::string fileName)
{
    if (exists(fileName))
    {
        PHYSFS_file* file = PHYSFS_openRead(fileName.c_str());
        int64_t len = PHYSFS_fileLength(file);
        PHYSFS_close(file);
        return len;
    }

    return -1;
}
bool File::readFull(const std::string fileName, char** buffer, uint64_t* bufferSize)
{
    if (!exists(fileName))
        return false;

    File* file = new File(fileName);
    if (!file)
        return false;

    bool result = file->readFull(buffer, bufferSize);
    delete (file);

    return result;
}

bool File::open(const std::string fileName, const std::string mode)
{
    if (!exists(fileName))
        return false;

    if (this->m_handle)
        close();

    if (mode == "r")
        this->m_handle = PHYSFS_openRead(fileName.c_str());
    else
        if (mode == "w")
            this->m_handle = PHYSFS_openWrite(fileName.c_str());
        else
            if (mode == "a")
                this->m_handle = PHYSFS_openAppend(fileName.c_str());

    this->m_fileName = fileName;
}

void File::close()
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        PHYSFS_close(this->m_handle);
        this->m_handle = nullptr;
    }

    this->m_fileName = "";
}

int64_t File::size()
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return (PHYSFS_fileLength(this->m_handle));
    }
    return -1;
}

int64_t File::tell()
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return PHYSFS_tell(this->m_handle);
    }
    return -1;
}

int File::seek(uint64_t position)
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return PHYSFS_seek(this->m_handle, position);
    }
    return -1;
}

int64_t File::read(char* buffer, uint64_t length)
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return PHYSFS_readBytes(this->m_handle, buffer, length);
    }
    return -1;
}

int64_t File::write(const char* buffer, uint64_t length)
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return PHYSFS_writeBytes(this->m_handle, buffer, length);
    }
    return -1;
}

bool File::readFull(char** buffer, uint64_t* bufferSize)
{
    if (!this->m_handle)
        return false;

    free(*buffer);
    *buffer = nullptr;

    int64_t fileSize = size();
    *buffer = (char*)calloc(fileSize, 1);  /* добавим в конце 0 для пущей уверенности */
    *bufferSize = fileSize;
    seek(0);
    int64_t readed = read(*buffer, fileSize);
    if (readed != fileSize)
    {
        std::cout << "Count of readed bytes and size of file '" << m_fileName << "' are not equal!" << std::endl;
        return false;
    }

    return true;
}

bool File::eof()
{
    if (this->m_handle)
    {
        if (!FileManager::IsInitialized())
            FileManager::Init(nullptr);

        return (PHYSFS_eof(this->m_handle) != 0);
    }
    return true;
}


/**
 * FileManager class
 * */

FileManager::FileManager(const std::string argv0)
{
    Init(argv0);
}

FileManager::~FileManager()
{
    Deinit();
}

void FileManager::Init(const std::string argv0)
{
    if (isInit)
        return;

    // Need to initialize PhysFS before using it
    if (PHYSFS_init(argv0.c_str()) == 0)
    {
        std::cout << "Failed to initialize PhysFS." << std::endl;
        PrintLastError();
    }
    isInit = true;

    std::cout << "Initialized PhysFS, supported archive formats:";
    for (const PHYSFS_ArchiveInfo** i = PHYSFS_supportedArchiveTypes(); *i != nullptr; ++i)
        std::cout << "\n  " << (*i)->extension << ": " << (*i)->description;
    std::cout << std::endl;
}

void FileManager::Deinit()
{
    if (isInit)
    {
        PHYSFS_deinit();
        isInit = false;
    }
}

bool FileManager::Mount(const std::string path, const char* mountPoint, int append)
{
    if (!isInit)
        Init();

    if (PHYSFS_mount(path.c_str(), mountPoint, append) == 0)
    {
        std::cout << "Failed to add \"" << path << "\"" << std::endl;
        PrintLastError();
        return false;
    }
    return true;
}

void FileManager::ListDirectory(std::string&& dir)
{
    if (!isInit)
        Init();

    char** files = PHYSFS_enumerateFiles(dir.c_str());
    PHYSFS_Stat stat;
    for(int i = 0; files[i]; ++i)
    {
        std::string file = dir + files[i];

        if (!PHYSFS_stat(file.c_str(), &stat))
        {
            PrintLastError();
            continue;
        }

        if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY)
            ListDirectory(file + "/");
        else
            std::cout << "  " << file << std::endl;
    }
    PHYSFS_freeList(files);
}

bool FileSystem::IsErrorExists()
{
    return (PHYSFS_getLastErrorCode() != PHYSFS_ERR_OK);
}

void FileSystem::PrintLastError()
{
    if (FileSystem::IsErrorExists())
    {
        PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();
        std::cout << "Error: " << PHYSFS_getErrorByCode(errorCode) << std::endl;
    }
}

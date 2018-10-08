#include <sstream>
#include <iostream>
#include <streambuf>
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
 * PhysFSBuf class
 **/

PhysFSBuf::int_type PhysFSBuf::underflow()
{
    if(mFile && gptr() == egptr())
    {
        // Read in the next chunk of data, and set the read pointers on
        // success
        PHYSFS_sint64 got = PHYSFS_read(mFile,
            mBuffer.data(), sizeof(char_type), mBuffer.size()
        );

        if(got != -1)
            setg(mBuffer.data(), mBuffer.data(), mBuffer.data()+got);
    }

    if (gptr() == egptr())
        return traits_type::eof();

    return traits_type::to_int_type(*gptr());
}

PhysFSBuf::pos_type PhysFSBuf::seekoff(off_type offset, std::ios_base::seekdir whence, std::ios_base::openmode mode)
{
    if(!mFile || (mode&std::ios_base::out) || !(mode&std::ios_base::in))
        return traits_type::eof();

    // PhysFS only seeks using absolute offsets, so we have to convert cur-
    // and end-relative offsets.
    PHYSFS_sint64 fpos;
    switch(whence)
    {
        case std::ios_base::beg:
            break;

        case std::ios_base::cur:
            // Need to offset for the file offset being at egptr() while
            // the requested offset is relative to gptr().
            offset -= off_type(egptr()-gptr());
            if((fpos=PHYSFS_tell(mFile)) == -1)
                return traits_type::eof();
            // If the offset remains in the current buffer range, just
            // update the pointer.
            if(offset < 0 && -offset <= off_type(egptr()-eback()))
            {
                setg(eback(), egptr()+offset, egptr());
                return fpos + offset;
            }
            offset += fpos;
            break;

        case std::ios_base::end:
            if((fpos=PHYSFS_fileLength(mFile)) == -1)
                return traits_type::eof();
            offset += fpos;
            break;

        default:
            return traits_type::eof();
    }

    if(offset < 0) return traits_type::eof();
    if(PHYSFS_seek(mFile, offset) == 0)
    {
        // HACK: Workaround a bug in PhysFS. Certain archive types error
        // when trying to seek to the end of the file. So if seeking to the
        // end of the file fails, instead try seeking to the last byte and
        // read it.
        if(offset != PHYSFS_fileLength(mFile))
            return traits_type::eof();
        if(PHYSFS_seek(mFile, offset-1) == 0)
            return traits_type::eof();
        PHYSFS_read(mFile, mBuffer.data(), 1, 1);
    }
    // Clear read pointers so underflow() gets called on the next read
    // attempt.
    setg(nullptr, nullptr, nullptr);
    return offset;
}

PhysFSBuf::pos_type PhysFSBuf::seekpos(pos_type pos, std::ios_base::openmode mode)
{
    // Simplified version of seekoff
    if(!mFile || (mode&std::ios_base::out) || !(mode&std::ios_base::in))
        return traits_type::eof();

    if(PHYSFS_seek(mFile, pos) == 0)
        return traits_type::eof();
    setg(nullptr, nullptr, nullptr);
    return pos;
}

bool PhysFSBuf::open(const char *filename) noexcept
{
    mFile = PHYSFS_openRead(filename);
    if(!mFile) return false;
    return true;
}

PhysFSBuf::~PhysFSBuf()
{
    PHYSFS_close(mFile);
    mFile = nullptr;
}


/**
 * FileManager class
 * */

FileManager::FileManager(const char* argv0)
{
    Init(argv0);
}

FileManager::~FileManager()
{
    Deinit();
}

alure::UniquePtr<std::istream> FileManager::openFile(const alure::String &name) noexcept
{
    auto stream = alure::MakeUnique<Stream>(name.c_str());
    if (stream->fail())
        stream = nullptr;
    return std::move(stream);
}

void FileManager::Init(const char* argv0)
{
    if (isInit)
        return;

    // Need to initialize PhysFS before using it
    if (PHYSFS_init(argv0) == 0)
        throw std::runtime_error(alure::String("Failed to initialize PhysFS: ") +
                                 PHYSFS_getLastError());
    isInit = true;
/*
    std::cout<< "Initialized PhysFS, supported archive formats:";
    for(const PHYSFS_ArchiveInfo **i = PHYSFS_supportedArchiveTypes();*i != NULL;i++)
        std::cout<< "\n  "<<(*i)->extension<<": "<<(*i)->description;
    std::cout<<std::endl;
 */
}

void FileManager::Deinit()
{
    if (isInit)
    {
        PHYSFS_deinit();
        isInit = false;
    }
}

bool FileManager::Mount(const char* path, const char *mountPoint, int append)
{
    if (!isInit)
        Init();

    if (PHYSFS_mount(path, mountPoint, append) == 0)
    {
        std::cout << "Failed to add \"" << path << "\": " << PHYSFS_getLastError() << std::endl;
        return false;
    }
    return true;
}

void FileManager::ListDirectory(std::string&& dir)
{
    if (!isInit)
        Init();

    char** files = PHYSFS_enumerateFiles(dir.c_str());
    for(int i = 0;files[i];++i)
    {
        std::string file = dir + files[i];
        if(PHYSFS_isDirectory(file.c_str()))
            ListDirectory(file+"/");
        else
            std::cout<<"  "<<file<<"\n";
    }
    PHYSFS_freeList(files);
}

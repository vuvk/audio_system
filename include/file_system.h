#pragma once
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include "alure2.h"
#include "physfs.h"


namespace FileSystem
{
    class File
    {
    private :
        PHYSFS_file* m_handle = nullptr;
        std::string m_fileName = "";

    public:
        File(const std::string fileName = "", const std::string mode = "r");
        ~File();

        static bool exists(const std::string fileName);
        static std::string extractExt(const std::string fileName, bool toLower = false);
        static int64_t size(const std::string fileName);
        static bool readFull(const std::string fileName, char** buffer, uint64_t* bufferSize);

        bool open(const std::string fileName, const std::string mode = "r");
        void close();
        int64_t size();
        int64_t tell();
        int seek(uint64_t position);
        int64_t read(char* buffer, uint64_t length);
        bool readFull(char** buffer, uint64_t* bufferSize);
        bool eof();
    };


    // Inherit from std::streambuf to handle custom I/O (PhysFS for this example)
    class PhysFSBuf final : public std::streambuf
    {
    public:
        bool open(const char *filename) noexcept;

        PhysFSBuf() = default;
        ~PhysFSBuf() override;
    private:
        alure::Array<char_type,4096> mBuffer;
        PHYSFS_File *mFile{nullptr};

        int_type underflow() override;
        pos_type seekoff(off_type offset, std::ios_base::seekdir whence, std::ios_base::openmode mode) override;
        pos_type seekpos(pos_type pos, std::ios_base::openmode mode) override;
    };


    // Inherit from std::istream to use our custom streambuf
    class Stream final : public std::istream
    {
    public:
        Stream(const char *filename) : std::istream(nullptr)
        {
            init(&mStreamBuf);

            // Set the failbit if the file failed to open.
            if(!mStreamBuf.open(filename))
                clear(failbit);
        }

    private:
        PhysFSBuf mStreamBuf;
    };


    // Inherit from alure::FileIOFactory to use our custom istream
    class FileManager final : public alure::FileIOFactory
    {
    public:
        FileManager(const char* argv0 = nullptr);
        ~FileManager() override;

        alure::UniquePtr<std::istream> openFile(const alure::String &name) noexcept override;
        static void Init(const char* argv0 = nullptr);
        static void Deinit();

        // A PhysFS-specific function to mount a new path to the virtual directory
        // tree.
        static bool Mount(const char *path, const char *mountPoint=nullptr, int append=0);
        static void ListDirectory(std::string&& dir);

        inline static IsInitialized()
        {
            return isInit;
        }

    private:
        static bool isInit;
    };
}

#endif // FILE_SYSTEM_H

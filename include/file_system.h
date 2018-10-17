#pragma once
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include "physfs.h"


namespace FileSystem
{
    class File
    {
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
        int64_t write(const char* buffer, uint64_t length);
        bool readFull(char** buffer, uint64_t* bufferSize);
        bool eof();

    private :
        PHYSFS_file* m_handle = nullptr;
        std::string m_fileName = "";
    };

    class FileManager
    {
    public:
        FileManager(const char* argv0 = nullptr);
        ~FileManager();

        static void Init(const char* argv0 = nullptr);
        static void Deinit();

        // A PhysFS-specific function to mount a new path to the virtual directory
        // tree.
        static bool Mount(const char *path, const char *mountPoint=nullptr, int append=0);
        static void ListDirectory(std::string&& dir);

        inline static bool IsInitialized()
        {
            return isInit;
        }

    private:
        static bool isInit;
    };

    bool IsErrorExists();
    void PrintLastError();
}

#endif // FILE_SYSTEM_H

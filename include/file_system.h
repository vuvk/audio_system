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
        File(const std::string& fileName = "", const std::string& mode = "r");
        ~File();

        static bool exists(const std::string& fileName);
        static std::string extractExt(const std::string& fileName, bool toLower = false);
        static int64_t size(const std::string& fileName);
        static bool readFull(const std::string& fileName, char** buffer, uint64_t* bufferSize);

        bool open(const std::string& fileName, const std::string& mode = "r");
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
        static void Init(const std::string& argv0 = "");
        static void Deinit();

        // A PhysFS-specific function to mount a new path to the virtual directory
        // tree.
        static bool Mount(const std::string& path, const std::string& mountPoint = "", int append = 0);
        static void ListDirectory(std::string&& dir);
        static std::string GetBaseDir();

        inline static bool IsInitialized()
        {
            return isInit;
        }

    private:
        FileManager(const std::string argv0 = "");
        ~FileManager();
        static bool isInit;
        static std::string baseDir;
    };

    bool IsErrorExists();
    void PrintLastError();
}

#endif // FILE_SYSTEM_H

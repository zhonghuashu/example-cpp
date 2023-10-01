/**
 * @file fileio.cpp
 * @brief Low level file access use system call directly for input / output is less inefficient, unbuffered I/O.
 * - System call expensive compared to function call
 * - Write an amount that is not multiple of IO data block size
 * @author Shu, Zhong Hua
 * @date 2023-05-31
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace {

const std::string mInFile = "CMakeLists.txt";
const std::string mOutFile1 = "CMakeLists.txt.copy1";
const std::string mOutFile2 = "CMakeLists.txt.copy2";

void copyFileByChar()
{
    char c;
    int in, out;

    if ((in = ::open(mInFile.c_str(), O_RDONLY)) < 0)
    {
        ::perror("Open in file failed");
    }

    // -rw------- 1 root root   2984 May 31 22:29 CMakeLists.txt.copy
    if ((out = ::open(mOutFile1.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
    {
        ::perror("Open out file failed");
    }

    while (1 == ::read(in, &c, 1))
    {
        ::write(out, &c, 1);
    }
    if (::close(in) < 0)
    {
        ::perror("Close in file failed");
    }
    if (::close(out) < 0)
    {
        ::perror("Close out file failed");
    }
}

void copyFileByBlock()
{
    char block[1024];
    int in, out;
    ssize_t nread;

    if ((in = ::open(mInFile.c_str(), O_RDONLY)) < 0)
    {
        ::perror("Open in file failed");
    }

    // -rw------- 1 root root   2984 May 31 22:29 CMakeLists.txt.copy
    if ((out = ::open(mOutFile2.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
    {
        ::perror("Open out file failed");
    }

    while ((nread = ::read(in, block, sizeof(block))) > 0)
    {
        ::write(out, block, (size_t)nread);
    }

    if (::close(in) < 0)
    {
        ::perror("Close in file failed");
    }
    if (::close(out) < 0)
    {
        ::perror("Close out file failed");
    }
}

}

int main()
{

    // Copy file character by character.
    copyFileByChar();
    // Copy file in larger block.
    copyFileByBlock();

    if (::unlink(mOutFile1.c_str()) < 0)
    {
        ::perror("Delete out file failed");
    }

    if (::unlink(mOutFile2.c_str()) < 0)
    {
        ::perror("Delete out file failed");
    }

    ::exit(0);
}


/**
 * @file stdio.cpp
 * @brief The standard I/O library (stdio) provide a versatile interface to low-level I/O system call.
 * stdio maintain internal buffered in FILE structure, efficiently write data block of different size.
 * @author Shu, Zhong Hua
 * @date 2023-05-31
 */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>

namespace {

const std::string mInFile = "CMakeLists.txt";
const std::string mOutFile1 = "CMakeLists.txt.copy1";
const std::string mOutFile2 = "CMakeLists.txt.copy2";

void copyFileByChar()
{
    int c;
    FILE *in, *out;

    if (nullptr == (in = ::fopen(mInFile.c_str(), "r")))
    {
        ::perror("Open in file failed");
    }

    if (nullptr == (out = ::fopen(mOutFile1.c_str(), "w")))
    {
        ::perror("Open out file failed");
    }

    while ((c = ::fgetc(in)) != EOF)
    {
        ::fputc(c, out);
    }

    if (in != nullptr && ::fclose(in) < 0)
    {
        ::perror("Close in file failed");
    }
    if (out != nullptr && ::fclose(out) < 0)
    {
        ::perror("Close out file failed");
    }
}

void copyFileByBlock()
{
    FILE *in, *out;
    char block[1024];

    if (nullptr == (in = ::fopen(mInFile.c_str(), "r")))
    {
        ::perror("Open in file failed");
    }

    if (nullptr == (out = ::fopen(mOutFile2.c_str(), "w")))
    {
        ::perror("Open out file failed");
    }

    while ((::fgets(block, sizeof(block), in)) != nullptr)
    {
        ::fputs(block, out);
        ::puts(block);  // equivalent to fputs(block, stdout)
    }

    // Flush buffer to output inexplicit.
    if (in != nullptr && ::fclose(in) < 0)
    {
        ::perror("Close in file failed");
    }
    if (out != nullptr && ::fclose(out) < 0)
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

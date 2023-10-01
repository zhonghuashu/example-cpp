/**
 * @file printdir.cpp
 * @brief Prints out the current directory.
 * It will recurse for subdirectories, using the depth parameter is used for indentation.
 * @author Shu, Zhong Hua
 * @date 2023-06-02
 */

#include <cstdio>
#include <string>
#include <cstdlib>

#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>

namespace {

void printdir(const char * const dir, const int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if (nullptr == (dp = ::opendir(dir)))
    {
        ::fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }

    ::chdir(dir);
    while ((entry = ::readdir(dp)) != nullptr)
    {
        ::lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            /* Found a directory, but ignore . and .. */
            if (0 == ::strcmp(".", entry->d_name) ||
                0 == ::strcmp("..", entry->d_name))
            {
                continue;
            }

            ::printf("%*s%s/\n", depth, "", entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name, depth + 4);
        }
        else
        {
            ::printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    ::chdir("..");
    ::closedir(dp);
}

}

/*  Now we move onto the main function.  */

int main(int argc, char *argv[])
{
    char *topdir, pwd[2] = ".";
    if (argc != 2)
    {
        topdir = pwd;
    }
    else
    {
        topdir = argv[1];
    }

    ::printf("Directory scan of %s\n", topdir);
    ::printdir(topdir, 0);
    ::printf("done.\n");

    ::exit(0);
}



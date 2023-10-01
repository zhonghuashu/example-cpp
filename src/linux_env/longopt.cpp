/**
 * @file longopt.cpp
 * @brief Program arguments accept single character or longer meaningful arguments.
 * Example:
 * <program> --initialize --list 'hi there'  --file fred.c -q
 * <program> -i -l "hi there"  -f fred.c -q
 * @author Shu, Zhong Hua
 * @date 2023-06-02
 */
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#define _GNU_SOURCE
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    const int OPT_LEN = 5;
    struct option longopts[OPT_LEN] =
    {
        {"initialize", 0, nullptr, 'i'},
        {"file", 1, nullptr, 'f'},
        {"list", 0, nullptr, 'l'},
        {"restart", 0, nullptr, 'r'},
        {nullptr, 0, nullptr, 0}
    };

    // Placing a colon as the first character of the options string, getopt returns : if no value given after argument.
    while ((opt = ::getopt_long(argc, argv, ":if:lr", longopts, nullptr)) != -1)
    {
        switch (opt)
        {
            case 'i':
            case 'l':
            case 'r':
                ::printf("option: %c\n", opt);
                break;
            case 'f':
                ::printf("filename: %s\n", ::optarg);
                break;
            case ':':
                ::printf("option needs a value\n");
                break;
            case '?':
                ::printf("unknown option: %c\n", ::optopt);
                break;
            default:
                break;
        }
    }
    for (; ::optind < argc; ::optind++)
    {
        ::printf("argument: %s\n", argv[::optind]);
    }

    ::exit(0);
}

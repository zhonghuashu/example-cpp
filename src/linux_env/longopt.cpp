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
#include <sstream>

#include <getopt.h>

namespace {

void printUsage()
{
    ::printf("Usage: \n");
    ::printf(" longopt [options]\n");
    ::printf("Demo get_optlong usage.\n");
    ::printf("Options: \n");
    ::printf("-i, --initialize          initialize system\n");
    ::printf("-f, --file <file name>    file name\n");
    ::printf("-l, --list                list options\n");
    ::printf("-r, --restart             restart system\n");
    ::printf("-h, --help                print help info\n");
}
}
int main(int argc, char *argv[])
{
    int opt;
    std::ostringstream cmdLine;
    struct option longopts[] =
    {
        {"initialize",  0, nullptr, 'i'},
        {"file",        1, nullptr, 'f'},
        {"list",        0, nullptr, 'l'},
        {"restart",     0, nullptr, 'r'},
        {"help",        0, nullptr, 'h'},
        {nullptr,       0, nullptr, 0}
    };

    for (int i = 0; i < argc; i++)
    {
        cmdLine << argv[i] << " ";
    }
    cmdLine << "\n";
    printf("%s\n", cmdLine.str().c_str());

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
                /*
                If an option requires a value (such as -fin our example) and no value is given, getoptnor-
                mally returns ?. By placing a colon as the first character of the options string, getoptreturns :
                instead of ? when no value is given.
                */
                ::printf("option needs a value\n");
                break;
           case 'h':
                printUsage();
                break;
            case '?':
                // getoptreturns ?if there is an unrecognized option.
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

    if (argc < 2)
    {
        printUsage();
    }

    ::exit(0);
}

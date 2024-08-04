#include <iostream>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int sleepUs = 1;
    if (argv[1] != nullptr)
    {
        sleepUs = ::atoi(argv[1]);
    }

    // 1 sec ticks
    int count = 1000 * 1000 / sleepUs;
    int i = 0;
    int j = 0;
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = sleepUs * 1000;

    std::cout << "Top test started" << std::endl;
    while (true)
    {
        if (++i > count)
        {
            i = 0;
            std::cout << j << std::endl;
            j++;
        }
        ::nanosleep(&ts, nullptr);
    }

    return 0;
}
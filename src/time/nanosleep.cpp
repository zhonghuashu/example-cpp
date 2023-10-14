/**
 * @file nanosleep.cpp
 * @brief 精度是纳秒级, 暂停某个进程直到你规定的时间后恢复
 * @author Shu, Zhong Hua
 * @date 2023-10-14
 */

#include <stdio.h>
#include <time.h>

#define s  5          // 5s
#define ns 999999999 // 大概是1s

int main(int argc, char *argv[])
{
    struct timespec s_sleep;
    struct timespec ns_sleep;
    s_sleep.tv_sec = s;
    s_sleep.tv_nsec = 0;
    ns_sleep.tv_sec = 0;
    ns_sleep.tv_nsec = ns;

    while (true)
    {
        nanosleep(&s_sleep, nullptr);
        printf("5 seconds passed...\n");

        nanosleep(&ns_sleep, nullptr);
        printf("1 seconds passed...\n");
        printf("\n");
    }

    return 0;
}

/**
 * @file mssleep.cpp
 * @brief 利用nanosleep函数实现毫秒级函数
 * @author Shu, Zhong Hua
 * @date 2023-10-14
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define ms_sleep 5000

void mssleep(unsigned long ms);

int main(int argc, char *argv[])
{
    while (true)
    {
        mssleep(ms_sleep);
        printf("5 seconds passed...\n");
    }
    return 0;
}

void mssleep(unsigned long ms)
{
    struct timespec ts = {
          .tv_sec = (long int)(ms / 1000),
          .tv_nsec = (long int)(ms % 1000) * 1000000L
    };
    nanosleep(&ts, nullptr);
}

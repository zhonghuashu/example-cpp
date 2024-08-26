/**
 * @file timestamp.cpp
 * @brief Get current timestamp and calculate time difference in ms.
 * @author Shu, Zhong Hua
 * @date 2024-08-08
 */

#include <ctime>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <chrono>
#include <time.h>
#include <semaphore.h>

using namespace std::chrono;

int main(int argc, char *argv[])
{

    // Use time()
    time_t seconds = ::time((time_t*)nullptr);
    ::printf("time: %d ms elapsed\n", (int)(seconds * 1000));

    // Use gettimeofday()
	struct timeval tv;
    ::gettimeofday(&tv, nullptr);
    ::printf("timeval: %d sec, %d us\n", (int) tv.tv_sec, (int) tv.tv_usec);
    ::printf("timeval: %d ms elapsed\n", (int)((tv.tv_sec * 1000 * 1000 + tv.tv_usec) / 1000));

    // Use clock_gettime
    timespec tpstart;
    timespec tpend;
    long timediff;

    ::clock_gettime(CLOCK_MONOTONIC, &tpstart);
    ::sleep(1);
    ::clock_gettime(CLOCK_MONOTONIC, &tpend);
    timediff = 1000 * 1000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec-tpstart.tv_nsec) / 1000;
    ::printf("clock_gettime: %ld ms elapsed\n", timediff / 1000);

    // Use C++11 chrono lib (see https://zhuanlan.zhihu.com/p/559873639)
    std::cout << "system_clock::is_steady: " << std::boolalpha << system_clock::is_steady << std::endl;
    std::cout << "steady_clock::is_steady: " << std::boolalpha << steady_clock::is_steady << std::endl;
    std::cout << "high_resolution_clock::is_steady: " << std::boolalpha << high_resolution_clock::is_steady << std::endl;

    system_clock::time_point start = system_clock::now();

    ::sleep(1);

    duration<double> timeGap = system_clock::now() - start;
    std::cout << "time diff 1: " << ::duration_cast<milliseconds>(timeGap).count() << " ms\n";

    std::time_t timeT = system_clock::to_time_t(system_clock::now());
    std::cout << "gm time: " << ::asctime(::gmtime(&timeT));
    std::cout << "local time: " << ::asctime(::localtime(&timeT));
    tm* currTime = ::localtime(&timeT);
    ::printf("Current time: %04d-%02d-%02d %02d:%02d:%02d\n", currTime->tm_year + 1900, currTime->tm_mon + 1, currTime->tm_mday,
            currTime->tm_hour, currTime->tm_min, currTime->tm_sec);

    duration<double> timeGap1 = system_clock::now() - system_clock::from_time_t(timeT);
    std::cout << "time diff 2: " << ::duration_cast<milliseconds>(timeGap1).count() << " ms\n";


    // Use timed sem_wait sec
    struct timespec ts;
    sem_t sem;

    ::sem_init(&sem, 0, 0);
    ::clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 1;

    ::printf("Semaphore wait...\n");
    ::sem_timedwait(&sem, &ts);
    ::printf("Semaphore wait... timeout\n");
    sem_destroy(&sem);

    // Use timed sem_wait ms
    sem_t sem2;
    struct timespec timeout;
    sem_init(&sem2, 0, 0);
    timeout.tv_nsec += 100 * 1000 * 1000;
    if (timeout.tv_nsec >= 1000000000)
    {
        timeout.tv_nsec -= 1000000000;
        timeout.tv_sec += 1;
    }

    // 等待信号量
    ::printf("Semaphore wait...\n");
    sem_timedwait(&sem2, &timeout);
    ::printf("Semaphore wait... timeout\n");
    sem_destroy(&sem2);


	return 0;
}

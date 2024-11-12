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

    /*
    Use time() -- timer.h from C standard lib.
    - Time resolution up to seconds.
    */
    // Get seconds since 1970 year.
    time_t seconds = ::time((time_t*)nullptr);
    ::printf("time: %ld ms elapsed\n", (long)(seconds * 1000));
    tm currTime;
    // xxx_r: thread-safe function.
    ::gmtime_r(&seconds, &currTime);
    ::printf("time: UTC:  %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec, (long) 0);
    ::localtime_r(&seconds, &currTime);
    ::printf("time: local: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec, (long) 0);

    ::printf("\n");

    /*
    Use gettimeofday() -- sys/time.h from Linux function.
    - Time resolution up to microseconds (us).
    */
	struct timeval tv;
    ::gettimeofday(&tv, nullptr);
    ::printf("gettimeofday: timeval: %d sec, %d us\n", (int) tv.tv_sec, (int) tv.tv_usec);
    ::localtime_r(&tv.tv_sec, &currTime);
    ::printf("gettimeofday: local: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec, tv.tv_usec / 1000);

    ::printf("\n");

    /*
    Use clock_gettime -- timer.h from C standard lib.
    - Posix High resolution time up to nanoseconds (ns)
    - CLOCK_REALTIME: Current Linux system time, changed by NTP.
    - CLOCK_MONOTONIC: Absolute elapsed time, not changed as Linux system time (e.g., NTP)
    */
    timespec tpstart;
    timespec tpend;
    long timediff;

    // clock_gettime: local: 1970-01-01 10:59:13.523
    ::clock_gettime(CLOCK_MONOTONIC, &tpstart);
    ::localtime_r(&tpstart.tv_sec, &currTime);
    ::printf("clock_gettime: CLOCK_MONOTONIC: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec, tpstart.tv_nsec / 1000 / 1000);
    ::sleep(1);
    ::clock_gettime(CLOCK_MONOTONIC, &tpend);
    timediff = 1000 * 1000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec-tpstart.tv_nsec) / 1000;
    ::printf("clock_gettime: CLOCK_MONOTONIC: %ld ms elapsed\n", timediff / 1000);

    // clock_gettime: local: 2024-10-20 14:59:53.942
    ::clock_gettime(CLOCK_REALTIME, &tpstart);
    ::localtime_r(&tpstart.tv_sec, &currTime);
    ::printf("clock_gettime: CLOCK_REALTIME: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec, tpstart.tv_nsec / 1000 / 1000);

    ::sleep(1);
    ::clock_gettime(CLOCK_REALTIME, &tpend);
    timediff = 1000 * 1000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec-tpstart.tv_nsec) / 1000;
    ::printf("clock_gettime: CLOCK_REALTIME: %ld ms elapsed\n", timediff / 1000);

    // Use clock() / time.h function to calculate program running ticks.
    clock_t startClock;
    clock_t endClock;
    startClock = clock();
    for (int i = 0; i < 100000000; i++) { /* empty */ }
    endClock = clock();
    ::printf("clock: %f ms elapsed\n", (double)(endClock - startClock) / CLOCKS_PER_SEC);

    ::printf("\n");

    /*
    Use C++11 chrono lib (see https://zhuanlan.zhihu.com/p/559873639)
    - system_clock: up to microseconds (us), Changed according Linux time (e.g., NTP)
    - steady_clock: up to nanoseconds (ns), suitable for measure program spend time.
    - high_resolution_clock: up to nanoseconds, equals to high resolution steady_clock.
    */

    std::cout << "chrono: system_clock::is_steady: " << std::boolalpha << system_clock::is_steady << std::endl;
    std::cout << "chrono: steady_clock::is_steady: " << std::boolalpha << steady_clock::is_steady << std::endl;
    std::cout << "chrono: high_resolution_clock::is_steady: " << std::boolalpha << high_resolution_clock::is_steady << std::endl;

    system_clock::time_point start = system_clock::now();
    std::time_t timeStart = system_clock::to_time_t(start);
    ::localtime_r(&timeStart, &currTime);
    ::printf("chrono: start: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec,
            (long)((::duration_cast<milliseconds>(start.time_since_epoch())).count() % 1000));
    ::sleep(1);

    system_clock::time_point end = system_clock::now();
    duration<double> timeGap = end - start;
    std::cout << "chrono: time diff 1: " << ::duration_cast<milliseconds>(timeGap).count() << " ms\n";

    std::time_t timeEnd = system_clock::to_time_t(end);
    std::cout << "chrono: gm time: " << ::asctime(::gmtime(&timeEnd));
    std::cout << "chrono: local time: " << ::asctime(::localtime(&timeEnd));
    ::localtime_r(&timeEnd, &currTime);
    ::printf("chrono: end: %04d-%02d-%02d %02d:%02d:%02d.%03ld\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday, currTime.tm_hour, currTime.tm_min, currTime.tm_sec,
            (long) ((::duration_cast<milliseconds>(end.time_since_epoch())).count() % 1000));

    duration<double> timeGap2 = system_clock::now() - system_clock::from_time_t(timeEnd);
    std::cout << "chrono: time diff 2: " << ::duration_cast<milliseconds>(timeGap2).count() << " ms\n";

    ::printf("\n");

    /*
    Use timed sem_wait sec
    */
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
    ::sem_init(&sem2, 0, 0);
    timeout.tv_nsec += 100 * 1000 * 1000;
    if (timeout.tv_nsec >= 1000000000)
    {
        timeout.tv_nsec -= 1000000000;
        timeout.tv_sec += 1;
    }

    // 等待信号量
    ::printf("Semaphore wait...\n");
    ::sem_timedwait(&sem2, &timeout);
    ::printf("Semaphore wait... timeout\n");
    ::sem_destroy(&sem2);

    ::printf("\n");

	return 0;
}

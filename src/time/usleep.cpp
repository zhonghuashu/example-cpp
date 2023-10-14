/**
 * @file usleep.cpp
 * @brief 阻塞的, 休眠秒或微妙，应用在短暂延时场合
 * @author Shu, Zhong Hua
 * @date 2023-10-14
 */
#include <stdio.h>
#include <unistd.h>

#define s  5000000  //5s

int main(int argc, char *argv[])
{
	while(true)
	{
        // Remove use of this obsolete "usleep" function. Replace it by a call to "nanosleep" or "setitimer".sonarlint(cpp:S1911).
		usleep(s);
		printf("5 seconds passed...\n");
	}
	return 0;
}

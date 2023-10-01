/**
 * @file hello_c.c
 * @brief Sample code for demonstrate the usage of C programming language.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "usage_func.h"
#include "usage_cplus.h"
#include "config.h"

int main()
{
    printf("Hello World C demo program (Version: %d.%d.%d)\n", APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH);

    usage_cmain();
    usage_cplusExternLinkage();

    return EXIT_SUCCESS;
}

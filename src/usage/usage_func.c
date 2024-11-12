/**
 * @file
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "usage_func.h"

bool usage_cmain()
{
    usage_switch();
    usage_ifElse();
    usage_macro();
    usage_print();
    usage_integer();

    return true;
}

void usage_switch()
{
    printf("\n#### Usage: switch case\n");
    enum Status
    {
        STATUS_OK = 1,
        STATUS_FAIL = 2
    };

    int i = 0;

    switch (i)
    {
        case STATUS_OK:
            printf("case 1\n");
            break;
        case STATUS_FAIL:
            printf("case 2\n");
            break;
        default:
            break;
    }

    printf("\n");
}

bool usage_ifElse()
{
    printf("\n#### Usage: if else\n");

    bool value = true;

    if (value == false)
    {
        // This rule shall be disabled in sonar qube:
        // A function should have a single point of exit at the end of the function (c:S1005)
        return false;
    }

    return true;
}

void usage_macro()
{
    printf("\n#### Usage: macro\n");
    #define BASE_RT_PRIO 20
    int prio = BASE_RT_PRIO + 1;

    printf("priority: %d", prio);
    printf("\n");
}

void usage_print()
{
    double val = 10.0 / 3.0;
    printf("\n#### Usage: print\n");
    printf("%15s = %10d\n", "String", 10);
    printf("%15s = %5.1f\n", "Double", val);
    printf("\n");
}

void usage_integer()
{
    printf("\n#### Usage: integer\n");
    unsigned char ival = 250;
    printf("ival = ");
    for (int i = 0; i < 10; i++)
    {
        // Check if round to 0 after 255.
        ival++;
        printf("%d ", ival);
    }
    printf("\n\n");
}
/**
 * @file usage_func.h
 * @brief Common usage of C programming language.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#ifndef USAGE_FUNC_H
#define USAGE_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Test C language usage function.
 * @return true if success.
 */
bool usage_cmain();

/**
 * Example usage for switch statement.
 * - Use switch / case.
 * - Always write default case at last case.
 * - Don't forgot add `break` in the case.
 */
void usage_switch();

/**
 * Example usage for if / else statement.
 * @return true if success.
 */
bool usage_ifElse();

#ifdef __cplusplus
}
#endif

#endif


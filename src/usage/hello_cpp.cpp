/**
 * @file hello_cpp.cpp
 * @brief Sample code for demonstrate the usage of C++ programming language.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */

#include <iostream>
#include "usage_cplus.h"
#include "config.h"

namespace {
int mLocalVariable = 1;
}

int main(int argc, char *argv[])
{
    std::string appName = argv[0];

    std::cout << "Hello World C++ demo program (Version: " << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << "." << APP_VERSION_PATCH << ")\n";
    std::cout << "Test variables: " << mLocalVariable << ", " << usage::mSomeHelloVariable << ", " << usage::SOME_HELLO_VARIABLE << "\n";
    std::cout << "App name: " << appName << "\n";
    usage::useMain();

    return EXIT_SUCCESS;
}
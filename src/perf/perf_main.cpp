#include <iostream>

void delay()
{
    int j;

    for (int i = 0; i < 1000000; i++)
    {
        j = i;
    }

    std::cout << j;
}

void function_1()
{
    for (int i = 0; i < 20; i++)
    {
        delay();
    }
}

void function_2()
{
    for (int i = 0; i < 80; i++)
    {
        delay();
    }
}

int main(void)
{
    std::cout << "Begin" << std::endl;
    function_1();
    function_2();
    std::cout << "End" << std::endl;
}
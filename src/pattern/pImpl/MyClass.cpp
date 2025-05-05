#include "MyClass.h"
#include <iostream>

struct MyClass::Impl
{
    int data;

    void privateMethod() const
    {
        std::cout << "Call pImpl private method" << std::endl;
    }
};

MyClass::MyClass() : pImpl(std::make_unique<Impl>())
{
    pImpl->data = 42;
}

MyClass::~MyClass() = default;

void MyClass::doSomething() const
{
    std::cout << "Data:" <<pImpl->data << std::endl;
    pImpl->privateMethod();
}
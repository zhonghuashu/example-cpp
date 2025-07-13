/**
 * @file MyClass.h
 * @brief pImpl pattern:　Pointer to IMPLementation
 * @author Shu, Zhong Hua
 * @date 2025-05-05
 */

 #include <memory>

 class MyClass
 {
public:
    MyClass();
    ~MyClass();
    void doSomething() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
 };


/**
 * @file usage_cplus.h
 * @brief Common usage of C++ programming language.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#ifndef USAGE_CPLUS_H
#define USAGE_CPLUS_H

#ifdef __cplusplus
 // Function inside namespace for C++ compiler option.
namespace usage {

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
/**
 * Global int variable for demo purpose only.
 */
extern int mSomeHelloVariable;

/**
 * Global const int variable for demo purpose only, initialize in header.
 */
const int SOME_HELLO_VARIABLE = 2;
}


namespace usage {

/**
 * Test C++ language usage function.
 * @return true if success.
 */
bool useMain();

/**
 * Example usage for basic C++.
 */
void useBasic();

/**
 * Example usage for array variable.
 */
void useArray();

/**
 * Example usage for string variable.
 */
void useString();

/**
 * Example usage for pointer type.
 */
void usePointer();

/**
 * Example usage for bitwise operations.
 */
void useBitWise();

/**
 * Example usage for sizeof operations.
 */
void useSizeof();

/**
 * Example usage for named cast operations.
 */
void useNamedCast();

/**
 * Example usage for try / exception.
 */
void useTryException();

/**
 * Example usage for passing arguments as value or reference.
 * @param i1 Reference argument.
 * @param i2 Reference argument.
 */
void useArguPassing(const int &i1, const int *const i2);

/**
 * Example usage for function pointer.
 */
void useFunctionPointer();

/**
 * Example usage for famous class object.
 */
void useClass();

/**
 * Example usage for file I/O operations.
 */
void useFileIo();

/**
 * Example usage for common vector container.
 */
void useVector();

/**
 * Example usage for list container.
 */
void useList();

/**
 * Example usage for adaptor container.
 */
void useAdaptor();

/**
 * Example usage for map container.
 */
void useMap();

/**
 * Example usage for set container.
 */
void useSet();

/**
 * Generic algorithm operates on standard container.
 * The algorithms is running on iterator and will not directly insert or delete elements in container.
 */
void useGenericAlgo();

/**
 * Example usage for if / else statement.
 * @return true if success.
 */
bool useIfElse();

/**
 * Example usage for C++ template.
 */
void useTemplate();

/**
 * Example usage for new features of C++ 2011 standard.
 */
void useC11();

/**
 * Example usage for new tuple type.
 * `Tuple` is similar like `pair` type, but may contains arbitrary objects.
 */
void useTuple();

/**
 * Example usage for binary bits operations with fixed bits number.
 */
void useBitset();

/**
 * Example usage for regular expression.
 */
void useRegex();

/**
 * Example usage for random number generation.
 */
void useRandom();

/**
 * Example usage for union type.
 */
void useUnion();

/**
 * Example usage for assert macro for debug purpose.
 */
void useDebug();

/**
 * Example usage for double operation.
 */
void useDouble();

}



#endif

// Function outside namespace for C compiler option.
#ifdef __cplusplus
extern "C" {
#endif

    /**
    * Example usage for external linkage.
    */
    void usage_cplusExternLinkage();

#ifdef __cplusplus
}
#endif

#endif
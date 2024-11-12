/**
 * @file usage_cplus.cpp
 * @brief Example usage for C++ programming languages.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <memory>
#include <functional>
#include <bitset>
#include <regex>
#include <random>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include "config.h"

#ifdef USE_STRING_FORMAT
#include <fmt/ranges.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#endif

#include "usage_cplus.h"
#include "SalesItem.h"
#include "Quote.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::cerr;
using std::string;

namespace usage {
int mSomeHelloVariable = 1;
}

namespace {
static void displayNumber(const int i)
{
    cout << i << ", ";
}

static bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

template <typename T>
static int compare(const T &v1, const T &v2)
{
    if (v1 < v2) { return -1; }
    if (v2 < v1) { return 1; }

    return 0;
}

void reset(int &i)
{
    i = 0;
}

}

extern "C" void usage_cplusExternLinkage()
{
    cout << "\n#### Usage: extern C linkage\n";
}

bool usage::useMain()
{
    const int i = 0;

    ::usage_cplusExternLinkage();
    usage::useBasic();
    usage::useArray();
    usage::useString();
    usage::usePointer();
    usage::useBitWise();
    usage::useSizeof();
    usage::useNamedCast();
    usage::useTryException();
    usage::useArguPassing(i, &i);
    usage::useFunctionPointer();
    usage::useClass();
    usage::useFileIo();
    usage::useVector();
    usage::useList();
    usage::useAdaptor();
    usage::useMap();
    usage::useSet();
    usage::useGenericAlgo();
    usage::useIfElse();
    usage::useTemplate();
    usage::useC11();
    usage::useTuple();
    usage::useBitset();
    usage::useRegex();
    usage::useRandom();
    usage::useUnion();
    usage::useDebug();
    usage::useDouble();

    return true;
}

void usage::useBasic()
{
    cout << "\n#### Usage: Basic C++\n";
    int ival = 1024;
    const int &refVal = ival;
    cout << "Reference: " << ival << ", " << refVal << "\n";
    ++ival;
    cout << "Reference: " << ival << ", " << refVal << "\n";
    const int *pval = nullptr;  // Same as NULL or 0.
    pval = &ival;
    cout << "Pointer: " << *pval << "\n";
    reset(ival);
    cout << "Reference parameter: " << ival << "\n";
}

void usage::useArray()
{
    cout << "\n#### Usage: array\n";

    const int MAX_LEN = 5;
    const int arr[MAX_LEN] = { 0, 1, 2, 3, 4 };

    // Change to to a range for-loop or an "std::for_each".sonarlint(cpp:S5566)
    cout << "Range for: ";
    for (const int i : arr)
    {
        cout << i << " ";
    }
    cout << "\n";
    cout << "Begin / end: ";
    const int *pbeg = std::begin(arr);
    while (pbeg != std::end(arr))
    {
        cout << *pbeg << " ";
        ++pbeg;
    }

    // Array: Fast random access, can't insert / delete element.
    // C++11: Array container with type and size
    const std::array<int, 10> arr2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (const int val : arr2)
    {
        cout << val << ", ";
    }
    cout << "\n";
}

void usage::useString()
{
    cout << "\n#### Usage: string\n";

    string hello1 = "Hello World";
    string hello2("Hello World");
    const int EMPTY_SPACE_POS = 5;

    // String operations.
    cout << "print: " << hello1 << "\n";
    cout << "print: " << hello2 << "\n";

    cout << "substr: " << hello1.substr(0, EMPTY_SPACE_POS) << ", " << hello1.substr(0, EMPTY_SPACE_POS) << "\n";
    cout << "append: " << hello1.append("!") << ", " << hello2.append("!") << "\n";
    cout << "find: " << (int)hello1.find("world") << ", " << hello1.find_first_of("world") << "\n";
    cout << "compare: " << ((hello1 == hello2) ? "equal" : "not equal") << ", " << hello1.compare(hello2) << "\n";

    // String iterator.
    string line = "first,second,third";
    const string::iterator comma = find(line.begin(), line.end(), ',');
    cout << "iterator: " << string(line.begin(), comma) << "\n" << flush;

    // String <> number conversion (C++11).
    const int ival = 40;
    const string sval = std::to_string(ival);
    const float fval = std::stof(sval);
    cout << "conversion: " << ival << ", " << sval << ", " << fval << "\n";
    string s2 = "hello";
    s2 += std::to_string(::getpid());
    cout << "s2: " << s2 << "\n";

    // C-Style string.
    const char *const ca = "a string";
    if (ca != nullptr)
    {
        cout << "char: " << ca << "\n";
    }

    const char cabuff[] = {'C', '+', '+', '\0'};
    const string castr = cabuff;
    std::ostringstream os;

    os << cabuff;
    cout << "char buffer: " << cabuff << ", string: " << castr << "os: " << os.str() << "\n";
    cout << "char buffer len: " << ::strnlen(cabuff, sizeof(cabuff)) << ", string len: " << castr.size() << "\n";


    // String format using snprintf.
    const char fmt[] = "test string: %s. test number: %d";
    const string strVal = "string";
    const int intVal = 3;
    char targetString[1024];
    const int realLen = ::snprintf(targetString, sizeof(targetString), fmt, strVal.c_str(), intVal);
    cout << "string format: " << realLen << ", " << targetString << "\n";

#ifdef USE_STRING_FORMAT
    const int TEST_NUM = 65;
    // String format using C++20 format.
    // Output: test string: hello, test number: 1, elog_test.cpp, 78
    std::cout << fmt::format("test string: {0}, test number: {1}", "hello", 1) << ", " << __FILE__ << ", " << __LINE__ << "\n";
    // Output: test string: hello, test number: 1, elog_test.cpp, 78
    std::cout << fmt::format("int: {0:d}; hex: {0:#x};  oct: {0:#o};  bin: {0:#b}; char: {0:c}", TEST_NUM) << "\n";
    // Output: float: 65.10;
    std::cout << fmt::format("float: {0:.2f};", 65.1) << "\n";
    // Output: [1, 2, 3]
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);
#endif
}

void usage::usePointer()
{
    cout << "\n#### Usage: pointer\n";
    // New / delete or malloc / free shall be replaced with smart pointer sonarlint(cpp:S5025).
    const int *pInt = new int(1024);
    const string *pStr = new string("hello pointer");
    cout << "pointer: " << "*int = " << *pInt << "\n";
    cout << "pointer: " << "*string = " << *pStr << "\n";
    delete pInt;
    delete pStr;
    pInt = nullptr; // To avoid dangling pointer.
    pStr = nullptr; // To avoid dangling pointer.

    // unique_ptr allow only one pointer point to same object, does't support copy / assignment operation.
    const std::unique_ptr<int> pi(new int(1024));
    const std::unique_ptr<string> ps(new string("hello pointer"));
    const int *const p1 = pi.get();     // Don't delete get() pointer.
    const string *const p2 = ps.get();  // Don't delete get() pointer.
    // Same as: const std::unique_ptr<char[]> up1(new char[10]);
    const std::unique_ptr<char[]> up1 = std::make_unique<char[]>(10);
    ::snprintf(up1.get(), 10, "%s", "hello");

    cout << "unique_ptr: " << "*pi = " << *pi << ", " << *p1 << "\n";
    cout << "unique_ptr: " << "*ps = " << *ps << ", " << *p2 << "\n";
    cout << "unique_ptr: " << "*p3 = " << up1.get() << "\n";

    // shared_ptr allow more pointers point to same object (e.g., p3 / p4 pointer to same object).
    const std::shared_ptr<int> p3 = std::make_shared<int>(42);
    const std::shared_ptr<int> p4 = p3;
    const std::shared_ptr<string> p5 = std::make_shared<string>();
    *p5 = "hello2";
    cout << "shared_ptr: " << "*p3 = " << *p3 << ", " << *p4 << ", *p5 = " << *p5 << "\n";

    // Dynamic array using smart pointer.
    std::unique_ptr<int[]> up(new int[10]);
    up.release();   // Use delete [] up
    std::shared_ptr<int> sp(new int[10], [](int *const p) { delete[] p; });
    sp.reset();

    // Function pointer.
    const int ival = 10;
    typedef void (*func)(const int);
    const func pf = displayNumber;
    pf(ival);
}

void usage::useBitWise()
{
    cout << "\n#### Usage: bitwise operation\n";

    // unsigned long is guaranteed have 32 bits long.
    unsigned long quiz1 = 0;
    bool status;
    const int BIT_POS = 27;

    // Set bit position 27.
    quiz1 |= 1UL << BIT_POS;

    // Check if bit position 27 is set.
    status = quiz1 & (1UL << BIT_POS);

    cout << "Status: " << status << std::flush;
}

void usage::useSizeof()
{
    cout << "\n#### Usage: size of\n";

    const int x[10] = { 0 };
    const int *const p = x;

    cout << "sizeof int " << sizeof(int) << "\n";
    cout << "sizeof int pointer: " << sizeof(p) << "\n";
    cout << "sizeof int x[10]: " << sizeof(x) / sizeof(*x) << "\n";
}

void usage::useNamedCast()
{
    cout << "\n#### Usage: named cast\n";

    int p = 10;
    void *const p1 = &p;
    const long *const p2 = static_cast<long *>(p1);
    // Replace "reinterpret_cast" with a safer cast.sonarlint(cpp:S3630)
    // const char *const pc = reinterpret_cast<char *>(p1);

    cout << "Size of long pointer type after named cast: " << sizeof(*p2) << "\n";
}

void usage::useTryException()
{
    cout << "\n#### Usage: try / exception\n";

    try
    {
        throw std::overflow_error("Error thrown in try / exception.");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}

void usage::useArguPassing(const int &i1, const int *const i2)
{
    cout << "\n#### Usage: argument passing\n";

    cout << "&i1: " << &i1 << "\n";
    cout << "*i2: " << i2 << "\n";
}

void usage::useFunctionPointer()
{
    cout << "\n#### Usage: function pointer\n";

    typedef void (*ArgumentHandler)(const int &, const int *);
    const int i = 0;

    const ArgumentHandler ah = usage::useArguPassing;
    ah(i, &i);
    cout << "\n";
}

void usage::useClass()
{
    cout << "\n#### Usage: class\n";
    // Use simple stuct object without operations.
    struct SalesData
    {
        std::string bookNo;
        unsigned int unitsSold = 0;
        double revenue = 0.0;
    };
    SalesData trans;
    trans.bookNo = "C++ Primer";
    cout << "Struct SalesData: [" << trans.bookNo << ", " << trans.unitsSold << ", " << trans.revenue << ", " << sizeof(SalesData) << "]\n";


    // Use struct initialization list.
    SalesData trans2 = { "C++ Primer 2", 0, 0.0 };
    cout << "Struct SalesData2: [" << trans2.bookNo << ", " << trans2.unitsSold << ", " << trans2.revenue << "]\n";

    SalesData trans3 = { .bookNo = "C++ Primer 3", .unitsSold = 0, .revenue = 0};
    cout << "Struct SalesData2: [" << trans3.bookNo << ", " << trans3.unitsSold << ", " << trans3.revenue << "]\n";

    // Use class object.
    SalesItem item("book 1", 1, 20);
    cout << "Average price: " << item.avgPrice() << ", isbn: " << item.isbn() << "\n";
    cout << "Static member: " << SalesItem::SOME_STATIC_CONST_MEMBER_1 << ", " << SalesItem::SOME_STATIC_CONST_MEMBER_2 << ", " << SalesItem::someStaticMember3 << "\n";
    usage::print(cout, item);
    cout << "\n";
    item.debug(cout);

    // Use Object Oriented Programming (OOP).
    static const int SOLD_UNIT = 10;
    const Quote base("0-201-82470-1", 50);
    usage::print_total(cout, base, SOLD_UNIT);    // Calls Quote::net_price.

    const Bulk_quote derived("0-201-82470-1", 50, 5, .19);
    usage::print_total(cout, derived, SOLD_UNIT); // Calls Bulk_quote::net_price.

    const Quote *const baseP = &derived;
    // Calls the version from the base class regardless of the dynamic type of baseP.
    const double undiscounted = baseP->Quote::net_price(42);
    cout << "Bulk quote: " << undiscounted << "\n";
}

void usage::useFileIo()
{
    cout << "\n#### Usage: file IO\n";

    const string infile = "CMakeLists.txt";
    const string outfile = infile + ".copy";

    // Inexplicit file mode: std::ofstream::in
    std::ifstream in(infile);
    // Inexplicit file mode: std::ofstream::out | std::ostream::trunc
    std::ofstream out(outfile);

    cout << "Read file: " << infile << "\n";
    cout << "Write file: " << outfile << "\n";

    if (!in) { cerr << "Couldn't open input file: " << infile; return; }
    if (!out) { cerr << "Couldn't open output file: " << outfile; return; }

    string line;

    while (getline(in, line))
    {
        static int lineNum = 0;
        const int LINE_NUM = 5;
        if (lineNum >= LINE_NUM)
        {
            // Refactor the code to remove this break statement.sonarlint(cpp:S1227)
            break;
        }
        ++lineNum;
        out << "Line" << lineNum << ": " << line << "\n";
    }

    in.close();
    out.close();
}

void usage::useVector()
{
    cout << "\n#### Usage: vector\n";

    // Vector: fast random read and insert at end.
    std::vector<int> vect;
    const int MAX = 10;

    cout << "ivec: size: " << vect.size()
        << ", capacity: " << vect.capacity() << "\n";

    for (int i = 0; i < MAX; ++i)
    {
        vect.push_back(i);
    }
    cout << "ivec: size: " << vect.size()
        << ", capacity: " << vect.capacity() << "\n";

    // Loop with subscript.
    cout << "Subscript: ";
    for (std::vector<int>::size_type i = 0; i < MAX; ++i)
    {
        cout << vect[i] << ", ";
    }
    cout << vect.at(vect.size() - 1);
    cout << "\n";

    // Loop with iterator.
    std::vector<int>::const_iterator begin = vect.cbegin();
    cout << "Iterator: ";
    while (begin != vect.cend())
    {
        cout << *begin << ", ";
        ++begin;
    }
    cout << "\n";

    // Loop with for_each.
    cout << "For-each: ";
    for_each(vect.begin(), vect.end(), ::displayNumber);
    cout << "\n";

    // Loop with for (:)
    cout << "Range for: ";
    for (const int elt : vect)
    {
        cout << elt << ", ";
    }
    cout << "\n";
}

void usage::useList()
{
    cout << "\n#### Usage: list\n";
    // C++11: Container list initializer.
    const char *const words[4] = { "stately", "plump", "buck", "mulligan" };
    const size_t wordSize = sizeof(words) / sizeof(char *);

    // List: Sequence access both forward / backward, fast insert random.
    // Use entire array to initialize.
    std::list<string> wordList(words, words + wordSize);
    wordList.push_front("first");
    wordList.insert(++wordList.begin(), "two-2");
    cout << "Remove last element: " << wordList.back() << "\n";
    wordList.pop_back();
    wordList.push_back("last");

    cout << "List: ";
    for (const string &word : wordList)
    {
        cout << word << ", ";
    }
    cout << "\n";

    // Forward_list: Sequence access forward, fast insert random.
    std::forward_list<string> wordList2 = { "one", "two", "three" };
    wordList2.push_front("first");
    wordList2.insert_after(++wordList2.begin(), "two-2");
    cout << "Forward_list: ";
    for (const string &word : wordList2)
    {
        cout << word << ", ";
    }
    cout << "\n";

    // Begin / end access queue, fast random access, fast insert at begin and end.
    std::deque<string> wordList3 = { "four", "five", "six" };
    wordList3.push_front("first");
    cout << "Deque: " << wordList3.at(0) << ", " << wordList3.at(wordList3.size() - 1) << "\n";
}

void usage::useAdaptor()
{
    cout << "\n#### Usage: container adaptor\n";
    std::stack<int> intStack;   // based on deque
    std::queue<int> intQueue;   // based on deque
    const int MAX = 10;

    for (int i = 0; i < MAX; ++i)
    {
        intStack.push(i);
        intQueue.push(i);
    }

    cout << "stack<int>: ";
    while (!intStack.empty())
    {
        cout << intStack.top() << ", ";
        intStack.pop();
    }
    cout << "\n";

    cout << "queue<int>: ";
    while (!intQueue.empty())
    {
        cout << intQueue.front() << ", ";
        intQueue.pop();
    }
    cout << "\n";
}

void usage::useMap()
{
    cout << "\n#### Usage: map\n";

    // Associative container stores with key-value pair (Associative array).
    std::map<string, int> wordCount;

    wordCount["red"] = 1;
    ++wordCount["green"];
    ++wordCount["white"];
    ++wordCount["black"];

    wordCount.insert(std::make_pair("orange", 1));
    wordCount.insert({ "blue", 1 });
    const std::pair<std::map<std::string, int>::iterator, bool> ret = wordCount.insert({ "blue", 1 });
    if (!ret.second)
    {
        cout << "Map insert: element already in map.\n";
    }

    std::map<string, int>::const_iterator map_it = wordCount.begin();
    while (map_it != wordCount.end())
    {
        // Word ordered as dictionary sequence compared to unordered_map.
        cout << "Map iterator: '" << map_it->first << "' occurs " << map_it->second << " times" << "\n";
        ++map_it;
    }

    const std::map<string, int>::iterator it = wordCount.find("green");
    if (it != wordCount.end())
    {
        cout << "Map find: '" << it->first << "' occurs " << it->second << "\n";
    }

    cout << "Map at: " << wordCount.at("green") << "\n";

    try
    {
        cout << "Map at non-exist: " << wordCount.at("non-exist") << "\n";
    }
    catch (const std::out_of_range &e)
    {
        cout << "\n";
        cout << "Map error: out of range" << "\n";
        std::cerr << e.what() << "\n";
    }

}

void usage::useSet()
{
    cout << "\n#### Usage: set\n";

    std::vector<int> ivec;
    int const MAX = 10;

    for (std::vector<int>::size_type i = 0; i != MAX; ++i)
    {
        ivec.push_back((int)i);
        ivec.push_back((int)i);
    }

    // Associative container stores with key only.
    const std::set<int> iset(ivec.begin(), ivec.end());
    cout << "Vector: " << ivec.size() << "\n";
    cout << "Set: " << iset.size() << "\n";
}

void usage::useGenericAlgo()
{
    cout << "\n#### Usage: generic algorithms\n";
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ia[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    static const int val1 = 50;
    static const int val2 = 2;
    cout << "Find in vector: the value " << val1 << (std::find(ivec.begin(), ivec.end(), val1) == ivec.end() ? " is not present\n" : " is present\n");
    cout << "Find in vector: the value " << val2 << (std::find(ivec.begin(), ivec.end(), val2) == ivec.end() ? " is not present\n" : " is present\n");
    cout << "Find in array: the value " << val1 << (std::find(std::begin(ia), std::end(ia), val1) == std::end(ia) ? " is not present\n" : " is present\n");
    cout << "Find in array: the value " << val1 << (std::find(std::begin(ia), std::end(ia), val2) == std::end(ia) ? " is not present\n" : " is present\n");

    // Append 10 elements at the end of empty vector (push_back).
    ivec.clear();
    static const int FILL_NUM = 10;
    fill_n(back_inserter(ivec), FILL_NUM, 1);
    cout << "Fill in vector: ";
    for_each(ivec.begin(), ivec.end(), ::displayNumber);
    cout << "\n";

    // Sort elements in container.
    std::vector<string> svec = { "one", "two", "three", "four" };
    std::sort(svec.begin(), svec.end());
    cout << "Sort in vector: ";
    for_each(svec.begin(), svec.end(), [](const string &s) { cout << s << ", "; });
    cout << "\n";

    // Sort elements with third parameter "Predicate" for return bool condition for sorts.
    std::sort(svec.begin(), svec.end(), ::isShorter);
    cout << "Sort in vector: ";
    for_each(svec.begin(), svec.end(), [](const string &s) { cout << s << ", "; });
    cout << "\n";

    // Lambda expression for predicate: [capture list for local variable access in function body](parameter list) -> return type { function body }
    std::vector<string> words = { "stately", "plump", "buck", "mulligan" };
    cout << "Lambda expression: ";
    std::stable_sort(words.begin(), words.end(),
        [](const string &a, const string &b)
        { return a.size() < b.size(); });
    for_each(words.begin(), words.end(),
        [](const string &s)
        { cout << s << " "; });
    cout << "\n";
}

bool usage::useIfElse()
{
    cout << "\n#### Usage: if else\n";

    const bool value = true;

    if (!value)
    {
        cout << "if\n";
        return false;
    }

    const int grade = 50;
    const int GRADE_THRESHOLD = 60;
    cout << "Condition operator: " << ((grade < GRADE_THRESHOLD) ? "fail" : "pass") << "\n";

    return true;
}

void usage::useTemplate()
{
    cout << "\n#### Usage: Template\n";
    const int v1 = 2;
    const int v2 = 1;
    const std::vector<int> vec1 = { 1, 2, 3 };
    const std::vector<int> vec2 = { 1, 2, 2 };
    const string s1 = "hi";
    const string s2 = "hj";

    cout << "Compare int: " << ::compare(v1, v2) << "\n";
    cout << "Compare vector<int>: " << ::compare(vec1, vec2) << "\n";
    cout << "Comare string: " << ::compare(s1, s2) << "\n";
}

void usage::useC11()
{
    cout << "\n#### Usage: C++ 11 features\n";

    // Long integer.
    const long long var = 0;
    cout << "Long long: " << var << "\n";

    // List initialization.
    const int unitsSold = { 0 };
    cout << "List initialization: " << unitsSold << "\n";

    // null pointer.
    const int *const p1 = nullptr;
    cout << "Null pointer: " << p1 << "\n";

    // Auto type must have initial value.
    const auto pi = 3.14;
    cout << "Auto: " << pi << "\n";

    // Declare type.
    const int ci = 0;
    decltype (ci) x = 0;
    cout << "Decltype: int x = " << x << "\n";

    // Range for.
    const string str("some string");
    cout << "Range for: ";
    for (const char c : str)
    {
        cout << c << " ";
    }
    cout << "\n";

    // Vector initialize.
    const std::vector<string> articles = { "a", "an", "the" };
    cout << "Vector initialize: " << articles.size() << "\n";

    // Array begin / end
    int ia[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const int *beg = std::begin(ia);
    cout << "Array begin / end: ";
    while (beg != std::end(ia))
    {
        cout << *beg << " ";
        ++beg;
    }
    cout << "\n";

    // Const express function, could assign to any function, e.g., = size().
    constexpr float scale = 1.0f;
    cout << "Constexpr: scale = " << scale << "\n";

    // Function.
    auto mod = [](const int i, const int j) { return i % j; };
    std::map<string, std::function<int(int, int)>> binops =
    {
        {"%", mod}
    };
    const int NUM_1 = 5;
    const int NUM_2 = 2;
    cout << "Function: binops[+] = " << binops["%"](NUM_1, NUM_2) << "\n";

    // Scoped enum class.
    enum class Color { Red, Yellow, Green };
    cout << "Enum class: " << (int)Color::Red << ", " << (int)Color::Yellow << ", " << (int)Color::Green << "\n";
}

void usage::useTuple()
{
    cout << "\n#### Usage: tuple\n";
    std::tuple<size_t, size_t, size_t> threeD;
    std::tuple<string, std::vector<double>, int, std::list<int>> someVal("constrants", { 3.14, 2.718f }, 42, { 0, 1, 2, 3, 4, 5 });

    cout << "threeD: " << std::get<0>(threeD) << ", " << std::get<1>(threeD) << ", " << std::get<1>(threeD) << "\n";
    cout << "someVal: " << std::get<0>(someVal) << ", " << std::get<1>(someVal)[0] << "\n";
}

void usage::useBitset()
{
    cout << "\n#### Usage: bitset\n";
    std::bitset<32> bitvec(1U);
    cout << "Bitset: " << bitvec.any() << ", " << bitvec.count() << "\n";
    bitvec.set(0, 0);
    cout << "Bitset: " << bitvec.any() << ", " << bitvec.count() << "\n";

    // Version using bitset library.
    bitvec.set(0, 1);
    cout << "Bitset: 0000 0001 = " << bitvec.to_ulong() << "\n";
    bitvec.reset(0);
    bitvec.set(7, 1);
    cout << "Bitset: 1000 0000 = " << bitvec.to_ulong() << "\n";

    // Equivalent version using bitwise operations.
    unsigned long stVal = 0;
    stVal |= 1UL << 0;
    cout << "Bitset: 0000 0001 = " << stVal << "\n";
    stVal |= 1UL << 0;      // set bit0 = 1
    stVal &= ~(1UL << 0);   // reset 0
    stVal |= 1UL << 7;      // set bit7 = 1
    cout << "Bitset: 1000 0000 = " << stVal << "\n";
}

void usage::useRegex()
{
    cout << "\n#### Usage: Regular expression\n";

    // Find the characters ei that follow a character other than c.
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

    const std::regex r(pattern);
    std::smatch results;

    const string testStr = "receipt freind theif receive";

    if (regex_search(testStr, results, r))
    {
        cout << results.str() << "\n";
    }
}

void usage::useRandom()
{
    cout << "\n#### Usage: Random\n";
    // Static for new random every function call.
    static std::default_random_engine e((unsigned long)::time(nullptr));
    static std::uniform_real_distribution<double> u(0, 1);
    const int MAX = 10;

    cout << "Random: seed(" << ::time(nullptr) << "): ";
    for (int i = 0; i < MAX; ++i)
    {
        cout << u(e) << " ";
    }
    cout << "\n";
}

void usage::useUnion()
{
    cout << "\n#### Usage: Union\n";
    union Token
    {
        char cval;
        int ival;
        float fval;
    };

    const Token token = { 'a' };
    cout << token.cval << ", " << token.ival << ", " << token.fval << "\n";
}

void usage::useDebug()
{
    cout << "\n#### Usage: NDEBUG\n";
    // Remove debug code using -D NDEBUG compiler option.
    const string word = "foo";
    const string::size_type THRESHOLD = 5;

    if (word.size() < THRESHOLD)
    {
        cerr << "Error: " << __FILE__
            << " : in function " << __FUNCTION__ << "()"       // or __func__
            << " at line " << __LINE__ << "\n"
            << "       Compiled on " << __DATE__
            << " at " << __TIME__ << "\n"
            << "       Word read was \"" << word
            << "\":  Length too short" << "\n";
    }

    cout << "line: " << __LINE__ << ", file: " << __FILENAME__ << ", function: " << __FUNCTION__ << "\n";

    // Comment out because aborting unit test.
    // assert(word.size() > THRESHOLD);
    cout << "\n";
}

void usage::useDouble()
{
    cout << "\n#### Usage: double\n";
    double dval = 40.6;

    if (dval > 50)
    {
        cout << "40.6 >= 50: true" << "\n";
    }
    else
    {
        cout << "40.6 >= 50: false" << "\n";
    }
    cout << "\n";
}
/**
 * @file SalesItem.h
 * @brief Sales item class definition.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <string>
#include <iostream>
#include <vector>

namespace usage {

/**
 * Debug for IO, HW and other errors.
 */
class Debug
{
public:
    /**
     * Default constructor.
     */
    Debug() = default;

    /**
     * Constructor function to initialize with boolean value.
     * @param b All errors source set to true or false.
     */
    explicit Debug(const bool b) : m_hw(b), m_io(b), m_other(b) {}

    /**
     * Check if any error occurred.
     * @return true if any error occurred.
     */
    bool any() { return m_hw || m_io || m_other; }

    /**
     * Set IO error to true or false.
     * @param b true if error is set.
     */
    void setIo(const bool b) { m_io = b; }

    /**
     * Set HW error to true or false.
     * @param b true if error is set.
     */
    void setHw(const bool b) { m_hw = b; }

    /**
     * Set Other error to true or false.
     * @param b true if error is set.
     */
    void setOther(const bool b) { m_other = b; }
private:
    // Hardware error
    bool m_hw = false;
    // IO error
    bool m_io = false;
    // Other error
    bool m_other = false;
};

/**
 * Sold item at an un-discounted price derived classes will define various discount strategies.
 */
class SalesItem
{
public:
    // Friend class for nonmember SalesItem interface functions.
    friend SalesItem add(const SalesItem &, const SalesItem &);
    friend std::ostream &print(std::ostream &, const SalesItem &);
    friend std::istream &read(std::istream &, SalesItem &);

public:
    /**
     * Default constructors (C++11) use class inside initialize.
     * Same as: SalesItem() { }
     */
    SalesItem() = default;

    /**
     * Delegating constructor.
     * @param s Book number.
     */
    explicit SalesItem(const std::string &s) : SalesItem(s, 0, 0) {}

    /**
     * Suppress inexplicit converting constructor with explicit defined in function prototyping.
     * @param s Book number.
     * @param n Sold units.
     * @param p Sold revenue.
     */
    explicit SalesItem(const std::string &s, const unsigned n, const double p) :
        m_bookNo(s),
        m_unitsSold(n),
        m_revenue(p *n) {}

    /**
     * Suppress inexplicit converting constructor.
     */
    explicit SalesItem(std::istream &);

    /**
     * Explicitly generate default copy constructor.
     * @param orig Original copied object.
     */
    SalesItem(const SalesItem &orig) = default;

    /**
     * Explicitly generate default assignment operator.
     * @return Assigned object.
     */
    SalesItem &operator=(const SalesItem &) = default;

    /**
     * Explicitly generate default destructor.
     */
    virtual ~SalesItem() = default;

    /**
     * Implicitly inline operations.
     * @return book ISBN number.
     */
    std::string isbn() const { return m_bookNo; }

    /**
     * Combine sales item into one.
     * @return Combined sales item.
     */
    SalesItem &combine(const SalesItem &);

    /**
     * Average price for total price and sold units.
     * @return Averaged price.
     */
    double avgPrice() const;

    /**
     * Debug class member for demonstrate purpose only.
     * @param os Standard output stream.
     */
    void debug(std::ostream &os);

public:
    /**
     * Constexpr needed for in-class initialization of static data member (int).
     */
    static constexpr int SOME_STATIC_CONST_MEMBER_1 = 1;

    /**
     * Constexpr needed for in-class initialization of static data member (float).
     */
    static constexpr float SOME_STATIC_CONST_MEMBER_2 = 1.0f;

    /**
     * Initialize in cpp class.
     */
    static double someStaticMember3;

private:
    std::string m_bookNo;
    // C++11: Initialize inside class.
    unsigned m_unitsSold = 0;
    double m_revenue = 0;
    Debug m_debug;
};

/**
* Add two sales item.
* @return Added sales item.
*/
SalesItem add(const SalesItem &, const SalesItem &);

/**
 * Print out sales item to output stream.
* @return Output stream.
*/
std::ostream &print(std::ostream &, const SalesItem &);

/**
* Read sales item from input stream.
* @return Input stream.
*/
std::istream &read(std::istream &, SalesItem &);

/**
 * Compare two ISBN number which is used in future chapters.
 * @param lhs Left sales item.
 * @param rhs Right sales item.
 * @return true of left less than right.
 */
inline bool compareIsbn(const SalesItem &lhs, const SalesItem &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

}
#endif
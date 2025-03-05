/**
 * @file SalesItem.cpp
 * @brief Implementation class of sales item.
 * @author Shu, Zhong Hua
 * @date 2022-08-14
 */
#include <iostream>
#include "SalesItem.h"

using std::istream;
using std::ostream;

namespace usage {

double SalesItem::someStaticMember3 = 3.0;

std::array<std::string, 10> SalesItem::m_testArray;

SalesItem::SalesItem(std::istream &is)
{
    m_testArray.fill("");
    read(is, *this);
}

double SalesItem::avgPrice() const
{
    if (m_unitsSold > 0)
    {
        return m_revenue / m_unitsSold;
    }
    else
    {
        return 0;
    }
}

void SalesItem::debug(ostream &os)
{
    os << "debug: " << m_debug.any() << "\n";
    m_debug.setHw(true);
     os << "debug: " << m_debug.any() << "\n";
}

SalesItem &SalesItem::combine(const SalesItem &rhs)
{
    m_unitsSold += rhs.m_unitsSold;
    m_revenue += rhs.m_revenue;
    return *this;
}

SalesItem add(const SalesItem &lhs, const SalesItem &rhs)
{
    SalesItem sum = lhs;
    sum.combine(rhs);
    return sum;
}

istream &read(istream &is, SalesItem &item)
{
    double price = 0;
    is >> item.m_bookNo >> item.m_unitsSold >> price;
    item.m_revenue = price * item.m_unitsSold;
    return is;
}

ostream &print(ostream &os, const SalesItem &item)
{
    os << item.isbn() << " " << item.m_unitsSold << " "
        << item.m_revenue << " " << item.avgPrice();
    return os;
}

}
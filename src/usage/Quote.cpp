/**
 * @file Quote.cpp
 * @brief Implementation of Quote class.
 * @author Shu, Zhong Hua
 * @date 2022-08-22
 */
#include <algorithm>
#include <cstddef>
#include <iostream>
#include "Quote.h"

using std::min;
using std::size_t;
using std::ostream;
using std::flush;
using std::cout;

namespace usage {
double Bulk_quote::net_price(const size_t cnt) const
{
    if (cnt >= quantity)
    {
        return (double)cnt * (1 - discount) * price;
    }
    else
    {
        return (double)cnt * price;
    }
}
}

double usage::print_total(ostream &os, const Quote &item, const size_t n)
{
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    const double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
        << " # sold: " << n << " total due: " << ret << "\n" << flush;

    return ret;
}

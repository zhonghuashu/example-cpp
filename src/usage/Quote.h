/**
 * @file Quote.h
 * @brief Quote class.
 * @author Shu, Zhong Hua
 * @date 2022-08-21
 */

#ifndef QUOTE_H
#define QUOTE_H

#include <memory>
#include <iostream>
#include <string>
#include <cstddef>

namespace usage {
/**
 * Item sold at an un-discounted price derived classes will define various discount strategies.
 */
class Quote {
    // friend std::istream &operator>>(std::istream &, Quote &);
    // friend std::ostream &operator<<(std::ostream &, const Quote &);
public:
    /**
     * Default constructor.
     */
    Quote() = default;

    /**
     * Class constructor.
     * @param book Book name.
     * @param sales_price Sales price.
     */
    Quote(const std::string &book, const double sales_price) :
        price(sales_price), bookNo(book) { }

    /**
     * Virtual destructor needed if a base pointer pointing to a derived object is deleted
     */
    virtual ~Quote() = default; // dynamic binding for the destructor

    /**
     * Return book ISBN number.
     * @return ISBN number.
     */
    std::string isbn() const { return bookNo; }

    /**
     * Returns the total sales price for the specified number of items
     * derived classes will override and apply different discount algorithms
     * @param n Unit number.
     * @return total sales price.
     */
    virtual double net_price(const std::size_t n) const
    {
        return (double)n * price;
    }

protected:
    /**
     * Normal, un-discounted price.
     */
    double price = 0.0;

private:
    // ISBN number of this item.
    std::string bookNo;
};

/**
 * Abstract base class to hold the discount rate and quantity.
 * Derived classes will implement pricing strategies using these data.
 */
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, const double price,
        const std::size_t qty, const double disc) :
        Quote(book, price),
        quantity(qty), discount(disc) { }

    std::pair<size_t, double> discount_policy() const
    {
        return { quantity, discount };
    }

protected:
    /**
     * Purchase size for the discount to apply.
     */
    std::size_t quantity = 0;

    /**
     * fractional discount to apply
     */
    double discount = 0.0;
};

/**
 * The discount kicks in when a specified number of copies of the same book are sold.
 * The discount is expressed as a fraction used to reduce the normal price.
 */
class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;
    Bulk_quote() = default;

    // overrides the base version in order to implement the bulk purchase discount policy
    double net_price(const std::size_t) const override;

    Bulk_quote *clone() const { return new Bulk_quote(*this); }
};

/**
 * Calculate and print the price for the given number of copies, applying any discounts.
 * @return total price.
 */
double print_total(std::ostream &, const Quote &, const std::size_t);

}
#endif


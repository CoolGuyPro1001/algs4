#ifndef TRANSACTION_H
#define TRANSACTION_H

/******************************************************************************
 *  Compilation:  javac Transaction.java
 *  Execution:    java Transaction
 *  Dependencies: StdOut.java
 *
 *  Data type for commercial transactions.
 *
 ******************************************************************************/

/**
 *  The {@code Transaction} class is an immutable data type to encapsulate a
 *  commercial transaction with a customer name, date, and amount.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

#include "Date.h"

class Transaction
{
public:

    /**
     * Initializes a new transaction from the given arguments.
     *
     * @param  who the person involved in this transaction
     * @param  when the date of this transaction
     * @param  amount the amount of this transaction
     * @throws IllegalArgumentException if {@code amount}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY},
     *         or {@code Double.NEGATIVE_INFINITY}
     */
    Transaction(std::string who, Date when, double amount);

    /**
     * Initializes a new transaction by parsing a string of the form NAME DATE AMOUNT.
     *
     * @param  transaction the string to parse
     * @throws IllegalArgumentException if {@code amount}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY},
     *         or {@code Double.NEGATIVE_INFINITY}
     */
    Transaction(std::string transaction);

    /**
     * Returns the name of the customer involved in this transaction.
     *
     * @return the name of the customer involved in this transaction
     */
    std::string who() const;

    /**
     * Returns the date of this transaction.
     *
     * @return the date of this transaction
     */
    Date when() const;

    /**
     * Returns the amount of this transaction.
     *
     * @return the amount of this transaction
     */
    double amount() const;

    /**
     * Returns a string representation of this transaction.
     *
     * @return a string representation of this transaction
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);

    /**
     * Compares this transaction to the specified object.
     *
     * @param  other the other transaction
     * @return true if this transaction is equal to {@code other}; false otherwise
     */
    bool operator==(const Transaction& other) const;
    bool operator!=(const Transaction& other) const;
    bool operator>(const Transaction& other) const;
    bool operator<(const Transaction& other) const;
    bool operator>=(const Transaction& other) const;
    bool operator<=(const Transaction& other) const;

    /**
     * Returns a hash code for this transaction.
     *
     * @return a hash code for this transaction
     */
    size_t hash_code();

    /**
     * Compares two transactions by customer name.
     */
    static bool who_order(Transaction a, Transaction b);

    /**
     * Compares two transactions by date.
     */
    static bool when_order(Transaction a, Transaction b);

    /**
     * Compares two transactions by amount.
     */
    static bool how_much_order(Transaction a, Transaction b);


private:
    std::string  m_who;      // customer
    Date    m_when;     // date
    double  m_amount;   // amount
};




/******************************************************************************
 *  Copyright 2002-2022, Robert Sedgewick and Kevin Wayne.
 *
 *  This file is part of algs4.jar, which accompanies the textbook
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *
 *  algs4.jar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif
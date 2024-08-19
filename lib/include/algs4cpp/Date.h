#ifndef DATE_H
#define DATE_H

/******************************************************************************
 *  Compilation:  javac Date.java
 *  Execution:    java Date
 *  Dependencies: StdOut.java
 *
 *  An immutable data type for dates.
 *
 ******************************************************************************/

/**
 *  The {@code Date} class is an immutable data type to encapsulate a
 *  date (day, month, and year).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
struct Date
{
public:
    Date();
    
   /**
     * Initializes a new date from the month, day, and year.
     * @param month the month (between 1 and 12)
     * @param day the day (between 1 and 28-31, depending on the month)
     * @param year the year
     * @throws IllegalArgumentException if this date is invalid
     */
    Date(int month, int day, int year);

    /**
     * Initializes new date specified as a string in form MM/DD/YYYY.
     * @param date the string representation of this date
     * @throws IllegalArgumentException if this date is invalid
     */
    Date(std::string date);

    /**
     * Return the month.
     * @return the month (an integer between 1 and 12)
     */
    int month() const;

    /**
     * Returns the day.
     * @return the day (an integer between 1 and 31)
     */
    int day() const;

    /**
     * Returns the year.
     * @return the year
     */
    int year() const;

    // is the given date valid?
    static bool is_valid(int m, int d, int y);

    // is y a leap year?
    static bool is_leap_year(int y);

    /**
     * Returns the next date in the calendar.
     *
     * @return a date that represents the next day after this day
     */
    Date next() const;

    /**
     * Compares two dates chronologically.
     *
     * @param  other the other date
     * @return {@code true} if this date is after that date; {@code false} otherwise
     */
    bool is_after(Date other) const;

    /**
     * Compares two dates chronologically.
     *
     * @param  other the other date
     * @return {@code true} if this date is before that date; {@code false} otherwise
     */
    bool is_before(Date other) const;

    /**
     * Compares two dates chronologically.
     *
     * @return the value {@code 0} if the argument date is equal to this date;
     *         a negative integer if this date is chronologically less than
     *         the argument date; and a positive integer if this date is
     *         chronologically after the argument date
     */
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    /**
     * Returns a string representation of this date.
     *
     * @return the string representation in the format MM/DD/YYYY
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Date& d);

    /**
     * Compares this date to the specified date.
     *
     * @param  other the other date
     * @return {@code true} if this date equals {@code other}; {@code false} otherwise
     */
    bool operator==(const Date& other) const;

    /**
     * Returns an integer hash code for this date.
     *
     * @return an integer hash code for this date
     */
    int hash_code() const;

private:
    static constexpr int DAYS[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int m_month;   // month (between 1 and 12)
    int m_day;     // day   (between 1 and DAYS[month]
    int m_year;    // year
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
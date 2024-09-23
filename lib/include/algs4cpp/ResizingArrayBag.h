#ifndef RESIZINGARRAYBAG_H
#define RESIZINGARRAYBAG_H

/******************************************************************************
 *  Compilation:  javac ResizingArrayBag.java
 *  Execution:    java ResizingArrayBag
 *  Dependencies: StdIn.java StdOut.java
 *
 *  Bag implementation with a resizing array.
 *
 ******************************************************************************/

/**
 *  The {@code ResizingArrayBag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *  <p>
 *  This implementation uses a resizing array.
 *  See {@link LinkedBag} for a version that uses a singly linked list.
 *  The <em>add</em> operation takes constant amortized time; the
 *  <em>isEmpty</em>, and <em>size</em> operations
 *  take constant time. Iteration takes time proportional to the number of items.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Item>
class ResizingArrayBag
{
public:
    /**
     * Initializes an empty bag.
     */
    ResizingArrayBag()
    {
        m_a = std::vector<Item>(INIT_CAPACITY);
        m_n = 0;
    }

    /**
     * Is this bag empty?
     * @return true if this bag is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_n == 0;
    }

    /**
     * Returns the number of items in this bag.
     * @return the number of items in this bag
     */
    int size() const
    {
        return m_n;
    }

    /**
     * Adds the item to this bag.
     * @param item the item to add to this bag
     */
    void add(Item item)
    {
        if (m_n == m_a.size()) resize(2*m_a.size()); // double size of array if necessary
        m_a[m_n++] = item;                           // add item
    }

    auto begin()
    {
       return m_a.begin(); 
    }

    auto end()
    {
        return m_a.end();
    }

private:
    // initial capacity of underlying resizing array
    static const int INIT_CAPACITY = 8;

    std::vector<Item> m_a;  // array of items
    int m_n;                // number of elements on bag

    // resize the underlying array holding the elements
    void resize(int capacity)
    {
        assert(capacity >= m_n);
        m_a.resize(capacity);
    }
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
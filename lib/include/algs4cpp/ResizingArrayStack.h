#ifndef RESIZINGARRAYSTACK_H
#define RESIZINGARRAYSTACK_H

/******************************************************************************
 *  Compilation:  javac ResizingArrayStack.java
 *  Execution:    java ResizingArrayStack < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/13stacks/tobe.txt
 *
 *  Stack implementation with a resizing array.
 *
 *  % more tobe.txt
 *  to be or not to - be - - that - - - is
 *
 *  % java ResizingArrayStack < tobe.txt
 *  to be not that or be (2 left on stack)
 *
 ******************************************************************************/

/**
 *  The {@code ResizingArrayStack} class represents a last-in-first-out (LIFO) stack
 *  of generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a resizing array, which double the underlying array
 *  when it is full and halves the underlying array when it is one-quarter full.
 *  The <em>push</em> and <em>pop</em> operations take constant amortized time.
 *  The <em>size</em>, <em>peek</em>, and <em>is-empty</em> operations takes
 *  constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

template <typename Item>
class ResizingArrayStack
{
public:

    /**
     * Initializes an empty stack.
     */
    ResizingArrayStack()
    {
        m_a = std::vector<std::unique_ptr<Item>>(INIT_CAPACITY);
        m_n = 0;
    }

    /**
     * Is this stack empty?
     * @return true if this stack is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_n == 0;
    }

    /**
     * Returns the number of items in the stack.
     * @return the number of items in the stack
     */
    int size() const
    {
        return m_n;
    }

    // resize the underlying array holding the elements
    void resize(int capacity)
    {
        assert(capacity >= m_n);

        // textbook implementation
        std::vector<std::unique_ptr<Node<Item>>> copy = std::vector<std::unique_ptr<Node<Item>>>(capacity);
        for (int i = 0; i < m_n; i++)
        {
           // copy[i] = std::move(m_a[i]);
        }
        //m_a = copy;
    }

    /**
     * Adds the item to this stack.
     * @param item the item to add
     */
    void push(std::unique_ptr<Item> item)
    {
        if (m_n == m_a.size()) resize(2*m_a.size());    // double size of array if necessary
        m_a[m_n++] = std::move(item);                   // add item
    }

    /**
     * Removes and returns the item most recently added to this stack.
     * @return the item most recently added
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    std::unique_ptr<Item> pop()
    {
        if (is_empty()) error("Stack underflow");
        std::unique_ptr<Node<Item>> item = std::move(m_a[m_n-1]);
        //m_a[m_n-1] = null;                              // to avoid loitering
        m_n--;
        // shrink size of array if necessary
        if (m_n > 0 && m_n == m_a.size()/4) resize(m_a.size()/2);
        return item;
    }


    /**
     * Returns (but does not remove) the item most recently added to this stack.
     * @return the item most recently added to this stack
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    Item& peek() const
    {
        if (is_empty()) error("Stack underflow");
        return *(m_a[m_n-1]);
    }

    /**
     * Returns an iterator to this stack that iterates through the items in LIFO order.
     * @return an iterator to this stack that iterates through the items in LIFO order.
     */
    /*Iterator<Item> iterator() {
        return new ReverseArrayIterator();
    }

    // a array iterator, in reverse order
    class ReverseArrayIterator implements Iterator<Item> {
        private int i;

        ReverseArrayIterator() {
            i = m_n-1;
        }

        bool hasNext() {
            return i >= 0;
        }

        Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            return m_a[i--];
        }
    }*/

private:
    // initial capacity of underlying resizing array
    static const int INIT_CAPACITY = 8;

    std::vector<std::unique_ptr<Item>> m_a;     // array of items
    int m_n;                                    // number of elements on stack
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
#ifndef RESIZINGARRAYQUEUE_H
#define RESIZINGARRAYQUEUE_H


/******************************************************************************
 *  Compilation:  javac ResizingArrayQueue.java
 *  Execution:    java ResizingArrayQueue < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/13stacks/tobe.txt
 *
 *  Queue implementation with a resizing array.
 *
 *  % java ResizingArrayQueue < tobe.txt
 *  to be or not to be (2 left on queue)
 *
 ******************************************************************************/

/**
 *  The {@code ResizingArrayQueue} class represents a first-in-first-out (FIFO)
 *  queue of generic items.
 *  It supports the usual <em>enqueue</em> and <em>dequeue</em>
 *  operations, along with methods for peeking at the first item,
 *  testing if the queue is empty, and iterating through
 *  the items in FIFO order.
 *  <p>
 *  This implementation uses a resizing array, which double the underlying array
 *  when it is full and halves the underlying array when it is one-quarter full.
 *  The <em>enqueue</em> and <em>dequeue</em> operations take constant amortized time.
 *  The <em>size</em>, <em>peek</em>, and <em>is-empty</em> operations takes
 *  constant time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Item>
class ResizingArrayQueue
{
public: 
    /**
     * Initializes an empty queue.
     */
    ResizingArrayQueue()
    {
        m_q = std::vector<ptr<Item>>(INIT_CAPACITY);
        m_n = 0;
        m_first = 0;
        m_last = 0;
    }

    /**
     * Is this queue empty?
     * @return true if this queue is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_n == 0;
    }

    /**
     * Returns the number of items in this queue.
     * @return the number of items in this queue
     */
    int size() const
    {
        return m_n;
    }

    
    /**
     * Adds the item to this queue.
     * @param item the item to add
     */
    void enqueue(Item item)
    {
        // double size of array if necessary and recopy to front of array
        if (m_n == m_q.size()) resize(2*m_q.size());    // double size of array if necessary
        m_q[m_last++] = alloc<Item>(item);              // add item
        if (m_last == m_q.size()) m_last = 0;           // wrap-around
        m_n++;
    }

    /**
     * Removes and returns the item on this queue that was least recently added.
     * @return the item on this queue that was least recently added
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    Item dequeue()
    {
        if (is_empty()) error("Queue underflow");
        Item item = *(m_q[m_first]);
        m_q[m_first].reset();                   // to avoid loitering
        m_n--;
        m_first++;
        if (m_first == m_q.size()) m_first = 0; // wrap-around
        // shrink size of array if necessary
        if (m_n > 0 && m_n == m_q.size()/4) resize(m_q.size()/2);
        return item;
    }

    /**
     * Returns the item least recently added to this queue.
     * @return the item least recently added to this queue
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    Item peek() const
    {
        if (is_empty()) error("Queue underflow");
        return *(m_q[m_first]);
    }

    auto begin() const
    {
        return m_q.begin() + m_first;
    }

    auto end() const
    {
        return m_q.begin() + m_last;
    }

private:
    // initial capacity of underlying resizing array
    static const int INIT_CAPACITY = 8;

    std::vector<ptr<Item>> m_q;       // queue elements
    int m_n;          // number of elements on queue
    int m_first;      // index of first element of queue
    int m_last;       // index of next available slot

    // resize the underlying array
    void resize(int capacity)
    {
        assert(capacity >= m_n);
        std::rotate(m_q.rbegin(), m_q.rend() - m_first, m_q.rend()); // Right rotate
        m_q.resize(capacity);
        m_first = 0;
        m_last  = m_n;
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
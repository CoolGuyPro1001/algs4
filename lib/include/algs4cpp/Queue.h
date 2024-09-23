#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

/******************************************************************************
 *  Compilation:  javac LinkedQueue.java
 *  Execution:    java LinkedQueue < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/13stacks/tobe.txt
 *
 *  A generic queue, implemented using a singly linked list.
 *
 *  % java Queue < tobe.txt
 *  to be or not to be (2 left on queue)
 *
 ******************************************************************************/

/**
 *  The {@code LinkedQueue} class represents a first-in-first-out (FIFO)
 *  queue of generic items.
 *  It supports the usual <em>enqueue</em> and <em>dequeue</em>
 *  operations, along with methods for peeking at the first item,
 *  testing if the queue is empty, and iterating through
 *  the items in FIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a non-static nested class
 *  for linked-list nodes.  See {@link Queue} for a version that uses a static nested class.
 *  The <em>enqueue</em>, <em>dequeue</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Item>
class Queue
{
public:
    /**
     * Initializes an empty queue.
     */
    Queue()
    {
        m_first = nullptr;
        m_last  = nullptr;
        m_n = 0;
        assert(check());
    }

    /**
     * Is this queue empty?
     * @return true if this queue is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_first == nullptr;
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
     * Returns the item least recently added to this queue.
     * @return the item least recently added to this queue
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    Item peek() const
    {
        if (is_empty()) error("Queue underflow");
        return m_first->item;
    }

    /**
     * Adds the item to this queue.
     * @param item the item to add
     */
    void enqueue(Item item)
    {
        Node<Item>* old_last;
        if (m_n == 1)
            old_last = m_first.get();
        else
            old_last = m_last;

        // Owns the new last node
        ptr<Node<Item>> new_last = alloc<Node<Item>>();
        new_last->item = item;
        new_last->next = nullptr;
        m_last = new_last.get();

        // Transfer ownership
        if (is_empty())
            m_first = std::move(new_last);
        else
            old_last->next = std::move(new_last);
            
        m_n++;
        assert(check());
    }

    /**
     * Removes and returns the item on this queue that was least recently added.
     * @return the item on this queue that was least recently added
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    Item dequeue()
    {
        if (is_empty()) error("Queue underflow");
        Item item = m_first->item;
        m_first = std::move(m_first->next);
        m_n--;
        if (is_empty()) m_last = nullptr;   // to avoid loitering
        assert(check());
        return item;
    }

    /**
     * Returns a string representation of this queue.
     * @return the sequence of items in FIFO order, separated by spaces
     */
    std::string to_string() const
    {
        std::string s; 
        for (Item item : *this)
            s += std::format("{} ", item);
        return s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue& q)
    {
        os << q.to_string();
        return os;
    }

    LinkedIterator<Item> begin() const
    {
        return LinkedIterator<Item>(m_first.get());
    }

    LinkedIterator<Item> end() const
    {
        return LinkedIterator<Item>(nullptr);
    }

private:
    int m_n;                    // number of elements on queue
    ptr<Node<Item>> m_first;    // beginning of queue
    Node<Item>* m_last;         // end of queue

    // check internal invariants
    bool check()
    {
        if (m_n < 0)
        {
            return false;
        }
        else if (m_n == 0)
        {
            if (m_first != nullptr) return false;
            if (m_last  != nullptr) return false;
        }
        else if (m_n == 1)
        {
            if (m_first == nullptr) return false;
            if (m_last == nullptr) return false;
            if (m_first->next != nullptr) return false;
        }
        else
        {
            if (m_first == nullptr || m_last == nullptr) return false;
            if (m_first.get() == m_last) return false;
            if (m_first->next == nullptr) return false;
            if (m_last->next  != nullptr) return false;

            // check internal consistency of instance variable n
            int num_of_nodes = 0;
            for (Node<Item>* x = m_first.get(); x != nullptr && num_of_nodes <= m_n; x = x->next.get())
            {
                num_of_nodes++;
            }
            if (num_of_nodes != m_n) return false;

            // check internal consistency of instance variable last
            Node<Item>* last_node = m_first.get();
            while (last_node->next != nullptr)
            {
                last_node = last_node->next.get();
            }
            if (m_last != last_node) return false;
        }

        return true;
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
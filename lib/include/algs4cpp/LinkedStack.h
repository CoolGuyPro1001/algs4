#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

/******************************************************************************
 *  Compilation:  javac LinkedStack.java
 *  Execution:    java LinkedStack < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/13stacks/tobe.txt
 *
 *  A generic stack, implemented using a linked list. Each stack
 *  element is of type Item.
 *
 *  % more tobe.txt
 *  to be or not to - be - - that - - - is
 *
 *  % java LinkedStack < tobe.txt
 *  to be not that or be (2 left on stack)
 *
 ******************************************************************************/

/**
 *  The {@code LinkedStack} class represents a last-in-first-out (LIFO) stack of
 *  generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a non-static nested class for
 *  linked-list nodes. See {@link Stack} for a version that uses a static nested class.
 *  The <em>push</em>, <em>pop</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

template <typename Item>
class LinkedStack
{
public:
    /**
     * Initializes an empty stack.
     */
    LinkedStack()
    {
        m_first = std::make_unique<Node<Item>>();
        m_first = nullptr;
        m_n = 0;
        assert(check());
    }

    /**
     * Is this stack empty?
     * @return true if this stack is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_first == nullptr;
    }

    /**
     * Returns the number of items in the stack.
     * @return the number of items in the stack
     */
    int size() const
    {
        return m_n;
    }

    /**
     * Adds the item to this stack.
     * @param item the item to add
     */
    void push(Item item)
    {
        std::unique_ptr<Node<Item>> old_first = std::move(m_first);
        m_first = std::make_unique<Node<Item>>();
        m_first->item = item;
        m_first->next = std::move(old_first);
        m_n++;
        assert(check());
    }

    /**
     * Removes and returns the item most recently added to this stack.
     * @return the item most recently added
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    Item pop()
    {
        if (is_empty()) error("Stack underflow");
        Item item = m_first->item;        // save item to return
        m_first = std::move(m_first->next);  // delete first node
        m_n--;
        assert(check());
        return item;                   // return the saved item
    }


    /**
     * Returns (but does not remove) the item most recently added to this stack.
     * @return the item most recently added to this stack
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    Item peek() const
    {
        if (is_empty()) error("Stack underflow");
        return m_first->item;
    }

    /**
     * Returns a string representation of this stack.
     * @return the sequence of items in the stack in LIFO order, separated by spaces
     */
    /*std::string to_string()
    {
        StringBuilder s = new StringBuilder();
        for (Item item : this)
            s.append(item + " ");
        return s.toString();
    }*/

    /**
     * Returns an iterator to this stack that iterates through the items in LIFO order.
     * @return an iterator to this stack that iterates through the items in LIFO order.
     */
    /*Iterator<Item> iterator()
    {
        return new LinkedIterator();
    }*/

    // a linked-list iterator
    /*class LinkedIterator implements Iterator<Item>
    {
        Node current = first;

        boolean hasNext()
        {
            return current != null;
        }

        Item next()
        {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }*/


    // check internal invariants
    bool check()
    {

        // check a few properties of instance variable 'first'
        if (m_n < 0)
        {
            return false;
        }
        if (m_n == 0)
        {
            if (m_first != nullptr) return false;
        }
        else if (m_n == 1)
        {
            if (m_first == nullptr)      return false;
            if (m_first->next != nullptr) return false;
        }
        else
        {
            if (m_first == nullptr)      return false;
            if (m_first->next == nullptr) return false;
        }

        // check internal consistency of instance variable n
        int number_of_nodes = 0;
        // for (std::unique_ptr<Node<Item>> x = m_first; x != nullptr && number_of_nodes <= m_n; x = x->next)
        // {
        //     number_of_nodes++;
        // }
        if (number_of_nodes != m_n) return false;

        return true;
    }

private:
    int m_n;          // size of the stack
    std::unique_ptr<Node<Item>> m_first;     // top of stack
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
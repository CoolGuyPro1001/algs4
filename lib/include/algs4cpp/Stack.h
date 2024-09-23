#ifndef STACK_H
#define STACK_H

/******************************************************************************
 *  Compilation:  javac Stack.java
 *  Execution:    java Stack < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/13stacks/tobe.txt
 *
 *  A generic stack, implemented using a singly linked list.
 *  Each stack element is of type Item.
 *
 *  This version uses a static nested class Node (to save 8 bytes per
 *  Node), whereas the version in the textbook uses a non-static nested
 *  class (for simplicity).
 *
 *  % more tobe.txt
 *  to be or not to - be - - that - - - is
 *
 *  % java Stack < tobe.txt
 *  to be not that or be (2 left on stack)
 *
 ******************************************************************************/

/**
 *  The {@code Stack} class represents a last-in-first-out (LIFO) stack of generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a static nested class for
 *  linked-list nodes. See {@link LinkedStack} for the version from the
 *  textbook that uses a non-static nested class.
 *  See {@link ResizingArrayStack} for a version that uses a resizing array.
 *  The <em>push</em>, <em>pop</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Item> the generic type each item in this stack
 */

template <typename Item>
class Stack
{
public:
    /**
     * Initializes an empty stack.
     */
    Stack()
    {
        m_first = nullptr;
        m_n = 0;
        assert(check());
    }
    
    /**
     * Returns true if this stack is empty.
     *
     * @return true if this stack is empty; false otherwise
     */
    bool is_empty() const
    {
        return m_first == nullptr;
    }

    /**
     * Returns the number of items in this stack.
     *
     * @return the number of items in this stack
     */
    int size() const
    {
        return m_n;
    }

    /**
     * Adds the item to this stack.
     *
     * @param  item the item to add
     */
    void push(Item item)
    {
        ptr<Node<Item>> old_first = std::move(m_first);
        m_first = alloc<Node<Item>>();
        m_first->item = item;
        m_first->next = std::move(old_first);
        m_n++;
        assert(check());
    }

    /**
     * Removes and returns the item most recently added to this stack.
     *
     * @return the item most recently added
     * @throws NoSuchElementException if this stack is empty
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
     *
     * @return the item most recently added to this stack
     * @throws NoSuchElementException if this stack is empty
     */
    Item peek() const
    {
        if (is_empty()) error("Stack underflow");
        return m_first->item;
    }

    /**
     * Returns a string representation of this stack.
     *
     * @return the sequence of items in this stack in LIFO order, separated by spaces
     */
    std::string to_string() const
    {
        std::string s;
        for (Item item : *this)
            s += std::format("{} ", item);
        return s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& s)
    {
        os << s.to_string();
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
    ptr<Node<Item>> m_first;     // top of stack
    int m_n;                // size of the stack

    // check internal invariants
    bool check() const
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
        for (Node<Item>* x = m_first.get(); x != nullptr && number_of_nodes <= m_n; x = x->next.get())
        {
            number_of_nodes++;
        }
        if (number_of_nodes != m_n) return false;

        return true;
    }
};

#endif
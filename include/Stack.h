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
        first = nullptr;
        n = 0;
    }
    
    /**
     * Returns true if this stack is empty.
     *
     * @return true if this stack is empty; false otherwise
     */
    bool isEmpty()
    {
        return first == nullptr;
    }

    /**
     * Returns the number of items in this stack.
     *
     * @return the number of items in this stack
     */
    int size()
    {
        return n;
    }

    /**
     * Adds the item to this stack.
     *
     * @param  item the item to add
     */
    void push(Item item)
    {
        Node<Item>* oldfirst = first;
        first = new Node<Item>();
        first->item = item;
        first->next = oldfirst;
        n++;
    }

    /**
     * Removes and returns the item most recently added to this stack.
     *
     * @return the item most recently added
     * @throws NoSuchElementException if this stack is empty
     */
    Item pop()
    {
        if (isEmpty()) error("Stack underflow");
        Item item = first->item;        // save item to return
        Node<Item>* oldfirst = first;
        first = first->next;            // delete first node
        delete oldfirst;
        n--;
        return item;                   // return the saved item
    }

    /**
     * Returns (but does not remove) the item most recently added to this stack.
     *
     * @return the item most recently added to this stack
     * @throws NoSuchElementException if this stack is empty
     */
    Item peek()
    {
        if (isEmpty()) error("Stack underflow");
        return first->item;
    }

    /**
     * Returns a string representation of this stack.
     *
     * @return the sequence of items in this stack in LIFO order, separated by spaces
     */
    //TODO
    /*stdstring toString()
    {
        stdstring s;
        for (Item item : this)
        {
            s += item;
            s += ' ';
        }
        return s;
    }*/

    /**
     * Returns an iterator to this stack that iterates through the items in LIFO order.
     *
     * @return an iterator to this stack that iterates through the items in LIFO order
     */
    //TODO
    /*Iterator<Item> iterator() {
        return new LinkedIterator(first);
    }

    // the iterator
    private class LinkedIterator implements Iterator<Item> {
        private Node<Item> current;

        LinkedIterator(Node<Item> first) {
            current = first;
        }

        // is there a next item?
        bool hasNext() {
            return current != null;
        }

        // returns the next item
        Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }*/

    
private:
    Node<Item>* first;     // top of stack
    int n;                // size of the stack
};

#endif
#ifndef SEQUENTIALSEARCHST_H
#define SEQUENTIALSEARCHST_H

#include "Queue.h"

/******************************************************************************
 *  Compilation:  javac SequentialSearchST.java
 *  Execution:    java SequentialSearchST
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/31elementary/tinyST.txt
 *
 *  Symbol table implementation with sequential search in an
 *  unordered linked list of key-value pairs.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % java SequentialSearchST < tinyST.txt
 *  L 11
 *  P 10
 *  M 9
 *  X 7
 *  H 5
 *  C 4
 *  R 3
 *  A 8
 *  E 12
 *  S 0
 *
 ******************************************************************************/

// a helper linked list data type
template <typename Key, typename Value>
struct STNode
{
    Key key;
    Value val;
    ptr<STNode<Key, Value>> next;

    STNode(Key key, Value val, ptr<STNode> next)
    {
        this->key  = key;
        this->val  = val;
        this->next = std::move(next);
    }
};

/**
 *  The {@code SequentialSearchST} class represents an (unordered)
 *  symbol table of generic key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  The class also uses the convention that values cannot be {@code nullptr}. Setting the
 *  value associated with a key to {@code nullptr} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  It relies on the {@code equals()} method to test whether two keys
 *  are equal. It does not call either the {@code compareTo()} or
 *  {@code hashCode()} method.
 *  <p>
 *  This implementation uses a <em>singly linked list</em> and
 *  <em>sequential search</em>.
 *  The <em>put</em> and <em>delete</em> operations take &Theta;(<em>n</em>).
 *  The <em>get</em> and <em>contains</em> operations takes &Theta;(<em>n</em>)
 *  time in the worst case.
 *  The <em>size</em>, and <em>is-empty</em> operations take &Theta;(1) time.
 *  Construction takes &Theta;(1) time.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/31elementary">Section 3.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Key, typename Value>
class SequentialSearchST
{
public:
    /**
     * Initializes an empty symbol table.
     */
    SequentialSearchST() {}

    /**
     * Returns the number of key-value pairs in this symbol table.
     *
     * @return the number of key-value pairs in this symbol table
     */
    int size()
    {
        return m_n;
    }

    /**
     * Returns true if this symbol table is empty.
     *
     * @return {@code true} if this symbol table is empty;
     *         {@code false} otherwise
     */
    bool is_empty()
    {
        return m_n == 0;
    }

    /**
     * Returns true if this symbol table contains the specified key.
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key};
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    bool contains(Key key)
    {
        return get(key) != std::optional<Value>();
    }

    /**
     * Returns the value associated with the given key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code nullptr} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key)
    {
        for (STNode<Key, Value>* x = m_first.get(); x != nullptr; x = x->next.get())
        {
            if (key == x->key)
                return std::optional<Value>(x->val);
        }
        return std::optional<Value>();
    }

    /**
     * Inserts the specified key-value pair into the symbol table, overwriting the old
     * value with the new value if the symbol table already contains the specified key.
     * Deletes the specified key (and its associated value) from this symbol table
     * if the specified value is {@code nullptr}.
     *
     * @param  key the key
     * @param  val the value
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    void put(Key key, Value val)
    {
        for (STNode<Key, Value>* x = m_first.get(); x != nullptr; x = x->next.get())
        {
            if (key == x->key)
            {
                x->val = val;
                return;
            }
        }
        m_first = alloc<STNode<Key, Value>>(key, val, std::move(m_first));
        m_n++;
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    void delete_key(Key key)
    {
        m_first = delete_key(m_first, key);
    }

    /**
     * Returns all keys in the symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in the symbol table
     */
    Queue<Key> keys() 
    {
        Queue<Key> queue = Queue<Key>();
        for (STNode<Key, Value>* x = m_first.get(); x != nullptr; x = x->next.get())
            queue.enqueue(x->key);
        return queue;
    }

private: 
    int m_n;                            // number of key-value pairs
    ptr<STNode<Key, Value>> m_first;    // the linked list of key-value pairs

    // delete key in linked list beginning at TreeNode<Key, Value> x
    // warning: function call stack too large if table is large
    STNode<Key, Value> delete_key(STNode<Key, Value> x, Key key)
    {
        if (x == nullptr) return nullptr;
        if (key == x->key)
        {
            m_n--;
            return x->next;
        }
        x->next = delete_key(x->next, key);
        return x;
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
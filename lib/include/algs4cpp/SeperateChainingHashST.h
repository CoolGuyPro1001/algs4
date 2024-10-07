#ifndef SEPERATECHAININGHASHST_H
#define SEPERATECHAININGHASHST_H

#include "SequentialSearchST.h"
#include "Queue.h"

/******************************************************************************
 *  Compilation:  javac SeparateChainingHashST.java
 *  Execution:    java SeparateChainingHashST < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/34hash/tinyST.txt
 *
 *  A symbol table implemented with a separate-chaining hash table.
 *
 ******************************************************************************/

/**
 *  The {@code SeparateChainingHashST} class represents a symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code nullptr}—setting the
 *  value associated with a key to {@code nullptr} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses a separate chaining hash table. It requires that
 *  the key type overrides the {@code equals()} and {@code hashCode()} methods.
 *  The expected time per <em>put</em>, <em>contains</em>, or <em>remove</em>
 *  operation is constant, subject to the uniform hashing assumption.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/34hash">Section 3.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For other implementations, see {@link ST}, {@link BinarySearchST},
 *  {@link SequentialSearchST}, {@link BST}, {@link RedBlackBST}, and
 *  {@link LinearProbingHashST},
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Key, typename Value>
class SeparateChainingHashST
{
public:
    /**
     * Initializes an empty symbol table.
     */
    SeparateChainingHashST() : SeparateChainingHashST(INIT_CAPACITY) {}

    /**
     * Initializes an empty symbol table with {@code m} chains.
     * @param m the initial number of chains
     */
    SeparateChainingHashST(int m)
    {
        m_m = m;
        m_st = std::vector<SequentialSearchST<Key, Value>>(m);
    }

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
        return get(key) != nullptr;
    }

    /**
     * Returns the value associated with the specified key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with {@code key} in the symbol table;
     *         {@code nullptr} if no such value
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key)
    {
        int i = hash(key);
        return m_st[i].get(key);
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
        // double table size if average length of list >= 10
        if (m_n >= 10*m_m) resize(2*m_m);

        int i = hash(key);
        if (!m_st[i].contains(key)) m_n++;
        m_st[i].put(key, val);
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
        if (key == nullptr) error("argument to delete() is nullptr");

        int i = hash(key);
        if (m_st[i].contains(key)) m_n--;
        m_st[i].delete_key(key);

        // halve table size if average length of list <= 2
        if (m_m > INIT_CAPACITY && m_n <= 2*m_m) resize(m_m/2);
    }

    // return keys in symbol table as an Iterable
    Queue<Key> keys()
    {
        Queue<Key> queue = Queue<Key>();
        for (int i = 0; i < m_m; i++)
        {
            for (Key key : m_st[i].keys())
                queue.enqueue(key);
        }
        return queue;
    }

private:
    static const int INIT_CAPACITY = 4;

    int m_n;                                // number of key-value pairs
    int m_m;                                // hash table size
    std::vector<SequentialSearchST<Key, Value>> m_st;  // array of linked-list symbol tables

    // resize the hash table to have the given number of chains,
    // rehashing all of the keys
    void resize(int chains)
    {
        SeparateChainingHashST<Key, Value> temp = SeparateChainingHashST<Key, Value>(chains);
        for (int i = 0; i < m_m; i++)
        {
            for (Key key : m_st[i].keys())
            {
                std::optional<Value> val = m_st[i].get(key);
                if (val.has_value())
                    temp.put(key, val.value());
            }
        }
        m_m  = temp.m_m;
        m_n  = temp.m_n;
        m_st = std::move(temp.m_st);
    }

    // hash function for keys - returns value between 0 and m-1
    int hash_textbook(Key key)
    {
        return (std::hash<Key>{}(key) & 0x7fffffff) % m_m;
    }

    // hash function for keys - returns value between 0 and m-1 (assumes m is a power of 2)
    // (from Java 7 implementation, protects against poor quality hashCode() implementations)
    int hash(Key key)
    {
        int h = std::hash<Key>{}(key);
        uint32_t uh = (uint32_t) h;
        h ^= (uh >> 20) ^ (uh >> 12) ^ (uh >> 7) ^ (uh >> 4);
        return h & (m_m-1);
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
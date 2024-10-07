#ifndef LINEARPROBINGHASHST_H
#define LINEARPROBINGHASHST_H

#include "Queue.h"

/******************************************************************************
 *  Compilation:  javac LinearProbingHashST.java
 *  Execution:    java LinearProbingHashST < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/34hash/tinyST.txt
 *
 *  Symbol-table implementation with linear-probing hash table.
 *
 ******************************************************************************/

/**
 *  The {@code LinearProbingHashST} class represents a symbol table of generic
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
 *  This implementation uses a linear probing hash table. It requires that
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
 *  {@link SeparateChainingHashST},
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Key, typename Value>
class LinearProbingHashST
{
public: 
    /**
     * Initializes an empty symbol table.
     */
    LinearProbingHashST() : LinearProbingHashST(INIT_CAPACITY) {}

    /**
     * Initializes an empty symbol table with the specified initial capacity.
     *
     * @param capacity the initial capacity
     */
    LinearProbingHashST(int capacity)
    {
        m_m = capacity;
        m_n = 0;
        m_keys = std::vector<ptr<Key>>(m_m);
        m_vals = std::vector<ptr<Value>>(m_m);
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     *
     * @return the number of key-value pairs in this symbol table
     */
    int size() const
    {
        return m_n;
    }

    /**
     * Returns true if this symbol table is empty.
     *
     * @return {@code true} if this symbol table is empty;
     *         {@code false} otherwise
     */
    bool is_empty() const
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
    bool contains(Key key) const
    {
        if (key == nullptr) error("argument to contains() is nullptr");
        return get(key) != nullptr;
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
        // double table size if 50% full
        if (m_n >= m_m/3) resize(2*m_m);

        int i;
        for (i = hash(key); m_keys[i] != nullptr; i = (i + 1) % m_m)
        {
            if (*m_keys[i] == key)
            {
                *m_vals[i] = val;
                return;
            }
        }
        m_keys[i] = alloc<Key>(key);
        m_vals[i] = alloc<Value>(val);
        m_n++;
    }

    /**
     * Returns the value associated with the specified key.
     * @param key the key
     * @return the value associated with {@code key};
     *         {@code nullptr} if no such value
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key) const
    {
        for (int i = hash(key); m_keys[i] != nullptr; i = (i + 1) % m_m)
            if (*m_keys[i] == key)
                return std::optional<Value>(*m_vals[i]);
        return std::optional<Value>();
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
        if (!contains(key)) return;

        // find position i of key
        int i = hash(key);
        while (!key == *m_keys[i])
        {
            i = (i + 1) % m_m;
        }

        // delete key and associated value
        m_keys[i] = nullptr;
        m_vals[i] = nullptr;

        // rehash all keys in same cluster
        i = (i + 1) % m_m;
        while (m_keys[i] != nullptr)
        {
            // delete keys[i] and vals[i] and reinsert
            Key   key_to_rehash = m_keys[i];
            Value val_to_rehash = m_vals[i];
            m_keys[i] = nullptr;
            m_vals[i] = nullptr;
            m_n--;
            put(key_to_rehash, val_to_rehash);
            i = (i + 1) % m_m;
        }

        m_n--;

        // halves size of array if it's 12.5% full or less
        if (m_n > 0 && m_n <= m_m/8) resize(m_m/2);

        assert(check());
    }

    /**
     * Returns all keys in this symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in this symbol table
     */
    Queue<Key> keys() const
    {
        Queue<Key> queue = Queue<Key>();
        for (int i = 0; i < m_m; i++)
            if (m_keys[i] != nullptr) queue.enqueue(*m_keys[i]);
        return queue;
    }

private:
    // must be a power of 2
    static const int INIT_CAPACITY = 4;

    int m_n;           // number of key-value pairs in the symbol table
    int m_m;           // size of linear probing table
    std::vector<ptr<Key>> m_keys;      // the keys
    std::vector<ptr<Value>> m_vals;    // the values

    // hash function for keys - returns value between 0 and m-1
    int hash_textbook(Key key) const
    {
        return (key.hashCode() & 0x7fffffff) % m_m;
    }

    // hash function for keys - returns value between 0 and m-1 (assumes m is a power of 2)
    // (from Java 7 implementation, protects against poor quality hashCode() implementations)
    int hash(Key key) const
    {
        int h = std::hash<Key>{}(key);
        uint32_t uh = (uint32_t) h;
        h ^= (uh >> 20) ^ (uh >> 12) ^ (uh >> 7) ^ (uh >> 4);
        return h & (m_m-1);
    }

    // resizes the hash table to the given capacity by re-hashing all of the keys
    void resize(int capacity)
    {
        LinearProbingHashST<Key, Value> temp = LinearProbingHashST<Key, Value>(capacity);
        for (int i = 0; i < m_m; i++)
        {
            if (m_keys[i] != nullptr)
            {
                temp.put(*m_keys[i], *m_vals[i]);
            }
        }

        copy_ptrs<Key>(m_keys, temp.m_keys);
        copy_ptrs<Value>(m_vals, temp.m_vals);
        m_m = temp.m_m;
    }

    
    // integrity check - don't check after each put() because
    // integrity not maintained during a call to delete()
    bool check() const
    {

        // check that hash table is at most 50% full
        if (m_m < 2*m_n)
        {
            std::cerr << "Hash table size m = " << m_m << "; array size n = " << m_n << "\n";
            return false;
        }

        // check that each key in table can be found by get()
        for (int i = 0; i < m_m; i++)
        {
            if (m_keys[i] == nullptr) continue;
            else if (get(m_keys[i]) != m_vals[i])
            {
                std::cerr < "get[" << m_keys[i] << "] = " << get(m_keys[i]) << "; vals[i] = " << m_vals[i] << "\n";
                return false;
            }
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
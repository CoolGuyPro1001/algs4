#ifndef BINARYSEARCHST_H
#define BINARYSEARCHST_H

#include "Queue.h"

/******************************************************************************
 *  Compilation:  javac BinarySearchST.java
 *  Execution:    java BinarySearchST
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/31elementary/tinyST.txt
 *
 *  Symbol table implementation with binary search in an ordered array.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % java BinarySearchST < tinyST.txt
 *  A 8
 *  C 4
 *  E 12
 *  H 5
 *  L 11
 *  M 9
 *  P 10
 *  R 3
 *  S 0
 *  X 7
 *
 ******************************************************************************/

/**
 *  The {@code BST} class represents an ordered symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides ordered methods for finding the <em>minimum</em>,
 *  <em>maximum</em>, <em>floor</em>, <em>select</em>, and <em>ceiling</em>.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code null}—setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  <p>
 *  This implementation uses a <em>sorted array</em>.
 *  The <em>put</em> and <em>remove</em> operations take &Theta;(<em>n</em>)
 *  time in the worst case.
 *  The <em>contains</em>, <em>ceiling</em>, <em>floor</em>,
 *  and <em>rank</em> operations take &Theta;(log <em>n</em>) time in the worst
 *  case.
 *  The <em>size</em>, <em>is-empty</em>, <em>minimum</em>, <em>maximum</em>,
 *  and <em>select</em> operations take &Theta;(1) time.
 *  Construction takes &Theta;(1) time.
 *  <p>
 *  For alternative implementations of the symbol table API,
 *  see {@link ST}, {@link BST}, {@link SequentialSearchST}, {@link RedBlackBST},
 *  {@link SeparateChainingHashST}, and {@link LinearProbingHashST},
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/31elementary">Section 3.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
template <typename Key, typename Value>
class BinarySearchST
{
public:
    /**
     * Initializes an empty symbol table.
     */
    BinarySearchST() : BinarySearchST(INIT_CAPACITY) {}

    /**
     * Initializes an empty symbol table with the specified initial capacity.
     * @param capacity the maximum capacity
     */
    BinarySearchST(int capacity)
    {
        m_keys = std::vector<ptr<Key>>(capacity);
        m_vals = std::vector<ptr<Value>>(capacity);
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
     * Does this symbol table contain the given key?
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    bool contains(Key key)
    {
        return get(key).has_value();
    }

    /**
     * Returns the value associated with the given key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in the symbol table
     *         and {@code nullptr} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key)
    {
        if (is_empty()) return std::optional<Value>();
        int i = rank(key);
        if (i < m_n && *m_keys[i] == key) return std::optional<Value>(*m_vals[i]);
        return std::optional<Value>();
    }

    /**
     * Returns the number of keys in this symbol table strictly less than {@code key}.
     *
     * @param  key the key
     * @return the number of keys in the symbol table strictly less than {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    int rank(Key key)
    {
        int lo = 0, hi = m_n-1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if      (key < *m_keys[mid]) hi = mid - 1;
            else if (key > *m_keys[mid]) lo = mid + 1;
            else return mid;
        }
        return lo;
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
        int i = rank(key);

        // key is already in table
        if (i < m_n && *m_keys[i] == key)
        {
            m_vals[i] = alloc<Value>(val);
            return;
        }

        // insert new key-value pair
        if (m_n == m_keys.size()) resize(2*m_keys.size());

        for (int j = m_n; j > i; j--)
        {
            m_keys[j] = alloc<Key>(*m_keys[j-1]);
            m_vals[j] = alloc<Value>(*m_vals[j-1]);
        }
        m_keys[i] = alloc<Key>(key);
        m_vals[i] = alloc<Value>(val);
        m_n++;

        assert(check());
    }

    /**
     * Removes the specified key and associated value from this symbol table
     * (if the key is in the symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    void delete_key(Key key)
    {
        if (key == nullptr) error("argument to delete() is nullptr");
        if (is_empty()) return;

        // compute rank
        int i = rank(key);

        // key not in table
        if (i == m_n || m_keys[i] != key)
        {
            return;
        }

        for (int j = i; j < m_n-1; j++)
        {
            m_keys[j] = m_keys[j+1];
            m_vals[j] = m_vals[j+1];
        }

        m_n--;
        m_keys[m_n] = nullptr;  // to avoid loitering
        m_vals[m_n] = nullptr;

        // resize if 1/4 full
        if (m_n > 0 && m_n == m_keys.size()/4) resize(m_keys.size()/2);

        assert(check());
    }

    /**
     * Removes the smallest key and associated value from this symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_min()
    {
        if (is_empty()) error("Symbol table underflow error");
        delete_key(min());
    }

    /**
     * Removes the largest key and associated value from this symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_max()
    {
        if (is_empty()) error("Symbol table underflow error");
        delete_key(max());
    }


   /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/

   /**
     * Returns the smallest key in this symbol table.
     *
     * @return the smallest key in this symbol table
     * @throws NoSuchElementException if this symbol table is empty
     */
    Key min()
    {
        if (is_empty()) error("called min() with empty symbol table");
        return *m_keys[0];
    }

    /**
     * Returns the largest key in this symbol table.
     *
     * @return the largest key in this symbol table
     * @throws NoSuchElementException if this symbol table is empty
     */
    Key max()
    {
        if (is_empty()) error("called max() with empty symbol table");
        return *m_keys[m_n-1];
    }

    /**
     * Return the kth smallest key in this symbol table.
     *
     * @param  k the order statistic
     * @return the {@code k}th smallest key in this symbol table
     * @throws IllegalArgumentException unless {@code k} is between 0 and
     *        <em>n</em>–1
     */
    Key select(int k)
    {
        if (k < 0 || k >= size())
        {
            error("called select() with invalid argument: {}", k);
        }
        return *m_keys[k];
    }

    /**
     * Returns the largest key in this symbol table less than or equal to {@code key}.
     *
     * @param  key the key
     * @return the largest key in this symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key floor(Key key)
    {
        if (key == nullptr) error("argument to floor() is nullptr");
        int i = rank(key);
        if (i < m_n && key == m_keys) return m_keys[i];
        if (i == 0) error("argument to floor() is too small");
        else return m_keys[i-1];
    }

    /**
     * Returns the smallest key in this symbol table greater than or equal to {@code key}.
     *
     * @param  key the key
     * @return the smallest key in this symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key ceiling(Key key)
    {
        if (key == nullptr) error("argument to ceiling() is nullptr");
        int i = rank(key);
        if (i == m_n) error("argument to ceiling() is too large");
        else return m_keys[i];
    }

    /**
     * Returns the number of keys in this symbol table in the specified range.
     *
     * @param lo minimum endpoint
     * @param hi maximum endpoint
     * @return the number of keys in this symbol table between {@code lo}
     *         (inclusive) and {@code hi} (inclusive)
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *         is {@code nullptr}
     */
    int size(Key lo, Key hi)
    {
        if (lo == nullptr) error("first argument to size() is nullptr");
        if (hi == nullptr) error("second argument to size() is nullptr");

        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else              return rank(hi) - rank(lo);
    }

    /**
     * Returns all keys in this symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in this symbol table
     */
    Queue<Key> keys()
    {
        return keys(min(), max());
    }

    /**
     * Returns all keys in this symbol table in the given range,
     * as an {@code Iterable}.
     *
     * @param lo minimum endpoint
     * @param hi maximum endpoint
     * @return all keys in this symbol table between {@code lo}
     *         (inclusive) and {@code hi} (inclusive)
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *         is {@code nullptr}
     */
    Queue<Key> keys(Key lo, Key hi)
    {
        Queue<Key> queue = Queue<Key>();
        if (lo > hi) return queue;
        for (int i = rank(lo); i < rank(hi); i++)
            queue.enqueue(*m_keys[i]);
        if (contains(hi)) queue.enqueue(*m_keys[rank(hi)]);
        return queue;
    }

private:
    static const int INIT_CAPACITY = 2;
    std::vector<ptr<Key>> m_keys;
    std::vector<ptr<Value>> m_vals;
    int m_n = 0;

    // resize the underlying arrays
    void resize(int capacity)
    {
        assert(capacity >= m_n);

        m_keys.resize(capacity);
        m_vals.resize(capacity);
    }


   /***************************************************************************
    *  Check internal invariants.
    ***************************************************************************/

    bool check()
    {
        return is_sorted() && rank_check();
    }

    // are the items in the array in ascending order?
    bool is_sorted()
    {
        for (int i = 1; i < size(); i++)
            if (*m_keys[i] < *m_keys[i-1]) return false;
        return true;
    }

    // check that rank(select(i)) = i
    bool rank_check()
    {
        for (int i = 0; i < size(); i++)
            if (i != rank(select(i))) return false;
        for (int i = 0; i < size(); i++)
            if (*m_keys[i] != select(rank(*m_keys[i]))) return false;
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
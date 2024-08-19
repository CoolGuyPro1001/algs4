#ifndef MAXPQ_H
#define MAXPQ_H

/******************************************************************************
 *  Compilation:  javac MaxPQ.java
 *  Execution:    java MaxPQ < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/24pq/tinyPQ.txt
 *
 *  Generic max priority queue implementation with a binary heap.
 *  Can be used with a comparator instead of the natural order,
 *  but the generic Key type must still be Comparable.
 *
 *  % java MaxPQ < tinyPQ.txt
 *  Q X P (6 left on pq)
 *
 *  We use a one-based array to simplify parent and child calculations.
 *
 *  Can be optimized by replacing full exchanges with half exchanges
 *  (ala insertion sort).
 *
 ******************************************************************************/

/**
 *  The {@code MaxPQ} class represents a priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-maximum</em>
 *  operations, along with methods for peeking at the maximum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a <em>binary heap</em>.
 *  The <em>insert</em> and <em>delete-the-maximum</em> operations take
 *  &Theta;(log <em>n</em>) amortized time, where <em>n</em> is the number
 *  of elements in the priority queue. This is an amortized bound
 *  (and not a worst-case bound) because of array resizing operations.
 *  The <em>min</em>, <em>size</em>, and <em>is-empty</em> operations take
 *  &Theta;(1) time in the worst case.
 *  Construction takes time proportional to the specified capacity or the
 *  number of items used to initialize the data structure.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Key> the generic type of key on this priority queue
 */

template <typename Key>
class MaxPQ
{
public:
    /**
     * Initializes an empty priority queue with the given initial capacity.
     *
     * @param  initCapacity the initial capacity of this priority queue
     */
    MaxPQ(int initCapacity)
    {
        m_pq = std::vector<Key>(initCapacity + 1);
        m_n = 0;
    }

    /**
     * Initializes an empty priority queue.
     */
    MaxPQ()
    {
        MaxPQ(1);
    }

    /**
     * Initializes an empty priority queue with the given initial capacity,
     * using the given comparator.
     *
     * @param  init_capacity the initial capacity of this priority queue
     * @param  cmp the order in which to compare the keys
     */
    MaxPQ(int init_capacity, bool(*cmp)(Key, Key))
    {
        m_cmp = cmp;
        m_pq = std::vector<Key>(init_capacity + 1);
        m_n = 0;
    }

    /**
     * Initializes an empty priority queue using the given comparator.
     *
     * @param  cmp the order in which to compare the keys
     */
    MaxPQ(bool(*cmp)(Key, Key))
    {
        MaxPQ(1, cmp);
    }

    /**
     * Initializes a priority queue from the array of keys.
     * Takes time proportional to the number of keys, using sink-based heap construction.
     *
     * @param  keys the array of keys
     */
    MaxPQ(std::vector<Key> keys)
    {
        m_n = keys.size();
        m_pq = std::vector<Key>(keys.size() + 1);
        for (int i = 0; i < m_n; i++)
            m_pq[i+1] = keys[i];
        for (int k = m_n/2; k >= 1; k--)
            sink(k);
        assert(is_max_heap());
    }

    /**
     * Returns true if this priority queue is empty.
     *
     * @return {@code true} if this priority queue is empty;
     *         {@code false} otherwise
     */
    bool is_empty() const
    {
        return m_n == 0;
    }

    /**
     * Returns the number of keys on this priority queue.
     *
     * @return the number of keys on this priority queue
     */
    int size() const
    {
        return m_n;
    }

    /**
     * Returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    Key max() const
    {
        if (is_empty()) error("Priority queue underflow");
        return m_pq[1];
    }

    /**
     * Adds a new key to this priority queue.
     *
     * @param  x the new key to add to this priority queue
     */
    void insert(Key x)
    {
        // double size of array if necessary
        if (m_n == m_pq.size() - 1) resize(2 * m_pq.size());

        // add x, and percolate it up to maintain heap invariant
        m_pq[++m_n] = x;
        swim(m_n);
        assert(is_max_heap());
    }

    /**
     * Removes and returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    Key del_max()
    {
        if (is_empty()) error("Priority queue underflow");
        Key max = m_pq[1];
        exch(1, m_n--);
        sink(1);
        m_pq[m_n+1] = nullptr;     // to avoid loitering and help with garbage collection
        if ((m_n > 0) && (m_n == (m_pq.size() - 1) / 4)) resize(m_pq.size() / 2);
        assert(is_max_heap());
        return max;
    }

   /***************************************************************************
    * Iterator.
    ***************************************************************************/

   //TODO
    /*
     * Returns an iterator that iterates over the keys on this priority queue
     * in descending order.
     * The iterator doesn't implement {@code remove()} since it's optional.
     *
     * @return an iterator that iterates over the keys in descending order
     
    Iterator<Key> iterator();*/

private:
    std::vector<Key> m_pq;    // store items at indices 1 to n
    int m_n;                  // number of items on priority queue
    bool(*m_cmp)(Key, Key);   // optional comparator

    // resize the underlying array to have the given capacity
    void resize(int capacity)
    {
        assert(capacity > m_n);
        std::vector<Key> temp = std::vector<Key>(capacity);
        for (int i = 1; i <= m_n; i++)
        {
            temp[i] = m_pq[i];
        }
        m_pq = temp;
    }

    /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/

    void swim(int k)
    {
        while (k > 1 && less(k/2, k))
        {
            exch(k/2, k);
            k = k/2;
        }
    }

    void sink(int k)
    {
        while (2*k <= m_n)
        {
            int j = 2*k;
            if (j < m_n && less(j, j+1)) j++;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }


    /***************************************************************************
    * Helper functions for compares and swaps.
    ***************************************************************************/
    bool less(int i, int j) const
    {
        if (m_cmp == nullptr)
        {
            return m_pq[i] < m_pq[j];
        }
        else
        {
            return (*m_cmp)(m_pq[i], m_pq[j]);
        }
    }

    void exch(int i, int j)
    {
        Key swap = m_pq[i];
        m_pq[i] = m_pq[j];
        m_pq[j] = swap;
    }

    // is pq[1..n] a max heap?
    bool is_max_heap() const
    {
        for (int i = 1; i <= m_n; i++)
        {
            if (m_pq[i] == nullptr) return false;
        }
        for (int i = m_n+1; i < m_pq.size(); i++)
        {
            if (m_pq[i] != nullptr) return false;
        }
        if (m_pq[0] != nullptr) return false;
        return is_max_heap_ordered(1);
    }

    // is subtree of pq[1..n] rooted at k a max heap?
    bool is_max_heap_ordered(int k) const
    {
        if (k > m_n) return true;
        int left = 2*k;
        int right = 2*k + 1;
        if (left  <= m_n && less(k, left))  return false;
        if (right <= m_n && less(k, right)) return false;
        return is_max_heap_ordered(left) && is_max_heap_ordered(right);
    }

    /***************************************************************************
    * Iterator.
    ***************************************************************************/

    /*Iterator<Key> iterator()
    {
        return new HeapIterator();
    }*/

    struct HeapIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Key;
        using pointer           = Key*;  // or also value_type*
        using reference         = Key&;  // or also value_type&

        HeapIterator(MaxPQ<Key> copy, pointer ptr) : m_ptr(ptr)
        {
            m_copy = copy;
            //if (cmp == nullptr) copy = new MaxPQ<Key>(size());
            //else                    copy = new MaxPQ<Key>(size(), cmp);
            //for (int i = 1; i <= n; i++)
            //    copy.insert(pq[i]);
        }

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        HeapIterator& operator++()
        {
            //if (!hasNext()) error();
            //return copy.delMax();
            m_ptr++;
            return *this;
        }  

        // Postfix increment
        HeapIterator operator++(int)
        {
            HeapIterator tmp = *this; 
            ++(*this);
            return tmp;
        }

        bool operator== (const HeapIterator& other)
        {
            return m_copy.is_empty() == other.m_copy.is_empty();
        };

        bool operator!= (const HeapIterator& other)
        {
            return m_copy.is_empty() != other.m_copy.is_empty();
        };
        
    private:
        pointer m_ptr;
        // create a new pq
        MaxPQ<Key> m_copy;
    };
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
 *  it under the terms of the GNU General License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General License for more details.
 *
 *  You should have received a copy of the GNU General License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif
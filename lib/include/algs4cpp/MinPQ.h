#ifndef MINPQ_H
#define MINPQ_H

/******************************************************************************
 *  Compilation:  javac MinPQ.java
 *  Execution:    java MinPQ < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/24pq/tinyPQ.txt
 *
 *  Generic min priority queue implementation with a binary heap.
 *  Can be used with a comparator instead of the natural order.
 *
 *  % java MinPQ < tinyPQ.txt
 *  E A E (6 left on pq)
 *
 *  We use a one-based array to simplify parent and child calculations.
 *
 *  Can be optimized by replacing full exchanges with half exchanges
 *  (ala insertion sort).
 *
 ******************************************************************************/

/**
 *  The {@code MinPQ} class represents a priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-minimum</em>
 *  operations, along with methods for peeking at the minimum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a <em>binary heap</em>.
 *  The <em>insert</em> and <em>delete-the-minimum</em> operations take
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
class MinPQ
{
public:
    /**
     * Initializes an empty priority queue with the given initial capacity.
     *
     * @param  init_capacity the initial capacity of this priority queue
     */
    MinPQ(int init_capacity)
    {
        m_pq = std::vector<ptr<Key>>(init_capacity + 1);
        m_n = 0;
        m_cmp = nullptr;
    }

    /**
     * Initializes an empty priority queue.
     */
    MinPQ() : MinPQ(1)
    {
    }

    /**
     * Initializes an empty priority queue with the given initial capacity,
     * using the given comparator.
     *
     * @param  init_capacity the initial capacity of this priority queue
     * @param  cmp the order in which to compare the keys
     */
    MinPQ(int init_capacity, bool (*cmp)(Key*, Key*))
    {
        m_cmp = cmp;
        m_pq = std::vector<ptr<Key>>(init_capacity + 1);
        m_n = 0;
    }

    /**
     * Initializes an empty priority queue using the given comparator.
     *
     * @param  cmp the order in which to compare the keys
     */
    MinPQ(bool (*cmp)(Key*, Key*)) : MinPQ(1, cmp)
    {
    }

    /**
     * Initializes a priority queue from the array of keys.
     * <p>
     * Takes time proportional to the number of keys, using sink-based heap construction.
     *
     * @param  keys the array of keys
     */
    MinPQ(std::vector<ptr<Key>> keys)
    {
        m_n = keys.size();
        m_cmp = nullptr;
        m_pq = std::vector<ptr<Key>>(keys.size() + 1);
        std::copy(keys.begin(), keys.end(), m_pq.begin() + 1);

        for (int k = m_n/2; k >= 1; k--)
            sink(k);
        assert(is_min_heap());
    }

    /**
     * Copy constructor.
     * 
     * @param other the MaxPQ to copy from
     */
    MinPQ(const MinPQ<Key>& other) : 
        m_n(other.m_n), m_cmp(other.m_cmp) 
    {
        m_pq = std::vector<ptr<Key>>();
        copy_ptrs<Key>(m_pq, other.m_pq);
    }
        
    /**
     * Assigment operator.
     * 
     * @param other the MaxPQ to assign from
     */
    MinPQ& operator=(const MinPQ<Key>& other)
    {
        m_n = other.m_n;
        m_cmp = other.m_cmp;
        m_pq = std::vector<ptr<Key>>();
        copy_ptrs<Key>(m_pq, other.m_pq);
        return *this;
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
     * Returns a smallest key on this priority queue.
     *
     * @return a smallest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    Key min() const
    {
        if (is_empty()) error("Priority queue underflow");
        return m_pq[1];
    }

    /**
     * Adds a new key to this priority queue.
     *
     * @param  x the key to add to this priority queue
     */
    void insert(Key x)
    {
        // double size of array if necessary
        if (m_n == m_pq.size() - 1) resize(2 * m_pq.size());

        // add x, and percolate it up to maintain heap invariant
        m_pq[++m_n] = alloc<Key>(x);
        swim(m_n);
        assert(is_min_heap());
    }

    /**
     * Removes and returns a smallest key on this priority queue.
     *
     * @return a smallest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    Key del_min()
    {
        if (is_empty()) error("Priority queue underflow");
        Key min = *(m_pq[1]);
        exch(1, m_n--);
        sink(1);
        m_pq[m_n+1].reset();     // to avoid loitering and help with garbage collection
        if ((m_n > 0) && (m_n == (m_pq.size() - 1) / 4)) resize(m_pq.size() / 2);
        assert(is_min_heap());
        return min;
    }

private:
    std::vector<ptr<Key>> m_pq;       // store items at indices 1 to n
    int m_n;                     // number of items on priority queue
    bool(*m_cmp)(Key*, Key*);      // optional comparator

    // resize the underlying array to have the given capacity
    void resize(int capacity)
    {
        assert(capacity > m_n);
        m_pq.resize(capacity);
    }

   /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/

    void swim(int k)
    {
        while (k > 1 && greater(k/2, k))
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
            if (j < m_n && greater(j, j+1)) j++;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

   /***************************************************************************
    * Helper functions for compares and swaps.
    ***************************************************************************/
    bool greater(int i, int j) const
    {
        if (m_cmp == nullptr)
        {
            return *(m_pq[i]) > *(m_pq[j]);
        }
        else
        {
            return (*m_cmp)(m_pq[i].get(), m_pq[j].get());
        }
    }

    void exch(int i, int j)
    {
        std::swap(m_pq[i], m_pq[j]);
    }

    // is pq[1..n] a min heap?
    bool is_min_heap() const
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
        return is_min_heap_ordered(1);
    }

    // is subtree of pq[1..n] rooted at k a min heap?
    bool is_min_heap_ordered(int k) const
    {
        if (k > m_n) return true;
        int left = 2*k;
        int right = 2*k + 1;
        if (left  <= m_n && greater(k, left))  return false;
        if (right <= m_n && greater(k, right)) return false;
        return is_min_heap_ordered(left) && is_min_heap_ordered(right);
    }


    /***************************************************************************
    * Iterator.
    ***************************************************************************/
    struct HeapIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Key;
        using pointer           = Key*;  // or also value_type*
        using reference         = Key&;  // or also value_type&

        HeapIterator(MinPQ<Key>& min_pq)
        {
            m_copy = min_pq;
            m_ptr = m_copy.m_pq[1].get();
        }

        HeapIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        HeapIterator& operator++()
        {
            if (m_copy.is_empty()) error("No such element");
            m_copy.del_min();

            if (m_copy.is_empty())
                m_ptr = nullptr;
            else
                m_ptr = m_copy.m_pq[1].get();

            return *this;
        }  

        // Postfix increment
        HeapIterator operator++(int)
        {
            HeapIterator tmp = *this; 
            ++(*this);
            return tmp;
        }

        friend bool operator== (const HeapIterator& a, const HeapIterator& b)
        {
            return a.m_ptr == b.m_ptr;
        };

        friend bool operator!= (const HeapIterator& a, const HeapIterator& b)
        {
            return a.m_ptr != b.m_ptr;
        };
        
    private:
        pointer m_ptr;
        MinPQ<Key> m_copy;
    };

public:
    HeapIterator begin()
    {
        return HeapIterator(*this);
    }

    HeapIterator end()
    {
        return HeapIterator(nullptr);
    }
};

#endif
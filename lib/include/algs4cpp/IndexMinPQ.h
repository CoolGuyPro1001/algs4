#ifndef INDEXMINPQ_H
#define INDEXMINPQ_H

/******************************************************************************
 *  Compilation:  javac IndexMinPQ.java
 *  Execution:    java IndexMinPQ
 *  Dependencies: StdOut.java
 *
 *  Minimum-oriented indexed PQ implementation using a binary heap.
 *
 ******************************************************************************/

/**
 *  The {@code IndexMinPQ} class represents an indexed priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-minimum</em>
 *  operations, along with <em>delete</em> and <em>change-the-key</em>
 *  methods. In order to let the client refer to keys on the priority queue,
 *  an integer between {@code 0} and {@code maxN - 1}
 *  is associated with each key—the client uses this integer to specify
 *  which key to delete or change.
 *  It also supports methods for peeking at the minimum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a binary heap along with an array to associate
 *  keys with integers in the given range.
 *  The <em>insert</em>, <em>delete-the-minimum</em>, <em>delete</em>,
 *  <em>change-key</em>, <em>decrease-key</em>, and <em>increase-key</em>
 *  operations take &Theta;(log <em>n</em>) time in the worst case,
 *  where <em>n</em> is the number of elements in the priority queue.
 *  Construction takes time proportional to the specified capacity.
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
class IndexMinPQ
{
public:
    /**
     * Default Constructor
     */
    IndexMinPQ()
    {
        m_max_n = 0;
        m_n = 0;
        m_keys = std::vector<ptr<Key>>();
        m_pq   = std::vector<int>();
        m_qp   = std::vector<int>();
    }

    /**
     * Initializes an empty indexed priority queue with indices between {@code 0}
     * and {@code m_max_n - 1}.
     *
     * @param  max_n the keys on this priority queue are index from {@code 0} to {@code max_n - 1}
     * @throws IllegalArgumentException if {@code max_n < 0}
     */
    IndexMinPQ(int max_n)
    {
        if (max_n < 0) error("illegal argument exception");
        m_max_n = max_n;
        m_n = 0;
        m_keys = std::vector<ptr<Key>>(m_max_n + 1);    // make this of length m_max_n??
        m_pq   = std::vector<int>(m_max_n + 1);
        m_qp   = std::vector<int>(m_max_n + 1);         // make this of length m_max_n??
        for (int i = 0; i <= m_max_n; i++)
            m_qp[i] = -1;
    }
    
    /**
     * Copy constructor.
     * 
     * @param other the IndexMaxPQ to copy from
     */
    IndexMinPQ(const IndexMinPQ<Key>& other) : 
        m_n(other.m_n), m_max_n(other.m_max_n), m_pq(other.m_pq), m_qp(other.m_qp)
    {
        m_keys = std::vector<ptr<Key>>();
        copy_ptrs<Key>(m_keys, other.m_keys);
    }
        
    /**
     * Assigment operator.
     * 
     * @param other the IndexMaxPQ to assign from
     */
    IndexMinPQ& operator=(const IndexMinPQ<Key>& other)
    {
        m_n = other.m_n;
        m_max_n = other.m_max_n;
        m_pq = other.m_pq;
        m_qp = other.m_qp;
        m_keys = std::vector<ptr<Key>>();
        copy_ptrs<Key>(m_keys, other.m_keys);
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
     * Is {@code i} an index on this priority queue?
     *
     * @param  i an index
     * @return {@code true} if {@code i} is an index on this priority queue;
     *         {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     */
    bool contains(int i) const
    {
        validate_index(i);
        return m_qp[i] != -1;
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
     * Associate key with index i.
     *
     * @param  i an index
     * @param  key the key to associate with index {@code i}
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     * @throws IllegalArgumentException if there already is an item
     *         associated with index {@code i}
     */
    void insert(int i, Key key)
    {
        validate_index(i);
        if (contains(i)) error("index is already in the priority queue");
        m_n++;
        m_qp[i] = m_n;
        m_pq[m_n] = i;
        m_keys[i] = alloc<Key>(key);
        swim(m_n);
    }

    /**
     * Returns an index associated with a minimum key.
     *
     * @return an index associated with a minimum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    int min_index() const
    {
        if (m_n == 0) error("Priority queue underflow");
        return m_pq[1];
    }

    /**
     * Returns a minimum key.
     *
     * @return a minimum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    Key min_key() const
    {
        if (m_n == 0) error("Priority queue underflow");
        return *(m_keys[m_pq[1]]);
    }

    /**
     * Removes a maximum key and returns its associated index.
     *
     * @return an index associated with a maximum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    int del_min()
    {
        if (m_n == 0) error("Priority queue underflow");
        int min = m_pq[1];
        exch(1, m_n--);
        sink(1);

        assert(m_pq[m_n+1] == min);
        m_qp[min] = -1;             // delete
        m_keys[min] = nullptr;      // to help with garbage collection
        m_pq[m_n+1] = -1;           // not needed
        return min;
    }

    /**
     * Returns the key associated with index {@code i}.
     *
     * @param  i the index of the key to return
     * @return the key associated with index {@code i}
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    Key key_of(int i) const
    {
        validate_index(i);
        if (!contains(i))
        {
            error("index is not in the priority queue");
            return nullptr;
        }
        else return *(m_keys[i]);
    }

    /**
     * Change the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to change
     * @param  key change the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     */
    void change_key(int i, Key key)
    {
        validate_index(i);
        if (!contains(i)) error("index is not in the priority queue");
        m_keys[i] = alloc<Key>(key);
        swim(m_qp[i]);
        swim(m_qp[i]);
    }

    /**
     * Increase the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to increase
     * @param  key increase the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     * @throws IllegalArgumentException if {@code key <= keyOf(i)}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void increase_key(int i, Key key)
    {
        validate_index(i); if (!contains(i)) error("index is not in the priority queue");
        if (*(m_keys[i]) == key)
            error("Calling increaseKey() with a key equal to the key in the priority queue");
        if (*(m_keys[i]) > key)
            error("Calling increaseKey() with a key that is strictly less than the key in the priority queue");

        m_keys[i] = alloc<Key>(key);
        sink(m_qp[i]);
    }

    /**
     * Decrease the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to decrease
     * @param  key decrease the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     * @throws IllegalArgumentException if {@code key >= keyOf(i)}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void decrease_key(int i, Key key)
    {
        validate_index(i);
        if (!contains(i)) error("index is not in the priority queue");
        if (*(m_keys[i]) == key)
            error("Calling decrease_key() with a key equal to the key in the priority queue");
        if (*(m_keys[i]) < key)
            error("Calling decrease_key() with a key that is strictly greater than the key in the priority queue");
        m_keys[i] = alloc<Key>(key);
        sink(m_qp[i]);
    }

    /**
     * Remove the key on the priority queue associated with index {@code i}.
     *
     * @param  i the index of the key to remove
     * @throws IllegalArgumentException unless {@code 0 <= i < m_max_n}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void delete_key(int i)
    {
        validate_index(i);
        if (!contains(i)) error("index is not in the priority queue");
        int index = m_qp[i];
        exch(index, m_n--);
        swim(index);
        sink(index);
        m_keys[i] = nullptr;
        m_qp[i] = -1;
    }

private:
    int m_max_n;        // maximum number of elements on PQ
    int m_n;           // number of elements on PQ
    std::vector<int> m_pq;        // binary heap using 1-based indexing
    std::vector<int> m_qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
    std::vector<ptr<Key>> m_keys;      // keys[i] = priority of i

    // throw an IllegalArgumentException if i is an invalid index
    void validate_index(int i) const
    {
        if (i < 0) error("index is negative: {}", i);
        if (i >= m_max_n) error("index >= capacity: {}", i);
    }

   /***************************************************************************
    * General helper functions.
    ***************************************************************************/
    bool greater(int i, int j) const
    {
        return *(m_keys[m_pq[i]]) > *(m_keys[m_pq[j]]);
    }

    void exch(int i, int j)
    {
        std::swap(m_pq[i], m_pq[j]);
        m_qp[m_pq[i]] = i;
        m_qp[m_pq[j]] = j;
    }


   /***************************************************************************
    * Heap helper functions.
    ***************************************************************************/
    void swim(int k)
    {
        while (k > 1 && greater(k/2, k))
        {
            exch(k, k/2);
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
    * Iterator.
    ***************************************************************************/
    struct HeapIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;  // or also value_type*
        using reference         = int&;  // or also value_type&

        HeapIterator(IndexMinPQ<Key>& min_pq)
        {
            m_copy = min_pq;
            m_ptr = &m_copy.m_pq[1];
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
                m_ptr = &m_copy.m_pq[1];

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
        IndexMinPQ<Key> m_copy;
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
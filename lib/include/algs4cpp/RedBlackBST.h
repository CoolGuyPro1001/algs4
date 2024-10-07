#ifndef REDBLACKBST_H
#define REDBLACKBST_H

#include "Queue.h"
#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac RedBlackBST.java
 *  Execution:    java RedBlackBST < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/33balanced/tinyST.txt
 *
 *  A symbol table implemented using a left-leaning red-black BST.
 *  This is the 2-3 version.
 *
 *  Note: commented out assertions because DrJava now enables assertions
 *        by default.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % java RedBlackBST < tinyST.txt
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

// BST helper node data type
template <typename Key, typename Value>
struct RBNode
{
    Key key;           // key
    Value val;         // associated data
    ptr<RBNode<Key, Value>> left, right;  // links to left and right subtrees
    bool color;     // color of parent link
    int size;          // subtree count

    RBNode(Key key, Value val, bool color, int size)
    {
        this->key = key;
        this->val = val;
        this->color = color;
        this->size = size;
    }
};

/**
 *  The {@code BST} class represents an ordered symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides ordered methods for finding the <em>minimum</em>,
 *  <em>maximum</em>, <em>floor</em>, and <em>ceiling</em>.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code nullptr}—setting the
 *  value associated with a key to {@code nullptr} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  <p>
 *  This implementation uses a <em>left-leaning red-black BST</em>.
 *  The <em>put</em>, <em>get</em>, <em>contains</em>, <em>remove</em>,
 *  <em>minimum</em>, <em>maximum</em>, <em>ceiling</em>, <em>floor</em>,
 *  <em>rank</em>, and <em>select</em> operations each take
 *  &Theta;(log <em>n</em>) time in the worst case, where <em>n</em> is the
 *  number of key-value pairs in the symbol table.
 *  The <em>size</em>, and <em>is-empty</em> operations take &Theta;(1) time.
 *  The <em>keys</em> methods take
 *  <em>O</em>(log <em>n</em> + <em>m</em>) time, where <em>m</em> is
 *  the number of keys returned by the iterator.
 *  Construction takes &Theta;(1) time.
 *  <p>
 *  For alternative implementations of the symbol table API, see {@link ST},
 *  {@link BinarySearchST}, {@link SequentialSearchST}, {@link BST},
 *  {@link SeparateChainingHashST}, {@link LinearProbingHashST}, and
 *  {@link AVLTreeST}.
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/33balanced">Section 3.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Key, typename Value>
class RedBlackBST
{
public:
    /**
     * Initializes an empty symbol table.
     */
    RedBlackBST() {}

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() const
    {
        return size(m_root);
    }

    /**
     * Is this symbol table empty?
     * @return {@code true} if this symbol table is empty and {@code false} otherwise
     */
    bool is_empty() const
    {
        return m_root == nullptr;
    }

    /***************************************************************************
    *  Standard BST search.
    ***************************************************************************/

    /**
     * Returns the value associated with the given key.
     * @param key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code nullptr} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key) const
    {
        return get(m_root.get(), key);
    }

    /**
     * Does this symbol table contain the given key?
     * @param key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *     {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    bool contains(Key key) const
    {
        return get(key) != nullptr;
    }

    /***************************************************************************
    *  Red-black tree insertion.
    ***************************************************************************/

    /**
     * Inserts the specified key-value pair into the symbol table, overwriting the old
     * value with the new value if the symbol table already contains the specified key.
     * Deletes the specified key (and its associated value) from this symbol table
     * if the specified value is {@code nullptr}.
     *
     * @param key the key
     * @param val the value
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    void put(Key key, Value val)
    {
        m_root = put(std::move(m_root), key, val);
        m_root->color = BLACK;
    }

    /***************************************************************************
    *  Red-black tree deletion.
    ***************************************************************************/

    /**
     * Removes the smallest key and associated value from the symbol table.
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_min()
    {
        if (is_empty()) error("BST underflow");

        // if both children of root are black, set m_root to red
        if (!is_red(m_root->left) && !is_red(m_root->right))
            m_root->color = RED;

        m_root = delete_min(m_root);
        if (!is_empty()) m_root->color = BLACK;
    }

    /**
     * Removes the largest key and associated value from the symbol table.
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_max()
    {
        if (is_empty()) error("BST underflow");

        // if both children of root are black, set m_root to red
        if (!is_red(m_root->left) && !is_red(m_root->right))
            m_root->color = RED;

        m_root = delete_max(m_root);
        if (!is_empty()) m_root->color = BLACK;
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

        // if both children of root are black, set m_root to red
        if (!is_red(m_root->left) && !is_red(m_root->right))
            m_root->color = RED;

        m_root = delete_key(m_root, key);
        if (!is_empty()) m_root->color = BLACK;
    }

    /***************************************************************************
    *  Utility functions.
    ***************************************************************************/

    /**
     * Returns the height of the BST (for debugging).
     * @return the height of the BST (a 1-node tree has height 0)
     */
    int height() const
    {
        return height(m_root);
    }

    /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/

    /**
     * Returns the smallest key in the symbol table.
     * @return the smallest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key min() const
    {
        if (is_empty()) error("calls min() with empty symbol table");
        return min(m_root.get()).key;
    }

    /**
     * Returns the largest key in the symbol table.
     * @return the largest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key max() const
    {
        if (is_empty()) error("calls max() with empty symbol table");
        return max(m_root.get()).key;
    }

    /**
     * Returns the largest key in the symbol table less than or equal to {@code key}.
     * @param key the key
     * @return the largest key in the symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key floor(Key key) const
    {
        if (key == nullptr) error("argument to floor() is nullptr");
        if (is_empty()) error("calls floor() with empty symbol table");
        RBNode<Key, Value> x = floor(m_root, key);
        if (x == nullptr) error("argument to floor() is too small");
        else           return x->key;
    }

    /**
     * Returns the smallest key in the symbol table greater than or equal to {@code key}.
     * @param key the key
     * @return the smallest key in the symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key ceiling(Key key) const
    {
        if (key == nullptr) error("argument to ceiling() is nullptr");
        if (is_empty()) error("calls ceiling() with empty symbol table");
        RBNode<Key, Value> x = ceiling(m_root, key);
        if (x == nullptr) error("argument to ceiling() is too large");
        else           return x->key;
    }

    /**
     * Return the key in the symbol table of a given {@code rank}.
     * This key has the property that there are {@code rank} keys in
     * the symbol table that are smaller. In other words, this key is the
     * ({@code rank}+1)st smallest key in the symbol table.
     *
     * @param  rank the order statistic
     * @return the key in the symbol table of given {@code rank}
     * @throws IllegalArgumentException unless {@code rank} is between 0 and
     *        <em>n</em>–1
     */
    Key select(int rank) const
    {
        if (rank < 0 || rank >= size())
        {
            error("argument to select() is invalid: {}", rank);
        }
        return select(m_root, rank);
    }

    /**
     * Return the number of keys in the symbol table strictly less than {@code key}.
     * @param key the key
     * @return the number of keys in the symbol table strictly less than {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    int rank(Key key) const
    {
        if (key == nullptr) error("argument to rank() is nullptr");
        return rank(key, m_root);
    }

    /***************************************************************************
    *  Range count and range search.
    ***************************************************************************/

    /**
     * Returns all keys in the symbol table in ascending order as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     * @return all keys in the symbol table in ascending order
     */
    Queue<Key> keys() const
    {
        if (is_empty()) return Queue<Key>();
        return keys(min(), max());
    }

    /**
     * Returns all keys in the symbol table in the given range in ascending order,
     * as an {@code Iterable}.
     *
     * @param  lo minimum endpoint
     * @param  hi maximum endpoint
     * @return all keys in the symbol table between {@code lo}
     *    (inclusive) and {@code hi} (inclusive) in ascending order
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *    is {@code nullptr}
     */
    Queue<Key> keys(Key lo, Key hi) const
    {
        Queue<Key> queue = Queue<Key>();
        // if (is_empty() || lo.compareTo(hi) > 0) return queue;
        keys(m_root.get(), queue, lo, hi);
        return queue;
    }

    /**
     * Returns the number of keys in the symbol table in the given range.
     *
     * @param  lo minimum endpoint
     * @param  hi maximum endpoint
     * @return the number of keys in the symbol table between {@code lo}
     *    (inclusive) and {@code hi} (inclusive)
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *    is {@code nullptr}
     */
    int size(Key lo, Key hi) const
    {
        if (lo == nullptr) error("first argument to size() is nullptr");
        if (hi == nullptr) error("second argument to size() is nullptr");

        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else              return rank(hi) - rank(lo);
    }

private:
    static constexpr bool RED = true;
    static constexpr bool BLACK = false;

    ptr<RBNode<Key, Value>> m_root;     // root of the BST

   /***************************************************************************
    *  RBNode helper methods.
    ***************************************************************************/

    // is node x red; false if x is nullptr ?
    bool is_red(RBNode<Key, Value>* x) const
    {
        if (x == nullptr) return false;
        return x->color == RED;
    }

    // number of node in subtree rooted at x; 0 if x is nullptr
    int size(RBNode<Key, Value>* x) const
    {
        if (x == nullptr) return 0;
        return x->size;
    }

    // value associated with the given key in subtree rooted at x; nullptr if no such key
    std::optional<Value> get(RBNode<Key, Value>* x, Key key) const
    {
        while (x != nullptr)
        {
            if (key < x->key)       x = x->left.get();
            else if (key > x->key)  x = x->right.get();
            else                    return std::optional<Value>(x->val);
        }
        return std::optional<Value>();
    }

    // insert the key-value pair in the subtree rooted at h
    ptr<RBNode<Key, Value>> put(ptr<RBNode<Key, Value>> h, Key key, Value val)
    {
        if (h == nullptr) return std::make_unique<RBNode<Key, Value>>(key, val, RED, 1);

        if (key < h->key)       h->left = put(std::move(h->left), key, val);
        else if (key > h->key)  h->right = put(std::move(h->right), key, val);
        else                    h->val = val;

        // fix-up any right-leaning links
        if (is_red(h->right.get()) && !is_red(h->left.get()))      h = rotate_left(std::move(h));
        if (is_red(h->left.get())  &&  is_red(h->left->left.get())) h = rotate_right(std::move(h));
        if (is_red(h->left.get())  &&  is_red(h->right.get()))     flip_colors(h.get());
        h->size = size(h->left.get()) + size(h->right.get()) + 1;

        return h;
    }

    // delete the key-value pair with the minimum key rooted at h
    RBNode<Key, Value> delete_min(RBNode<Key, Value> h)
    {
        if (h->left == nullptr)
            return nullptr;

        if (!is_red(h->left) && !is_red(h->left->left))
            h = move_red_left(h);

        h->left = delete_min(h->left);
        return balance(h);
    }

    /***************************************************************************
    *  Red-black tree deletion.
    ***************************************************************************/

    // delete the key-value pair with the maximum key rooted at h
    RBNode<Key, Value> delete_max(RBNode<Key, Value> h)
    {
        if (is_red(h->left))
            h = rotate_right(h);

        if (h->right == nullptr)
            return nullptr;

        if (!is_red(h->right) && !is_red(h->right->left))
            h = move_red_right(h);

        h->right = delete_max(h->right);

        return balance(h);
    }

    // delete the key-value pair with the given key rooted at h
    RBNode<Key, Value> delete_key(RBNode<Key, Value> h, Key key)
    {
        if (key.compareTo(h->key) < 0)
        {
            if (!is_red(h->left) && !is_red(h->left->left))
                h = move_red_left(h);
            h->left = delete_key(h->left, key);
        }
        else
        {
            if (is_red(h->left))
                h = rotate_right(h);
            if (key.compareTo(h->key) == 0 && (h->right == nullptr))
                return nullptr;
            if (!is_red(h->right) && !is_red(h->right->left))
                h = move_red_right(h);
            if (key == h->key)
            {
                RBNode<Key, Value> x = min(h->right);
                h->key = x->key;
                h->val = x->val;
                // h->val = get(h->right, min(h->right).key);
                // h->key = min(h->right).key;
                h->right = delete_min(h->right);
            }
            else h->right = delete_key(h->right, key);
        }
        return balance(h);
    }

   /***************************************************************************
    *  Red-black tree helper functions.
    ***************************************************************************/

    // make a left-leaning link lean to the right
    ptr<RBNode<Key, Value>> rotate_right(ptr<RBNode<Key, Value>> h)
    {
        assert((h != nullptr) && is_red(h->left.get()));
        ptr<RBNode<Key, Value>> x = std::move(h->left);
        h->left = std::move(x->right);
        x->right = std::move(h);
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = size(h->left.get()) + size(h->right.get()) + 1;
        return x;
    }

    // make a right-leaning link lean to the left
    ptr<RBNode<Key, Value>> rotate_left(ptr<RBNode<Key, Value>> h)
    {
        assert((h != nullptr) && is_red(h->right.get()));
        ptr<RBNode<Key, Value>> x = std::move(h->right);
        h->right = std::move(x->left);
        x->left = std::move(h);
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = size(h->left.get()) + size(h->right.get()) + 1;
        return x;
    }

    // flip the colors of a node and its two children
    void flip_colors(RBNode<Key, Value>* h) const
    {
        // h must have opposite color of its two children
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }

    // Assuming that h is red and both h->left and h->left->left
    // are black, make h->left or one of its children red.
    RBNode<Key, Value> move_red_left(RBNode<Key, Value> h) const
    {
        flip_colors(h);
        if (is_red(h->right->left))
        {
            h->right = rotate_right(h->right);
            h = rotate_left(h);
            flip_colors(h);
        }
        return h;
    }

    // Assuming that h is red and both h->right and h->right->left
    // are black, make h->right or one of its children red.
    RBNode<Key, Value> move_red_right(RBNode<Key, Value> h) const
    {
        flip_colors(h);
        if (is_red(h->left->left))
        {
            h = rotate_right(h);
            flip_colors(h);
        }
        return h;
    }

    // restore red-black tree invariant
    RBNode<Key, Value> balance(RBNode<Key, Value> h) const
    {
        if (is_red(h->right) && !is_red(h->left))    h = rotate_left(h);
        if (is_red(h->left) && is_red(h->left->left)) h = rotate_right(h);
        if (is_red(h->left) && is_red(h->right))     flip_colors(h);

        h->size = size(h->left) + size(h->right) + 1;
        return h;
    }

   /***************************************************************************
    *  Utility functions.
    ***************************************************************************/

    int height(RBNode<Key, Value>* x) const
    {
        if (x == nullptr) return -1;
        return 1 + std::max(height(x->left.get()), height(x->right.get()));
    }

   /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/

    // the smallest key in subtree rooted at x; nullptr if no such key
    RBNode<Key, Value>& min(RBNode<Key, Value>* x) const
    {
        // assert x != nullptr;
        if (x->left == nullptr) return *x;
        else                return min(x->left.get());
    }

    // the largest key in the subtree rooted at x; nullptr if no such key
    RBNode<Key, Value>& max(RBNode<Key, Value>* x) const
    {
        // assert x != nullptr;
        if (x->right == nullptr) return *x;
        else                 return max(x->right.get());
    }

    // the largest key in the subtree rooted at x less than or equal to the given key
    RBNode<Key, Value> floor(RBNode<Key, Value>* x, Key key) const
    {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key)  return floor(x->left.get(), key);
        RBNode<Key, Value> t = floor(x->right.get(), key);
        if (t != nullptr) return t;
        else           return x;
    }

    // the smallest key in the subtree rooted at x greater than or equal to the given key
    RBNode<Key, Value> ceiling(RBNode<Key, Value>* x, Key key) const
    {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key > x->key)  return ceiling(x->right.get(), key);
        RBNode<Key, Value> t = ceiling(x->left.get(), key);
        if (t != nullptr) return t;
        else           return x;
    }

    // Return key in BST rooted at x of given rank.
    // Precondition: rank is in legal range.
    Key select(RBNode<Key, Value>* x, int rank) const
    {
        if (x == nullptr) return nullptr;
        int left_size = size(x->left);
        if      (left_size > rank) return select(x->left.get(),  rank);
        else if (left_size < rank) return select(x->right.get(), rank - left_size - 1);
        else                      return x->key;
    }

    // number of keys less than key in the subtree rooted at x
    int rank(Key key, RBNode<Key, Value>* x) const
    {
        if (x == nullptr) return 0;
        if      (key < x->key) return rank(key, x->left.get());
        else if (key > x->key) return 1 + size(x->left) + rank(key, x->right.get());
        else              return size(x->left);
    }

   /***************************************************************************
    *  Range count and range search.
    ***************************************************************************/
    
    // add the keys between lo and hi in the subtree rooted at x
    // to the queue
    void keys(RBNode<Key, Value>* x, Queue<Key>& queue, Key lo, Key hi) const
    {
        if (x == nullptr) return;
        if (lo < x->key) keys(x->left.get(), queue, lo, hi);
        if (lo <= x->key && hi >= x->key) queue.enqueue(x->key);
        if (hi > x->key) keys(x->right.get(), queue, lo, hi);
    }

   /***************************************************************************
    *  Check integrity of red-black tree data structure.
    ***************************************************************************/
    bool check() const
    {
        if (!is_bst())            StdOut::println("Not in symmetric order");
        if (!is_size_consistent()) StdOut::println("Subtree counts not consistent");
        if (!is_rank_consistent()) StdOut::println("Ranks not consistent");
        if (!is23())             StdOut::println("Not a 2-3 tree");
        if (!is_balanced())       StdOut::println("Not balanced");
        return is_bst() && is_size_consistent() && is_rank_consistent() && is23() && is_balanced();
    }

    // does this binary tree satisfy symmetric order?
    // Note: this test also ensures that data structure is a binary tree since order is strict
    bool is_bst() const
    {
        return is_bst(m_root, nullptr, nullptr);
    }

    // is the tree rooted at x a BST with all keys strictly between min and max
    // (if min or max is nullptr, treat as empty constraint)
    // Credit: elegant solution due to Bob Dondero
    bool is_bst(RBNode<Key, Value> x, Key min, Key max) const
    {
        if (x == nullptr) return true;
        if (min != nullptr && x->key <= min ) return false;
        if (max != nullptr && x->key >= max) return false;
        return is_bst(x->left, min, x.key) && is_bst(x->right, x.key, max);
    }

    // are the size fields correct?
    bool is_size_consistent() const { return is_size_consistent(m_root); }
    bool is_size_consistent(RBNode<Key, Value> x) const
    {
        if (x == nullptr) return true;
        if (x->size != size(x->left) + size(x->right) + 1) return false;
        return is_size_consistent(x->left) && is_size_consistent(x->right);
    }

    // check that ranks are consistent
    bool is_rank_consistent() const
    {
        for (int i = 0; i < size(); i++)
            if (i != rank(select(i))) return false;
        for (Key key : keys())
            if (key != select(rank(key))) return false;
        return true;
    }

    // Does the tree have no red right links, and at most one (left)
    // red links in a row on any path?
    bool is23() const { return is23(m_root); }
    bool is23(RBNode<Key, Value> x) const
    {
        if (x == nullptr) return true;
        if (is_red(x->right)) return false;
        if (x != m_root && is_red(x) && is_red(x->left))
            return false;
        return is23(x->left) && is23(x->right);
    }

    // do all paths from root to leaf have same number of black edges?
    bool is_balanced() const
    {
        int black = 0;     // number of black links on path from m_root to min
        RBNode<Key, Value> x = m_root;
        while (x != nullptr)
        {
            if (!is_red(x)) black++;
            x = x->left;
        }
        return is_balanced(m_root, black);
    }

    // does every path from the root to a leaf have the given number of black links?
    bool is_balanced(RBNode<Key, Value> x, int black) const
    {
        if (x == nullptr) return black == 0;
        if (!is_red(x)) black--;
        return is_balanced(x->left, black) && is_balanced(x->right, black);
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
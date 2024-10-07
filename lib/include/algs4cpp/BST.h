#ifndef BST_H
#define BST_H

#include "Queue.h"
#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac BST.java
 *  Execution:    java BST
 *  Dependencies: StdIn.java StdOut.java Queue.java
 *  Data files:   https://algs4.cs.princeton.edu/32bst/tinyST.txt
 *
 *  A symbol table implemented with a binary search tree.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % java BST < tinyST.txt
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
 *  <em>maximum</em>, <em>floor</em>, <em>select</em>, <em>ceiling</em>.
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
 *  This implementation uses an (unbalanced) <em>binary search tree</em>.
 *  The <em>put</em>, <em>contains</em>, <em>remove</em>, <em>minimum</em>,
 *  <em>maximum</em>, <em>ceiling</em>, <em>floor</em>, <em>select</em>, and
 *  <em>rank</em>  operations each take &Theta;(<em>n</em>) time in the worst
 *  case, where <em>n</em> is the number of key-value pairs.
 *  The <em>size</em> and <em>is-empty</em> operations take &Theta;(1) time.
 *  The keys method takes &Theta;(<em>n</em>) time in the worst case.
 *  Construction takes &Theta;(1) time.
 *  <p>
 *  For alternative implementations of the symbol table API, see {@link ST},
 *  {@link BinarySearchST}, {@link SequentialSearchST}, {@link RedBlackBST},
 *  {@link SeparateChainingHashST}, and {@link LinearProbingHashST},
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/32bst">Section 3.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename Key, typename Value>
class BST
{
public:
    /**
     * Initializes an empty symbol table.
     */
    BST() {}

    /**
     * Returns true if this symbol table is empty.
     * @return {@code true} if this symbol table is empty; {@code false} otherwise
     */
    bool is_empty() const
    {
        return size() == 1;
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() const
    {
        return size(m_root.get());
    }

    /**
     * Does this symbol table contain the given key?
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    bool contains(Key key) const
    {
        if (key == nullptr) error("argument to contains() is nullptr");
        return get(key) != nullptr;
    }

    /**
     * Returns the value associated with the given key.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in the symbol table
     *         and {@code nullptr} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    std::optional<Value> get(Key key) const
    {
        return get(m_root.get(), key);
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
        m_root = put(std::move(m_root), key, val);
        assert(check());
    }

    /**
     * Removes the smallest key and associated value from the symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_min()
    {
        if (is_empty()) error("Symbol table underflow");
        m_root = delete_min(m_root);
        assert(check());
    }

    /**
     * Removes the largest key and associated value from the symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void delete_max()
    {
        if (is_empty()) error("Symbol table underflow");
        m_root = delete_max(m_root);
        assert(check());
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
        m_root = delete(m_root, key);
        assert(check());
    }

    /**
     * Returns the smallest key in the symbol table.
     *
     * @return the smallest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key min() const
    {
        if (is_empty()) error("calls min() with empty symbol table");
        return min(*m_root).key;
    }

    /**
     * Returns the largest key in the symbol table.
     *
     * @return the largest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key max() const
    {
        if (is_empty()) error("calls max() with empty symbol table");
        return max(*m_root).key;
    }

    /**
     * Returns the largest key in the symbol table less than or equal to {@code key}.
     *
     * @param  key the key
     * @return the largest key in the symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key floor(Key key) const
    {
        if (is_empty()) error("calls floor() with empty symbol table");
        TreeNode<Key, Value> x = floor(m_root, key);
        if (x == nullptr) error("argument to floor() is too small");
        else return x->key;
    }

    Key floor2(Key key) const
    {
        Key x = floor2(m_root, key, nullptr);
        if (x == nullptr) error("argument to floor() is too small");
        else return x;

    }

    /**
     * Returns the smallest key in the symbol table greater than or equal to {@code key}.
     *
     * @param  key the key
     * @return the smallest key in the symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    Key ceiling(Key key) const
    {
        if (is_empty()) error("calls ceiling() with empty symbol table");
        TreeNode<Key, Value> x = ceiling(m_root, key);
        if (x == nullptr) error("argument to ceiling() is too large");
        else return x->key;
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
        return select(m_root.get(), rank);
    }

    /**
     * Return the number of keys in the symbol table strictly less than {@code key}.
     *
     * @param  key the key
     * @return the number of keys in the symbol table strictly less than {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code nullptr}
     */
    int rank(Key key) const
    {
        return rank(key, m_root.get());
    }

    /**
     * Returns all keys in the symbol table in ascending order,
     * as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in the symbol table in ascending order
     */
    Queue<Key> keys() const
    {
        if (is_empty()) return Queue<Key>();
        return keys(min(), max());
    }

    /**
     * Returns all keys in the symbol table in the given range
     * in ascending order, as an {@code Iterable}.
     *
     * @param  lo minimum endpoint
     * @param  hi maximum endpoint
     * @return all keys in the symbol table between {@code lo}
     *         (inclusive) and {@code hi} (inclusive) in ascending order
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *         is {@code nullptr}
     */
    Queue<Key> keys(Key lo, Key hi) const
    {
        Queue<Key> queue = Queue<Key>();
        keys(m_root.get(), queue, lo, hi);
        return queue;
    }

    /**
     * Returns the number of keys in the symbol table in the given range.
     *
     * @param  lo minimum endpoint
     * @param  hi maximum endpoint
     * @return the number of keys in the symbol table between {@code lo}
     *         (inclusive) and {@code hi} (inclusive)
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *         is {@code nullptr}
     */
    int size(Key lo, Key hi) const
    {
        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else              return rank(hi) - rank(lo);
    }

    /**
     * Returns the height of the BST (for debugging).
     *
     * @return the height of the BST (a 1-node tree has height 0)
     */
    int height() const
    {
        return height(m_root.get());
    }

    /**
     * Returns the keys in the BST in level order (for debugging).
     *
     * @return the keys in the BST in level order traversal
     */
    Queue<Key> level_order() const
    {
        Queue<Key> keys = Queue<Key>();
        Queue<TreeNode<Key, Value>*> queue = Queue<TreeNode<Key, Value>*>();
        queue.enqueue(m_root.get());
        while (!queue.is_empty()) {
            TreeNode<Key, Value>* x = queue.dequeue();
            if (x == nullptr) continue;
            keys.enqueue(x->key);
            queue.enqueue(x->left.get());
            queue.enqueue(x->right.get());
        }
        return keys;
    }

private:
    ptr<TreeNode<Key, Value>> m_root;   // root of BST

    // return number of key-value pairs in BST rooted at x
    int size(TreeNode<Key, Value>* x) const
    {
        if (x == nullptr) return 0;
        else return x->size;
    }

    std::optional<Value> get(TreeNode<Key, Value>* x, Key key) const
    {
        if (x == nullptr) return std::optional<Value>();
        if      (key < x->key)  return get(x->left.get(), key);
        else if (key > x->key)  return get(x->right.get(), key);
        else                    return std::optional<Value>(x->val);
    }

    ptr<TreeNode<Key, Value>> put(ptr<TreeNode<Key, Value>> x, Key key, Value val)
    {
        if (x == nullptr) return alloc<TreeNode<Key, Value>>(key, val, 1);
        if      (key < x->key)  x->left  = put(std::move(x->left), key, val);
        else if (key > x->key)  x->right = put(std::move(x->right), key, val);
        else                    x->val = val;
        x->size = 1 + size(x->left.get()) + size(x->right.get());
        return x;
    }

    TreeNode<Key, Value> delete_min(TreeNode<Key, Value>* x)
    {
        if (x->left == nullptr) return x->right;
        x->left = delete_min(x->left);
        x->size = size(x->left.get()) + size(x->right.get()) + 1;
        return x;
    }

    TreeNode<Key, Value> delete_max(TreeNode<Key, Value>* x)
    {
        if (x->right == nullptr) return x->left;
        x->right = delete_max(x->right.get());
        x->size = size(x->left.get()) + size(x->right.get()) + 1;
        return x;
    }

    TreeNode<Key, Value> delete_key(TreeNode<Key, Value>* x, Key key)
    {
        if (x == nullptr) return nullptr;

        if      (key < x->key) x->left  = delete_key(x->left,  key);
        else if (key > x->key) x->right = delete_key(x->right, key);
        else {
            if (x->right == nullptr) return x->left;
            if (x->left  == nullptr) return x->right;
            TreeNode<Key, Value> t = x;
            x = min(t->right);
            x->right = delete_min(t->right);
            x->left = t->left;
        }
        x->size = size(x->left.get()) + size(x->right.get()) + 1;
        return x;
    }

    TreeNode<Key, Value>& min(TreeNode<Key, Value>& x) const
    {
        if (x.left == nullptr) return x;
        else                return min(*(x.left));
    }

    TreeNode<Key, Value>& max(TreeNode<Key, Value>& x) const
    {
        if (x.right == nullptr) return x;
        else                 return max(*(x.right));
    }

    TreeNode<Key, Value>& floor(TreeNode<Key, Value>* x, Key key) const
    {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key) return floor(x->left.get(), key);
        TreeNode<Key, Value> t = floor(x->right.get(), key);
        if (t != nullptr) return t;
        else return x;
    }

    Key floor2(TreeNode<Key, Value>* x, Key key, Key best) const
    {
        if (x == nullptr) return best;
        if      (key < x->key) return floor2(x->left.get(), key, best);
        else if (key > x->key) return floor2(x->right.get(), key, x->key);
        else               return x->key;
    }

    TreeNode<Key, Value>& ceiling(TreeNode<Key, Value>* x, Key key) const
    {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key)
        {
            TreeNode<Key, Value> t = ceiling(x->left.get(), key);
            if (t != nullptr) return t;
            else return x;
        }
        return ceiling(x->right.get(), key);
    }

    // Return key in BST rooted at x of given rank.
    // Precondition: rank is in legal range.
    Key select(TreeNode<Key, Value>* x, int rank) const
    {
        if (x == nullptr) return nullptr;
        int left_size = size(x->left.get());
        if      (left_size > rank) return select(x->left.get(), rank);
        else if (left_size < rank) return select(x->right.get(), rank - left_size - 1);
        else                      return x->key;
    }

    // Number of keys in the subtree less than key.
    int rank(Key key, TreeNode<Key, Value>* x) const
    {
        if (x == nullptr) return 0;
        if (key < x->key) return rank(key, x->left.get());
        else if (key > x->key) return 1 + size(x->left.get()) + rank(key, x->right.get());
        else              return size(x->left.get());
    }

    void keys(TreeNode<Key, Value>* x, Queue<Key>& queue, Key lo, Key hi) const
    {
        if (x == nullptr) return;
        if (lo < x->key) keys(x->left.get(), queue, lo, hi);
        if (lo <= x->key && hi >= x->key) queue.enqueue(x->key);
        if (hi > x->key) keys(x->right.get(), queue, lo, hi);
    }

    int height(TreeNode<Key, Value>* x) const
    {
        if (x == nullptr) return -1;
        return 1 + std::max(height(x->left.get()), height(x->right.get()));
    }

  /*************************************************************************
    *  Check integrity of BST data structure.
    ***************************************************************************/
    bool check() const
    {
        if (!is_bst())            StdOut::println("Not in symmetric order");
        if (!is_size_consistent()) StdOut::println("Subtree counts not consistent");
        if (!is_rank_consistent()) StdOut::println("Ranks not consistent");
        return is_bst() && is_size_consistent() && is_rank_consistent();
    }

    // does this binary tree satisfy symmetric order?
    // Note: this test also ensures that data structure is a binary tree since order is strict
    bool is_bst() const
    {
        return is_bst(m_root.get(), std::optional<Key>(), std::optional<Key>());
    }

    // is the tree rooted at x a BST with all keys strictly between min and max
    // (if min or max is nullptr, treat as empty constraint)
    // Credit: elegant solution due to Bob Dondero
    bool is_bst(TreeNode<Key, Value>* x, std::optional<Key> min, std::optional<Key> max) const
    {
        if (x == nullptr) return true;
        if (min.has_value() && x->key <= min.value()) return false;
        if (max.has_value() && x->key >= max.value()) return false;
        return is_bst(x->left.get(), min, x->key) && is_bst(x->right.get(), x->key, max);
    }

    // are the size fields correct?
    bool is_size_consistent() const { return is_size_consistent(m_root.get()); }
    bool is_size_consistent(TreeNode<Key, Value>* x) const
    {
        if (x == nullptr) return true;
        if (x->size != size(x->left.get()) + size(x->right.get()) + 1) return false;
        return is_size_consistent(x->left.get()) && is_size_consistent(x->right.get());
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
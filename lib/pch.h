#ifndef PCH_H
#define PCH_H

#include <string>
#include <cstring>
#include <iostream>
#include <istream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <memory>
#include <limits>
#include <random>
#include <chrono>
#include <climits>
#include <cassert>
#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <functional>
#include <cstdarg>
#include <ctime>
#include <format>
#include <cstdint>
#include <thread>
#include <fstream>
#include <utility>

//#include <wx/wx.h>

#define cmp_func bool(*cmp)(T, T)

template <typename T>
using ptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr ptr<T> alloc(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
void copy_ptrs(std::vector<ptr<T>>& dst, const std::vector<ptr<T>>& src)
{
    dst.reserve(src.size());
    
    // Can't directly copy vector due to std::unique_ptr
    for (const auto& it : src)
    {
        if (it == nullptr)
            dst.push_back(nullptr);
        else
            dst.push_back(alloc<T>(*it));
    }
}
template<typename... Args>
void error(const std::format_string<Args...> fmt, Args&&... args)
{
    std::cerr << "Error: " << std::vformat(fmt.get(), std::make_format_args(args...)) << '\n';
    exit(EXIT_FAILURE);
}

namespace map_extended
{
    template <typename Key, typename Value>
    Key floor_key(Key k, std::map<Key, Value> map);
}

constexpr double pi() { return std::atan(1)*4; }

template <typename T>
constexpr size_t size(T* array) { return sizeof(array) / sizeof(T);}

// helper linked list class
template <typename Item>
struct Node
{
    Item item;
    ptr<Node<Item>> next;
};

template <typename Item>
struct LinkedIterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Item;
    using pointer           = Item*;
    using reference         = Item&; 

    LinkedIterator(Node<Item>* node) : m_node(node)
    {
        m_ptr = &node->item;
    }

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // Prefix increment
    LinkedIterator& operator++()
    {
        m_node = m_node->next.get();
        m_ptr = &m_node->item;
        return *this;
    }  

    // Postfix increment
    LinkedIterator operator++(int)
    {
        LinkedIterator tmp = *this; 
        ++(*this);
        return tmp;
    }

    friend bool operator== (const LinkedIterator& a, const LinkedIterator& b)
    {
        return a.m_ptr == b.m_ptr;
    };

    friend bool operator!= (const LinkedIterator& a, const LinkedIterator& b)
    {
        return a.m_ptr != b.m_ptr;
    };
    
private:
    pointer m_ptr;
    Node<Item>* m_node;
};

#endif
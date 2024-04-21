#ifndef PCH_H
#define PCH_H

#include <string>
#include <iostream>
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

#define cmp_func bool(*cmp)(T, T)

void error(std::string outputError);

namespace map_extended
{
    template <typename Key, typename Value>
    Key floorKey(Key k, std::map<Key, Value> map);
}

constexpr double pi() { return std::atan(1)*4; }
constexpr double infinity = std::numeric_limits<double>::infinity();

template <typename T>
constexpr size_t size(T* array) { return sizeof(array) / sizeof(T);}

// helper linked list class
template <typename Item>
struct Node
{
    Item item;
    Node<Item>* next;
};

#endif
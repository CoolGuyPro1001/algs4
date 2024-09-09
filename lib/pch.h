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

//#include <wx/wx.h>

#define cmp_func bool(*cmp)(T, T)

void error(std::string outputError);

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
    std::unique_ptr<Node<Item>> next;
};

#endif
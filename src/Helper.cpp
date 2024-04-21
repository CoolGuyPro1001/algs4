void error(std::string outputError)
{
    std::cerr << "Error: " << outputError << "\n";
    exit(EXIT_FAILURE);
}

template <typename Key, typename Value>
Key map_extended::floorKey(Key k, std::map<Key, Value> map)
{
    auto highestKey = map.begin();
    for (auto it = map.begin(); it != map.lower_bound(k); it++)
    {
        highestKey = it;
        if (highestKey == k)
            return *highestKey;
    }

    return *highestKey;
}
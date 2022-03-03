#ifndef RADIX_TREE
#define RADIS_TREE

#include <map>
#include <vector>
#include <string>
using namespace std;

template <typename ValueType>
class RadixTree {
    public:
        RadixTree();
        ~RadixTree();
        void insert(string key, const ValueType& value);
        ValueType* search(string key);
    private:
        map<string, ValueType> m_map; // Fake design
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree() {

}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree() {

}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value) {
    m_map[key] = value;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(string key) {
    map<string, ValueType>::iterator it = m_map.find(key);
    if (it == m_map.end())
        return nullptr;
    return &it->second;
}

#endif
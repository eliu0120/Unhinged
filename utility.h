#ifndef UTILITY
#define UTILITY

#include <string>
#include <vector>
using namespace std;

struct AttValPair;

string structToString(const AttValPair& attVal);

template <typename ValueType>
bool compareValues(const ValueType& value, const vector<ValueType>& comparisons) {
    for (int i = 0; i < comparisons.size(); i++)
        if (value != comparisons[i])
            return false;
    return true;
}

#endif
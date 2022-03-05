#include "utility.h"
#include "provided.h"
#include <string>
using namespace std;

string structToString(const AttValPair& attVal) {
    return attVal.attribute + "," + attVal.value;
}

bool compareEmailCounts(const EmailCount& lhs, const EmailCount& rhs) {
    if (lhs.count > rhs.count)
        return true;
    else if (lhs.count < rhs.count)
        return false;
    return lhs.email < rhs.email;
}
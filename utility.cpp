#include "utility.h"
#include "provided.h"
#include <string>
using namespace std;

string structToString(const AttValPair& attVal) {
    return attVal.attribute + "," + attVal.value;
}
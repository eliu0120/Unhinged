#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "provided.h"
#include "utility.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// #include <iostream>
using namespace std;

AttributeTranslator::AttributeTranslator() {

}

AttributeTranslator::~AttributeTranslator() {

}

bool AttributeTranslator::Load(string filename) {
    ifstream file(filename.c_str());
    if (file.is_open()) {
        string line = "";
        string source = "";
        string compatible_att = "";
        string compatible_value = "";
        while (getline(file, line)) {
            int pos = line.find(",");
            pos = line.find(",", pos + 1);
            source = line.substr(0, pos);
            pos = line.find(",", pos + 1);
            compatible_att = line.substr(source.size() + 1, pos - source.size() - 1);
            compatible_value = line.substr(source.size() + compatible_att.size() + 2);
            AttValPair compatiblePair(compatible_att, compatible_value);
            vector<AttValPair>* values = m_sourceToCompatible.search(source);
            if (values != nullptr && compareValues(compatiblePair, *values))
                continue;
            else if (values != nullptr)
                (*values).push_back(compatiblePair);
            else {
                vector<AttValPair> v = {compatiblePair};
                m_sourceToCompatible.insert(source, v);
            }
            // cout << source << endl << compatible_att << endl << compatible_value << endl; // testing only
        }
        return true;
    }
    return false;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) { // Re-add const later
    string src = structToString(source);
    vector<AttValPair>* values = m_sourceToCompatible.search(src);
    if (values == nullptr) {
        vector<AttValPair> emptyVector;
        return emptyVector;
    }
    return *values;
}
#ifndef ATTRIBUTE_TRANSLATOR
#define ATTRIBUTE_TRANSLATOR

#include <string>
#include <vector>
#include "RadixTree.h"
using namespace std;

struct AttValPair;

class AttributeTranslator {
    public:
        AttributeTranslator();
        ~AttributeTranslator();
        bool Load(string filename);
        vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const; // Re-add const later
    private:
        RadixTree<vector<AttValPair>> m_sourceToCompatible;
};

#endif
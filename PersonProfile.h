#ifndef PERSON_PROFILE
#define PERSON_PROFILE

#include <string>
#include <vector>
#include <unordered_set>
#include "RadixTree.h"
using namespace std;

struct AttValPair;

class PersonProfile {
    public:
        PersonProfile(string name, string email);
        ~PersonProfile();
        string GetName() const;
        string GetEmail() const;
        void AddAttValPair(const AttValPair& attval);
        int GetNumAttValPairs() const;
        bool GetAttVal(int attribute_num, AttValPair& attval) const;
        // void dump(string key); // delete later
    private:    
        string m_name;
        string m_email;
        int m_numAttValPairs;
        RadixTree<unordered_set<string>> m_AttToVal;
        vector<AttValPair> m_attValPairs;
};

#endif
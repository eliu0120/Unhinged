#include "PersonProfile.h"
#include "RadixTree.h"
#include "utility.h"
#include "provided.h"
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

PersonProfile::PersonProfile(string name, string email) {
    m_name = name;
    m_email = email;
    m_numAttValPairs = 0;
}

PersonProfile::~PersonProfile() {

}

string PersonProfile::GetName() const {
    return m_name;
}

string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    unordered_set<string>* values = m_AttToVal.search(attval.attribute);
    if (values != nullptr && (*values).find(attval.value) != (*values).end())
        return;
    else if (values != nullptr)
        (*values).insert(attval.value);
    else {
        unordered_set<string> v = {attval.value};
        m_AttToVal.insert(attval.attribute, v);
    }
    m_numAttValPairs++;
    m_attValPairs.push_back(attval);
}

int PersonProfile::GetNumAttValPairs() const {
    return m_numAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
        return false;
    attval = m_attValPairs[attribute_num];
    return true;
}

/*
#include <iostream>
void PersonProfile::dump(string key) {
    vector<string>* values = m_AttToVal.search(key);
    for (int i = 0; i < (*values).size(); i++)
        cout << (*values)[i] << endl;
} */
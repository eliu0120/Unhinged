#include "MemberDatabase.h"
#include "RadixTree.h"
#include "provided.h"
#include "utility.h"
#include "PersonProfile.h"
#include <fstream>
#include <string>
using namespace std;

MemberDatabase::MemberDatabase() {

}

MemberDatabase::~MemberDatabase() {
    while (m_profiles.size() > 0) {
        delete m_profiles[0];
        m_profiles.erase(m_profiles.begin());
    }
}

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream file(filename.c_str());
    if (file.is_open()) {
        string line = "";
        string name = "";
        string email = "";
        string attribute = "";
        string value = "";
        string avpstr = "";
        int linePos = 1, numPairs = 0, commaPos = 0;
        vector<AttValPair> pairs;
        while (getline(file, line)) {
            if (linePos == 0) {
                linePos++;
                continue;
            } else if (linePos == 1) {
                name = line;
                linePos++;
            } else if (linePos == 2) {
                email = line;
                linePos++;
            } else if (linePos == 3) {
                numPairs = stoi(line);
                linePos++;
            } else if (linePos < numPairs + 4) {
                commaPos = line.find(",");
                attribute = line.substr(0, commaPos);
                value = line.substr(commaPos + 1);
                AttValPair avp(attribute, value);
                pairs.push_back(avp);
                avpstr = structToString(avp);
                vector<string>* values = m_pairToEmail.search(avpstr);
                if (values != nullptr && !compareValues(email, *values)) {
                    (*values).push_back(email);
                } else if (values == nullptr) {
                    vector<string> v;
                    v.push_back(email);
                    m_pairToEmail.insert(avpstr, v);
                }
                linePos++;
            } 
            if (linePos == numPairs + 4) {
                PersonProfile* p = new PersonProfile(name, email);
                for (int i = 0; i < pairs.size(); ) {
                    p->AddAttValPair(pairs[i]);
                    pairs.erase(pairs.begin());
                }
                m_profiles.push_back(p);
                if (m_emailToProfile.search(email) != nullptr)
                    return false;
                m_emailToProfile.insert(email, p);
                linePos = 0;
                numPairs = 0;
            }
        }
        return true;
    }
    return false;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    string avpstr = structToString(input);
    vector<string>* members = m_pairToEmail.search(avpstr);
    if (members == nullptr) {
        vector<string> emptyMap;
        return emptyMap;
    }
    return *members;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
    PersonProfile** pp = m_emailToProfile.search(email);
    if (pp == nullptr)
        return nullptr;
    return *pp;
}
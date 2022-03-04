#include "MemberDatabase.h"
#include "RadixTree.h"
#include "provided.h"
#include "utility.h"
#include "PersonProfile.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

MemberDatabase::MemberDatabase() {

}

MemberDatabase::~MemberDatabase() {

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
            if (linePos == 1) {
                name = line;
                linePos++;
                continue;
            } else if (linePos == 2) {
                email = line;
                linePos++;
                continue;
            } else if (linePos == 3) {
                stringstream ss;
                ss << line;
                ss >> numPairs;
                // cout << numPairs << endl;
                linePos++;
                continue;
            } else if (linePos < numPairs + 4) {
                commaPos = line.find(",");
                attribute = line.substr(0, commaPos);
                value = line.substr(commaPos + 1);
                AttValPair avp(attribute, value);
                pairs.push_back(avp);
                avpstr = structToString(avp);
                vector<string>* values = m_pairToEmail.search(avpstr);
                if (values != nullptr && compareValues(email, *values)) {
                    linePos++;
                    continue;
                } else if (values != nullptr)
                    (*values).push_back(email);
                else {
                    vector<string> v = {email};
                    m_pairToEmail.insert(avpstr, v);
                }
                linePos++;
                continue;
            } else {
                PersonProfile p(name, email);
                for (int i = 0; i < pairs.size(); ) {
                    p.AddAttValPair(pairs[i]);
                    pairs.erase(pairs.begin());
                }
                if (m_emailToProfile.search(email) != nullptr)
                    return false;
                m_emailToProfile.insert(email, p);
                linePos = 1;
                numPairs = 0;
            }
        }
        return true;
    }
    return false;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) {
    string avpstr = structToString(input);
    vector<string>* members = m_pairToEmail.search(avpstr);
    if (members == nullptr) {
        vector<string> emptyMap;
        return emptyMap;
    }
    return *members;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) {
    return m_emailToProfile.search(email);
}
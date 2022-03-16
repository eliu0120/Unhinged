#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "utility.h"
#include "provided.h"
#include "PersonProfile.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

MatchMaker::MatchMaker(MemberDatabase& mdb, AttributeTranslator& at) { // Add const to parameters later
    m_md = &mdb;
    m_at = &at;
}

MatchMaker::~MatchMaker() {

}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const { // Add const later
    const PersonProfile* pp = m_md->GetMemberByEmail(email);
    AttValPair avp;
    int i = 0;
    unordered_set<string> compatibleAVPs;
    vector<AttValPair> possibleAVPs;
    unordered_map<string, int> uniqueEmails;
    vector<EmailCount> ECs;
    while (pp->GetAttVal(i, avp)) {
        possibleAVPs = m_at->FindCompatibleAttValPairs(avp);
        for (int j = 0; j < possibleAVPs.size(); j++)
            compatibleAVPs.insert(structToString(possibleAVPs[j]));
        i++;
    }
    unordered_set<string>::iterator it;
    for (it = compatibleAVPs.begin(); it != compatibleAVPs.end(); it++) {
        int commaPos = (*it).find(",");
        string att = (*it).substr(0, commaPos);
        string val = (*it).substr(commaPos + 1);
        AttValPair avp2(att, val);
        vector<string> matches = m_md->FindMatchingMembers(avp2);
        for (int j = 0; j < matches.size(); j++)
            if (uniqueEmails.find(matches[j]) == uniqueEmails.end())
                uniqueEmails[matches[j]] = 1;
            else
                uniqueEmails[matches[j]]++;
    }
    unordered_map<string, int>::iterator it2;
    for (it2 = uniqueEmails.begin(); it2 != uniqueEmails.end(); it2++) {
        if (it2->second >= threshold && it2->first != email) {
            EmailCount ec(it2->first, it2->second);
            ECs.push_back(ec);
        }
    }
    sort(ECs.begin(), ECs.end(), compareEmailCounts);
    return ECs;
}
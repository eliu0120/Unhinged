#ifndef MATCHMAKER
#define MATCHMAKER

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class AttributeTranslator;
class MemberDatabase;
struct EmailCount;

class MatchMaker {
    public:
        MatchMaker(MemberDatabase& mdb, AttributeTranslator& at); // Add const to parameters later
        ~MatchMaker();
        vector<EmailCount> IdentifyRankedMatches(string email, int threshold); // Add const later
    private:
        MemberDatabase* m_md;
        AttributeTranslator* m_at;
};

#endif
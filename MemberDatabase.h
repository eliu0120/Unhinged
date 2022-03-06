#ifndef MEMBER_DATABASE
#define MEMBER_DATABASE

#include <string>
#include <vector>
#include "RadixTree.h"
using namespace std;

class PersonProfile;
struct AttValPair;

class MemberDatabase {
    public:
        MemberDatabase();
        ~MemberDatabase();
        bool LoadDatabase(string filename);
        vector<string> FindMatchingMembers(const AttValPair& input) const; // Add const later
        const PersonProfile* GetMemberByEmail(string email) const; // Add const later
    private:
        RadixTree<vector<string>> m_pairToEmail;
        RadixTree<PersonProfile*> m_emailToProfile;
        vector<PersonProfile*> m_profiles;
};

#endif
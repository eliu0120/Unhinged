// main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(MemberDatabase &mdb, AttributeTranslator &at);


#include "RadixTree.h"
#include <iostream>
#include "utility.h"
// int main() {
    /* RadixTree<vector<string>> rt;
    vector<string> v = {"CS", "Gameing"};
    rt.insert("Eric", v);
    vector<string>* result = rt.search("Eric");
    for (int i = 0; i < result->size(); i++)
        cout << (*result)[i] << endl;
    vector<string> v2 = {"Gameing", "Body Building", "irony"};
    rt.insert("Daniel", v2);
    result = rt.search("Daniel");
    for (int i = 0; i < result->size(); i++)
        cout << (*result)[i] << endl;
    result = rt.search("Kyle");
    if (result == nullptr)
        cout << "Nope" << endl;
    cout << endl; */

    /*
    PersonProfile p("Eric", "eliu0120@gmail.com");
    AttValPair attVal1("Hobby", "Gameing");
    AttValPair attVal2("Hobby", "Hiking");
    p.AddAttValPair(attVal1);
    p.AddAttValPair(attVal2);
    AttValPair attVal3("Occupation", "student");
    AttValPair attVal4("Gender", "male");
    p.AddAttValPair(attVal3);
    p.AddAttValPair(attVal4);
    for (int i = 0; i < p.GetNumAttValPairs(); i++) {
        AttValPair av;
        p.GetAttVal(i, av);
        cout << av.attribute << "->" << av.value << endl;
    }
    cout << endl; */
    
    /*
    AttributeTranslator at;
    // at.load("test.txt");
    at.Load("translator.txt");
    string srcAtt = "";
    string srcVal = "";
    cout << "Input source attribute: ";
    getline(cin, srcAtt);
    cout << "Input source value: ";
    getline(cin, srcVal);
    cout << endl;
    AttValPair src(srcAtt, srcVal);
    vector<AttValPair> compPairs = at.FindCompatibleAttValPairs(src);
    for (int i = 0; i < compPairs.size(); i++)
        cout << structToString(compPairs[i]) << endl; */

    /*
    MemberDatabase md;
    md.LoadDatabase("testMembers.txt"); */

    /*
    string att = "";
    string val = "";
    cout << "Input attribute: ";
    getline(cin, att);
    cout << "Input value: ";
    getline(cin, val);
    AttValPair pair(att, val);
    vector<string> emails = md.FindMatchingMembers(pair);
    for (int i = 0; i < emails.size(); i++)
        cout << emails[i] << endl;
    cout << emails.size() << endl; */
    
    /*
    string email = "";
    cout << "Input email: ";
    getline(cin, email);
    const PersonProfile* pp = md.GetMemberByEmail(email);
    cout << pp->GetEmail() << " " << pp->GetName() << endl; */

    /*
    MemberDatabase mdb;
    AttributeTranslator at;
    mdb.LoadDatabase(MEMBERS_FILE);
    at.load(TRANSLATOR_FILE);
    MatchMaker m(mdb, at);
    m.IdentifyRankedMatches("AbFow2483@charter.net", 0); */
// } 


int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
} 

bool findMatches(MemberDatabase &mdb, AttributeTranslator &at) // add const to parameters later
{
    // Prompt for email
    std::string email;
    const PersonProfile *pp;
    for (;;)
    {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

    // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++)
    {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

    // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else
    {
        std::cout << "The following members were good matches:" << std::endl;
        ;
        for (const auto &emailCount : emails)
        {
            const PersonProfile *pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}

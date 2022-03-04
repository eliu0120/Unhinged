#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "provided.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

AttributeTranslator::AttributeTranslator() {

}

AttributeTranslator::~AttributeTranslator() {

}

bool AttributeTranslator::load(string filename) {
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
            // cout << source << endl << compatible_att << endl << compatible_value << endl; // testing only
        }
        return true;
    }
    return false;
}
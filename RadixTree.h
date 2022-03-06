#ifndef RADIX_TREE
#define RADIX_TREE

#include <map>
#include <string>
using namespace std;

template <typename ValueType>
class RadixTree {
    public:
        RadixTree();
        ~RadixTree();
        void insert(string key, const ValueType& value);
        ValueType* search(string key) const; // Add const later with real RadixTree  design
    private:
        struct Node {
            string str;
            bool isEnd;
            Node* arr[128];
            ValueType value;
        };
        Node* head;
        void cleanUp(Node* p);
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree() {
    head = new Node;
    head->isEnd = false;
    for (int i = 0; i < 128; i++)
        head->arr[i] = nullptr;
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree() {
    cleanUp(head);
}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value) {
    if (head->arr[key[0]] == nullptr) { // Top row
        head->arr[key[0]] = new Node;
        head->arr[key[0]]->str = key;
        head->arr[key[0]]->isEnd = true;
        for (int i = 0; i < 128; i++)
            head->arr[key[0]]->arr[i] = nullptr;
        head->arr[key[0]]->value = value;
        return;
    }
    Node* p = head->arr[key[0]];
    int keyItr = 0;
    string newSubstr = "";
    string compareKey = p->str;
    for (int i = 0; i < key.size(); i++) {
        if (keyItr == p->str.size()) {
            if (p->arr[key[i]] != nullptr) {
                p = p->arr[key[i]];
                keyItr = 0;
                i--;
                compareKey += p->str;
                continue;
            } else { // Adding "Cause" to "Ca"
                p->arr[key[i]] = new Node;
                p->arr[key[i]]->str = key.substr(i);
                p->arr[key[i]]->isEnd = true;
                for (int j = 0; j < 128; j++)
                    p->arr[key[i]]->arr[j] = nullptr;
                p->arr[key[i]]->value = value;
                return;
            }
        } else if (compareKey == key) {
            p->value = value;
            if (!p->isEnd)
                p->isEnd = true;
            return; // Adding "Ca" when "Ca" already exists
        } else if (p->str[keyItr] != key[i]) { // "Card" vs "Coin"
            newSubstr = p->str.substr(keyItr);
            p->str = p->str.substr(0, keyItr);
            Node* n = new Node;
            n->str = newSubstr;
            n->value = p->value;
            if (!p->isEnd)
                n->isEnd = false;
            else
                n->isEnd = true;
            p->isEnd = false;
            for (int j = 0; j < 128; j++) {
                n->arr[j] = p->arr[j];
                p->arr[j] = nullptr;
            }
            p->arr[newSubstr[0]] = n;
            p->arr[key[i]] = new Node;
            p->arr[key[i]]->str = key.substr(i);
            p->arr[key[i]]->isEnd = true;
            for (int j = 0; j < 128; j++)
                p->arr[key[i]]->arr[j] = nullptr;
            p->arr[key[i]]->value = value;
            return;
        } else if (p->str[keyItr] == key[i])
            keyItr++;
    }
    newSubstr = p->str.substr(keyItr);
    p->str = p->str.substr(0, keyItr);
    p->arr[newSubstr[0]] = new Node; // Adding "Car" to Cards
    p->arr[newSubstr[0]]->str = newSubstr;
    p->arr[newSubstr[0]]->isEnd = true;
    for (int i = 0; i < 128; i++)
        p->arr[newSubstr[0]]->arr[i] = nullptr;
    p->arr[newSubstr[0]]->value = p->value;
    p->value = value;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(string key) const {
    if (head == nullptr || head->arr[key[0]] == nullptr)
        return nullptr;
    string word = "";
    Node* p = head->arr[key[0]];
    while (p != nullptr && word.size() < key.size()) {
        word += p->str;
        if (word.size() < key.size())
            p = p->arr[key[word.size()]];
    }
    if (word == key && p->isEnd)
        return &p->value;
    return nullptr;
}

template <typename ValueType>
void RadixTree<ValueType>::cleanUp(Node* p) {
    if (p == nullptr)
        return;
    for (int i = 0; i < 128; i++)
        cleanUp(p->arr[i]);
    delete p;
}

#endif
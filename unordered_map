#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <map>

using namespace std;

template<typename K, typename V>
class unordered_map
{
private:
    vector<list<pair<K, vector<V>>>> hashTable;
    int size;
    int capacity;

public:
    unordered_map(int cap = 100000) : capacity(cap), size(0), hashTable(cap) {}

    int hash(K key)
    {
        return std::hash<K>{}(key) % capacity;
    }

    void insert(K key, vector<V> values)
    {
        for (auto x : hashTable[hash(key)])
        {
            if (x.first == key)
            {
                x.second = values;
                return;
            }
        }
        hashTable[hash(key)].push_back(make_pair(key, values));
        size++;
    }

    bool search(K key, vector<V>& values)
    {
        for (auto x : hashTable[hash(key)])
        {
            if (x.first == key)
            {
                values = x.second;
                return true;
            }
        }
        return false;
    }

    bool remove(K key)
    {
        for (auto it = hashTable[hash(key)].begin(); it != hashTable[hash(key)].end(); it++)
        {
            if (it->first == key)
            {
                hashTable[hash(key)].erase(it);
                size--;
                return true;
            }
        }
        return false;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

int main() {
    unordered_map<string, string> unordered_map;

    vector<string> Jif_values = { "low", "low", "low" };
    vector<string> Skippy_values = { "medium", "low", "low" };
    vector<string> PeterPan_values = { "high", "low", "low" };
    vector<string> Reeses_values = { "high", "low", "medium" };
    vector<string> GreatValue_values = { "low", "high", "low" };

    unordered_map.insert("Jif", Jif_values);
    unordered_map.insert("Skippy", Skippy_values);
    unordered_map.insert("Peter Pan", PeterPan_values);
    unordered_map.insert("Reeses", Reeses_values);
    unordered_map.insert("Great Value", GreatValue_values);

    vector<string> value;
    if (unordered_map.search("Jif", value)) {
        cout << "Found Jif, values are: ";
        for (const auto& val : value) {
            cout << val << " ";
        }
        cout << endl;
    }
    else {
        cout << "Jif not found" << endl;
    }

    unordered_map.remove("Jif");

    if (unordered_map.search("Jif", value)) {
        cout << "Found Jif, values are: ";
        for (const auto& val : value) {
            cout << val << " ";
        }
        cout << endl;
    }
    else {
        cout << "Jif not found" << endl;
    }

    return 0;
}

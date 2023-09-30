// zavd_88.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int hashFunc(string str, int tableSize) {
    int hash = 0;
    for (char c : str) {
        hash = (hash * 31 + static_cast<int>(c)) % tableSize;
    }
    return abs(hash);
}

class HashTable {
    class KeyValuePair {
    private:
        int hash;
        string value;
        KeyValuePair* next;

    public:
        KeyValuePair(string value, int tableSize) {
            this->hash = hashFunc(value, tableSize);
            this->value = value;
            next = nullptr;
        }

        void setNext(KeyValuePair* next) {
            this->next = next;
        }

        string getValue() {
            return value;
        }

        int getHash() {
            return hash;
        }

        KeyValuePair* getNext() {
            return next;
        }
    };

private:
    vector<KeyValuePair*> vec;
    int tableSize;

public:
    HashTable(int tableSize) : tableSize(tableSize) {
        vec.resize(tableSize);
    }

    void add(string value) {
        int hash = hashFunc(value, tableSize);
        KeyValuePair* k = new KeyValuePair(value, tableSize);
        if (vec[hash] == nullptr) {
            vec[hash] = k;
        }
        else {
            KeyValuePair* temp = vec[hash];
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            temp->setNext(k);
        }
    }

    bool search(string value) {
        int hash = hashFunc(value, tableSize);
        if (vec[hash] == nullptr) {
            cout << "Value not found" << endl;
            return false;
        }

        KeyValuePair* temp = vec[hash];
        while (temp != nullptr) {
            if (temp->getValue() == value) {
                cout << "Value found" << endl;
                return true;
            }
            temp = temp->getNext();
        }
        cout << "Value not found" << endl;
        return false;
    }

    void remove(string value) {
        int hash = hashFunc(value, tableSize);
        if (vec[hash] != nullptr) {
            KeyValuePair* temp = vec[hash];
            if (temp->getValue() == value) {
                vec[hash] = temp->getNext();
                cout << "Removed value: " << value << endl;
                delete temp;
            }
            else {
                while (temp->getNext() != nullptr && temp->getNext()->getValue() != value)
                    temp = temp->getNext();

                if (temp->getNext() != nullptr) {
                    KeyValuePair* toDelete = temp->getNext();
                    cout << "Removed value: " << toDelete->getValue() << endl;
                    temp->setNext(toDelete->getNext());
                    delete toDelete;
                }
                else {
                    cout << "Value not found" << endl;
                }
            }
        }
        else {
            cout << "Value not found" << endl;
        }
    }

    void print() {
        for (int i = 0; i < tableSize; i++) {
            cout << "Slot " << i + 1 << ": ";
            KeyValuePair* temp = vec[i];
            while (temp != nullptr) {
                cout << temp->getValue();
                if (temp->getNext() != nullptr)
                    cout << " -> ";
                temp = temp->getNext();
            }
            cout << endl;
        }
    }
};


int main() {
    HashTable ht(10);
    int choice;
    string value;

    do {
        cout << "Choose an option:\n";
        cout << "1. Add a value\n";
        cout << "2. Search for a value\n";
        cout << "3. Remove a value\n";
        cout << "4. Print all values\n";
        cout << "5. Exit\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter a value to add: ";
            cin >> value;
            ht.add(value);
        }
        else if (choice == 2) {
            cout << "Enter a value to search for: ";
            cin >> value;
            ht.search(value);
        }
        else if (choice == 3) {
            cout << "Enter a value to remove: ";
            cin >> value;
            ht.remove(value);
        }
        else if (choice == 4) {
            ht.print();
        }
        else if (choice == 5) {
            cout << "Exiting the program...\n";
        }
        else {
            cout << "Unknown option. Try again.\n";
        }

    } while (choice != 5);
}
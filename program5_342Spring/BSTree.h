/*
Simple binary search tree class that has basic functions like insert retrieve etc for our client accounts
Utilizes recursive BSTree functions to help with the functions. Handles edge cases like an account already existing
negative account id, and if we are trying to print out the history for an empty client base. 
*/
#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"
#include <iostream>

class BSTree {
public:
    BSTree();
    BSTree(const BSTree& other);
    ~BSTree();

    bool Insert(Account* insert);
    bool Retrieve(const int& account_id, Account*& acc) const;
    void Display() const;

    void Empty();
    bool IsEmpty() const;

    BSTree& operator=(const BSTree& other);

private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Account* pAcct;
    };

    Node* root = nullptr;

    bool RecursiveInsert(Node*& cur, Account* insert);
    bool RecursiveRetrieve(Node* cur, const int& account_id, Account*& acc) const;
    void RecursiveDisplay(Node* cur) const;
    void RecursiveEmpty(Node*& cur);
    Node* RecursiveCopy(Node* cur) const;
};
#endif

#include "BSTree.h"

BSTree::BSTree() = default;

BSTree::BSTree(const BSTree &other)
{
    root = RecursiveCopy(other.root);
}

BSTree::~BSTree()
{
    Empty();
}

bool BSTree::Insert(Account *insert)
{
    if (insert == nullptr || insert->GetAccountID() < 0)
    {
        cerr << "ERROR: Could not insert. Invalid account or negative account ID." << endl;
        return false;
    }

    Account *temp = nullptr; //temp pointer for the account 
    if (RecursiveRetrieve(root, insert->GetAccountID(), temp))
    {
        cerr << "ERROR: Account ID " << insert->GetAccountID() << " already exists." << endl;
        return false;
    }

    return RecursiveInsert(root, insert);
}

bool BSTree::RecursiveInsert(Node *&cur, Account *insert)
{
    if (cur == nullptr)
    {
        cur = new Node{nullptr, nullptr, insert};
        return true;
    }

    if (insert->GetAccountID() < cur->pAcct->GetAccountID())
    {
        return RecursiveInsert(cur->left, insert);
    }
    else if (insert->GetAccountID() > cur->pAcct->GetAccountID())
    {
        return RecursiveInsert(cur->right, insert);
    }
    else
    {
        return false; // Account already exists
    }
}

bool BSTree::Retrieve(const int &account_id, Account *&acc) const
{
    if (account_id < 0)
    {
        cerr << "ERROR: Invalid negative account ID." << endl;
        return false;
    }

    bool found = RecursiveRetrieve(root, account_id, acc);
    return found;
}

bool BSTree::RecursiveRetrieve(Node *cur, const int &account_id, Account *&acc) const
{
    if (cur == nullptr)
    {
        acc = nullptr; // Set acc to nullptr to indicate account not found
        return false;
    }

    if (account_id == cur->pAcct->GetAccountID())
    {
        acc = cur->pAcct;
        return true;
    }
    else if (account_id < cur->pAcct->GetAccountID())
    {
        return RecursiveRetrieve(cur->left, account_id, acc);
    }
    else
    {
        return RecursiveRetrieve(cur->right, account_id, acc);
    }
}

void BSTree::Display() const
{
    if (IsEmpty())
    {
        cerr << "ERROR: Tree is empty." << endl;
        return;
    }

    RecursiveDisplay(root);
}

void BSTree::RecursiveDisplay(Node *cur) const
{
    if (cur != nullptr)
    {
        RecursiveDisplay(cur->left);
        cout << *(cur->pAcct) << endl;
        RecursiveDisplay(cur->right);
    }
}

void BSTree::Empty()
{
    RecursiveEmpty(root);
    root = nullptr;
}

void BSTree::RecursiveEmpty(Node *&cur)
{
    if (cur != nullptr)
    {
        RecursiveEmpty(cur->left);
        RecursiveEmpty(cur->right);
        delete cur->pAcct;
        delete cur;
        cur = nullptr;
    }
}

bool BSTree::IsEmpty() const
{
    return root == nullptr;
}

BSTree &BSTree::operator=(const BSTree &other)
{
    if (this != &other)
    {
        Empty();
        root = RecursiveCopy(other.root);
    }
    return *this;
}

BSTree::Node *BSTree::RecursiveCopy(Node *cur) const
{
    if (cur == nullptr)
    {
        return nullptr;
    }

    Node *NewNode = new Node{nullptr, nullptr, cur->pAcct};
    NewNode->left = RecursiveCopy(cur->left);
    NewNode->right = RecursiveCopy(cur->right);

    return NewNode;
}

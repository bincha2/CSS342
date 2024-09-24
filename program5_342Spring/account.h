/*
This class will implement what the fund and transaction classes and make them work coherently for a client account
the account can do the actions we implemented earlier, like deposit, withdraw, transfer, etc...
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "fund.h"
#include "transaction.h"
using namespace std;

class Account
{
public:
    // client accounts are represented by a first and last name (two strings) & a unique ID
    Account();
    Account(const string &first_name, const string &last_name, int acc_id);
    ~Account();

    // getters setters
    int GetAccountID() const;
    string GetFirstName() const;
    string GetLastName() const;

    // actions 
    bool Deposit(int fund_id, int amount);
    bool Withdraw(int fund_id, int amount);
    bool Transfer(int fund_id, int destination_fund_id, int amount, Account *destination_acc, int destination_acc_id);
    void TrackTransfer(int fund_id, int destination_fund_id, int amount, int destination_acc_id, bool inter_transfer);

    void DisplayAccountHistory() const;
    void DisplayFundHistory(int fund_id) const;

    friend ostream &operator<<(ostream &stream, const Account &acc);

private:
    int account_id_;
    string first_name_;
    string last_name_;

    // vector to store fund objects (8), each fund object has a transaction vector that stores transaction objects that are processed
    vector<Fund> funds_;

    // join account helper function for funds 0,1 & 2,3
    bool HandleLinkedFunds(int fund_id, int amount);
};
#endif
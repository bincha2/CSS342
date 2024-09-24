/*
This class deals with how a "transcation" is handled from the file
we convert the transaction to a transaction object so we can store it in the fund history, as well as process
user actions. The transactions is the starting point of the program, and funds hold transactions, accounts hold funds, and the tree holds accounts. 
*/

#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
using namespace std;

// enum for the transaction types, when we create a transaction obj we will use these names for ease of implementation, than we can use a switch statement to handle the types
enum TransactionType
{
    OPEN,
    DEPOSIT,
    WITHDRAW,
    TRANSFER,
    DISPLAY_CLIENT_HISTORY,
    DISPLAY_FUND_HISTORY
};

class Transaction
{
public:
    // default
    Transaction();
    ~Transaction();

    // handles deposits, withdraws, transfers, etc. Anything besides opening an account
    Transaction(TransactionType type, int acc_id, int fund_id, int amount, int destination_acc_id, int destination_fund_id, bool failed);
    // open account constructor
    Transaction(TransactionType type, int acc_id, const string &last_name, const string &first_name);

    // getters setters
    TransactionType GetType() const;
    int GetAccountID() const;
    int GetFundID() const;
    int GetAmount() const;
    int GetDestinationAccID() const;
    int GetDestinationFundID() const;
    string GetFirstName() const;
    string GetLastName() const;

    // helper function to track if transactions are failed or not
    bool IsFailed() const;
    void SetFailed(bool failed);

    // overload to display the transaction object and its contents
    friend ostream &operator<<(ostream &stream, const Transaction &tran);

private:
    TransactionType type_;
    int account_id_;
    int fund_id_;
    int amount_;
    int destination_account_id_;
    int destination_fund_id_;
    string first_name_;
    string last_name_;
    bool failed_;
};
#endif
/*
This class deals with the operations for a single fund within an accounts
we will store the "transaction" actions into a fund history holding transactions objects, since each fund will deal with 
actions for a transaction. The transaction obj has been overloaded to output correctly. Each fund obj will be overloaded, for when we store the fund objects in the fund history
vector in the account class
*/

#ifndef FUND_H_
#define FUND_H_
#include <vector>
#include <iostream>
#include <string>
#include "transaction.h"
using namespace std;

class Fund
{

public:
    // constructors destructors
    Fund();
    ~Fund();

    // actions
    int GetFundBalance() const;

    void SetFundName(string name);
    string GetFundName() const;

    bool DepositFunds(int amount);
    bool WithdrawFunds(int amount);

    void TrackFundHistory(Transaction tran);
    void DisplayFundHistory() const;

    // overload to display fund obj & balance
    friend ostream &operator<<(ostream &stream, const Fund &fund);

private:
    string fund_name_;
    int fund_balance_;
    vector<Transaction> fund_history_;
};
#endif
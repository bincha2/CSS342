#include "fund.h"

Fund::Fund()
{
    fund_name_ = "";
    fund_balance_ = 0;
}

Fund::~Fund()
{
    // default
}

int Fund::GetFundBalance() const
{
    return fund_balance_;
}

void Fund::SetFundName(string name)
{
    fund_name_ = name;
}

string Fund::GetFundName() const
{
    return fund_name_;
}

bool Fund::DepositFunds(int amount)
{
    fund_balance_ = fund_balance_ + amount;
    return true;
}

bool Fund::WithdrawFunds(int amount)
{
    if (amount <= fund_balance_)
    {
        fund_balance_ = fund_balance_ - amount;
        return true;
    }
    else
    {
        return false;
    }
}

void Fund::TrackFundHistory(Transaction tran)
{
    // each transaction "action" taken for a fund will be stored in a transaction obj vector
    fund_history_.push_back(tran);
}

void Fund::DisplayFundHistory() const
{
    for (int i = 0; i < fund_history_.size(); i++)
    {
        // overload << in transaction class so that DisplayFundHistory can properly output the "tran" (transaction) obj
        
        cout << fund_history_[i] << endl;
    }
}

// overload << for fund class, so that we can properly display a "fund" obj
ostream &operator<<(ostream &stream, const Fund &fund)
{
    stream << fund.GetFundName() << ": $" << fund.GetFundBalance();
    return stream;
}

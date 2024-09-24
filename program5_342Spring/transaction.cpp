#include "transaction.h"

Transaction::Transaction()
{
    // default
    type_ = OPEN;
    account_id_ = -1;
    fund_id_ = -1;
    amount_ = -1;
    destination_account_id_ = -1;
    destination_fund_id_ = -1;
    first_name_ = " ";
    last_name_ = " ";
    failed_ = false;
}

Transaction::~Transaction()
{
}

// transactions of all types besides OPEN
Transaction::Transaction(TransactionType type, int acc_id, int fund_id, int amount, int destination_acc_id, int destination_fund_id, bool failed)
{
    type_ = type;
    account_id_ = acc_id;
    fund_id_ = fund_id;
    amount_ = amount;
    destination_account_id_ = destination_acc_id;
    destination_fund_id_ = destination_fund_id;
    failed_ = false;
}

// OPEN account transaction
Transaction::Transaction(TransactionType type, int acc_id, const string &last_name, const string &first_name)
{
    type_ = type;
    account_id_ = acc_id;
    first_name_ = first_name;
    last_name_ = last_name;

    fund_id_ = -1;
    amount_ = 0;
    destination_account_id_ = -1;
    destination_fund_id_ = -1;
    failed_ = false;
}

TransactionType Transaction::GetType() const
{
    return type_;
}

int Transaction::GetAccountID() const
{
    return account_id_;
}

int Transaction::GetFundID() const
{
    return fund_id_;
}

int Transaction::GetAmount() const
{
    return amount_;
}

int Transaction::GetDestinationAccID() const
{
    return destination_account_id_;
}

int Transaction::GetDestinationFundID() const
{
    return destination_fund_id_;
}

string Transaction::GetFirstName() const
{
    return first_name_;
}

string Transaction::GetLastName() const
{
    return last_name_;
}

bool Transaction::IsFailed() const
{
    return failed_;
}

void Transaction::SetFailed(bool failed)
{
    failed_ = failed;
}

// Format transaction obj for output
ostream &operator<<(ostream &stream, const Transaction &tran)
{
    // check if a transaction has failed first
    if (tran.IsFailed())
    {
        switch (tran.type_)
        {
        case OPEN:
            stream << "\t O " << tran.account_id_ << " " << tran.GetLastName() << " " << tran.GetFirstName() << " (Failed)";
            break;
        case DEPOSIT:
            stream << "\t D " << tran.account_id_ << " " << tran.fund_id_ << " " << tran.amount_ << " (Failed)";
            break;
        case WITHDRAW:
            stream << "\t W " << tran.account_id_ << " " << tran.fund_id_ << " " << tran.amount_ << " (Failed)";
            break;
        case TRANSFER:
            stream << "\t T " << tran.account_id_ << " " << tran.destination_fund_id_ << " " << tran.destination_account_id_ << " " << tran.fund_id_ << " " << tran.amount_ << " (Failed)";
             break;
        case DISPLAY_CLIENT_HISTORY:
            stream << "\t A " << tran.account_id_ << " (Failed)";
            break;
        case DISPLAY_FUND_HISTORY:
            stream << "\t F " << tran.account_id_ << " " << tran.fund_id_ << " (Failed)";
            break;
        }
    }
    else
    {
        switch (tran.type_)
        {
        case OPEN:
            stream << "\t O " << tran.account_id_ << " " << tran.GetLastName() << " " << tran.GetFirstName();
            break;
        case DEPOSIT:
            stream << "\t D " << tran.account_id_ << " " << tran.fund_id_ << " " << tran.amount_;
            break;
        case WITHDRAW:
            stream << "\t W " << tran.account_id_ << " " << tran.fund_id_ << " " << tran.amount_;
            break;
        case TRANSFER:
            stream << "\t T " << tran.account_id_ << " " << tran.destination_fund_id_ << " " << tran.destination_account_id_ << " " << tran.fund_id_ << " " << tran.amount_;
             break;
        case DISPLAY_CLIENT_HISTORY:
            stream << "\t A " << tran.account_id_;
            break;
        case DISPLAY_FUND_HISTORY:
            stream << "\t F " << tran.account_id_ << " " << tran.fund_id_;
            break;
        }
    }
    return stream;
}
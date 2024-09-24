#include "account.h"

Account::Account() : funds_(8)
{
    // default
    first_name_ = " ";
    last_name_ = " ";
    account_id_ = -1;
    funds_[0].SetFundName("Money Market");
    funds_[1].SetFundName("Prime Money Market");
    funds_[2].SetFundName("Long-Term Bond");
    funds_[3].SetFundName("Short-Term Bond");
    funds_[4].SetFundName("500 Index Fund");
    funds_[5].SetFundName("Capital Value Fund");
    funds_[6].SetFundName("Growth Equity Fund");
    funds_[7].SetFundName("Growth Index Fund");
}

Account::Account(const string &first_name, const string &last_name, int acc_id) : funds_(8)
{
    first_name_ = first_name;
    last_name_ = last_name;
    account_id_ = acc_id;
    funds_[0].SetFundName("Money Market");
    funds_[1].SetFundName("Prime Money Market");
    funds_[2].SetFundName("Long-Term Bond");
    funds_[3].SetFundName("Short-Term Bond");
    funds_[4].SetFundName("500 Index Fund");
    funds_[5].SetFundName("Capital Value Fund");
    funds_[6].SetFundName("Growth Equity Fund");
    funds_[7].SetFundName("Growth Index Fund");
}

Account::~Account()
{
}

int Account::GetAccountID() const
{
    return account_id_;
}

string Account::GetFirstName() const
{
    return first_name_;
}

string Account::GetLastName() const
{
    return last_name_;
}

bool Account::Deposit(int fund_id, int amount)
{
    // check if fund id is valid (only funds 0-7 allowed)
    if (fund_id < 0 || fund_id >= 8)
    {
        cerr << "ERROR: The fund id " << fund_id << " does not exist in our bank" << endl;

        // creating tran object with failed marker marked as true to log into our fund history for that specific fund, do this for every transaction that failed so we can properly store in history
        Transaction tran(DEPOSIT, account_id_, fund_id, amount, -1, -1, false);
        tran.SetFailed(true);
        funds_[fund_id].TrackFundHistory(tran);
        return false;
    }
    else if (amount < 0)
    {
        cerr << "ERROR: The deposit amount " << amount << " cannot be negative. Transaction failed." << endl;
        Transaction tran(DEPOSIT, account_id_, fund_id, amount, -1, -1, false);
        tran.SetFailed(true);
        funds_[fund_id].TrackFundHistory(tran);
        return false;
    }
    else
    {
        funds_[fund_id].DepositFunds(amount);
        funds_[fund_id].TrackFundHistory(Transaction(DEPOSIT, account_id_, fund_id, amount, -1, -1, false));
        return true;
    }
}

bool Account::Withdraw(int fund_id, int amount)
{

    // check if fund id is valid and if amount is valid
    if (fund_id < 0 || fund_id >= 8)
    {
        cerr << "ERROR: The fund id " << fund_id << " does not exist in our bank" << endl;
        Transaction tran(WITHDRAW, account_id_, fund_id, amount, -1, -1, false);
        tran.SetFailed(true);
        funds_[fund_id].TrackFundHistory(tran);
        return false;
    }
    else if (amount < 0)
    {
        cerr << "ERROR: Cannot withdraw a negative amount from fund" << endl;
        Transaction tran(WITHDRAW, account_id_, fund_id, amount, -1, -1, false);
        tran.SetFailed(true);
        funds_[fund_id].TrackFundHistory(tran);
        return false;
    }

    //  withdrawing funds logic
    if (funds_[fund_id].WithdrawFunds(amount)) // if we can withdraw funds is true
    {
        funds_[fund_id].TrackFundHistory(Transaction(WITHDRAW, account_id_, fund_id, amount, -1, -1, false)); // store in history
        return true;
    }
    else if (HandleLinkedFunds(fund_id, amount)) // check to see if it is a join account and there is enough balance to cover the amount
    {
        funds_[fund_id].TrackFundHistory(Transaction(WITHDRAW, account_id_, fund_id, amount, -1, -1, false));
        return true;
    }
    else
    {
        cerr << "ERROR: Not enough funds to withdraw $" << amount << " from " << first_name_ << " " << last_name_ << " " << funds_[fund_id].GetFundName() << endl;
        Transaction tran(WITHDRAW, account_id_, fund_id, amount, -1, -1, false);
        tran.SetFailed(true);
        funds_[fund_id].TrackFundHistory(tran);
        return false;
    }
}

bool Account::Transfer(int fund_id, int destination_fund_id, int amount, Account *destination_acc, int destination_acc_id)
{
    if (fund_id < 0 || fund_id >= 8 || destination_fund_id < 0 || destination_fund_id >= 8)
    {
        cerr << "ERROR: Invalid fund ID." << endl;
        return false;
    }

    if (amount < 0)
    {
        cerr << "ERROR: Cannot transfer a negative amount." << endl;
        return false;
    }

    int FromFundBalance = funds_[fund_id].GetFundBalance();
    if (amount > FromFundBalance)
    {
        // Check if the fund_id is part of a joint account and handle linked funds
        if (!HandleLinkedFunds(fund_id, amount))
        {
            cerr << "ERROR: Insufficient balance in fund " << funds_[fund_id].GetFundName() << " of Client " << first_name_ << " " << last_name_ << " for transfer." << endl;
            return false;
        }
    }

    funds_[fund_id].WithdrawFunds(amount);
    if (this == destination_acc)
    {
        // same acc transfer
        funds_[destination_fund_id].DepositFunds(amount);
        TrackTransfer(fund_id, destination_fund_id, amount, destination_acc_id, false);
    }
    else
    {
        // diff acc transfer
        destination_acc->funds_[destination_fund_id].DepositFunds(amount);
        TrackTransfer(fund_id, destination_fund_id, amount, destination_acc_id, true);
        destination_acc->TrackTransfer(fund_id, destination_fund_id, amount, destination_acc_id, true);
    }

    return true;
}

void Account::TrackTransfer(int fund_id, int destination_fund_id, int amount, int destination_acc_id, bool inter_transfer)
{
    if (inter_transfer) // check to see if this was a inter transfer (one acc to another)
    {
        // Add the transfer transaction to the fund history of the "from" fund
        Transaction FromTransaction(TRANSFER, account_id_, destination_fund_id, amount, destination_acc_id, fund_id, false);
        funds_[fund_id].TrackFundHistory(FromTransaction);

        // Add the transfer transaction to the fund history of the "to" fund in the destination account
        Transaction ToTransaction(TRANSFER, destination_acc_id, destination_fund_id, amount, account_id_, fund_id, false);
        funds_[destination_fund_id].TrackFundHistory(ToTransaction);
    }
    else
    {
        // else it was a same account transfer and track it in the same account
        Transaction FromTransaction(TRANSFER, account_id_, destination_fund_id, amount, account_id_, fund_id, false);
        funds_[fund_id].TrackFundHistory(FromTransaction);

        Transaction ToTransaction(TRANSFER, account_id_, destination_fund_id, amount, account_id_, fund_id, false);
        funds_[destination_fund_id].TrackFundHistory(ToTransaction);
    }
}

void Account::DisplayAccountHistory() const
{
    cout << "Transaction History for " << first_name_ << " " << last_name_ << " by fund." << endl;
    for (int i = 0; i < funds_.size(); i++)
    {
        cout << funds_[i] << endl;
        funds_[i].DisplayFundHistory();
    }
}

void Account::DisplayFundHistory(int fund_id) const
{
    // check if fund exists
    if (fund_id < 0 || fund_id >= 8)
    {
        cerr << "Fund does not exist" << endl;
        return;
    }
    else
    {
        cout << "Transaction History for " << first_name_ << " " << last_name_ << " " << funds_[fund_id].GetFundName() << ": $" << funds_[fund_id].GetFundBalance() << endl;
        funds_[fund_id].DisplayFundHistory();
    }
}

bool Account::HandleLinkedFunds(int fund_id, int amount)
{
    if (fund_id == 0 || fund_id == 1)
    {
        int destination_fund_id = (fund_id == 0) ? 1 : 0; // Corresponding joint account
        int TotalBalance = funds_[fund_id].GetFundBalance() + funds_[destination_fund_id].GetFundBalance();
        if (amount <= TotalBalance)
        {
            int needed = amount - funds_[fund_id].GetFundBalance();
            if (needed > 0)
            {
                funds_[destination_fund_id].WithdrawFunds(needed);
                funds_[fund_id].DepositFunds(needed);
            }
            funds_[fund_id].WithdrawFunds(amount);
            return true;
        }
    }
    else if (fund_id == 2 || fund_id == 3)
    {
        int destination_fund_id = (fund_id == 2) ? 3 : 2; // Corresponding joint account
        int TotalBalance = funds_[fund_id].GetFundBalance() + funds_[destination_fund_id].GetFundBalance();
        if (amount <= TotalBalance)
        {
            int needed = amount - funds_[fund_id].GetFundBalance();
            if (needed > 0)
            {
                funds_[destination_fund_id].WithdrawFunds(needed);
                funds_[fund_id].DepositFunds(needed);
            }
            funds_[fund_id].WithdrawFunds(amount);
            return true;
        }
    }
    return false;
}

ostream &operator<<(ostream &stream, const Account &acc)
{
    stream << acc.GetFirstName() << " " << acc.GetLastName() << " Account ID: " << acc.GetAccountID() << endl;
    // display funds & their balance for acc, overloaded funds obj earlier to display name and balance
    for (int i = 0; i < 8; i++)
    {
        cout << "\t" << acc.funds_[i] << endl;
    }

    return stream;
}

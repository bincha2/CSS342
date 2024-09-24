#include "jolly_banker.h"

JollyBanker::JollyBanker() = default;

void JollyBanker::ReadTransaction(const string &filename)
{

    // open file, check to see if it is a valid file
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "ERROR: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        char type;
        int account_id;
        int fund_id;
        int amount;
        int destination_acc_id = -1;
        int destination_fund_id = -1;
        string first_name;
        string last_name;

        // read in the type of transaction from the file, than based on type create the corresponding transaction object to store in the transaction object queue
        iss >> type;
        switch (type)
        {
        case 'O':
            iss >> account_id >> first_name >> last_name;
            transactions.push(Transaction(OPEN, account_id, first_name, last_name));
            break;
        case 'D':
            iss >> account_id >> fund_id >> amount;
            transactions.push(Transaction(DEPOSIT, account_id, fund_id, amount, -1, -1, false));
            break;
        case 'W':
            iss >> account_id >> fund_id >> amount;
            transactions.push(Transaction(WITHDRAW, account_id, fund_id, amount, -1, -1, false));
            break;
        case 'T':
            iss >> account_id >> fund_id >> destination_acc_id >> destination_fund_id >> amount;
            transactions.push(Transaction(TRANSFER, account_id, fund_id, amount, destination_acc_id, destination_fund_id, false));
            break;
        case 'A':
            iss >> account_id;
            transactions.push(Transaction(DISPLAY_CLIENT_HISTORY, account_id, -1, -1, -1, -1, false));
            break;
        case 'F':
            iss >> account_id >> fund_id;
            transactions.push(Transaction(DISPLAY_FUND_HISTORY, account_id, fund_id, -1, -1, -1, false));
            break;
        default: // handle any other types of transactions besides O, D, W, T, A, and F as our bank cant do that
            cerr << "ERROR: Unknown transaction type " << type << endl;
            break;
        }
    }
}

void JollyBanker::ProcessTransactions()
{
    while (!transactions.empty())
    {
        Transaction transaction = transactions.front();
        transactions.pop();
        Account *account = nullptr;
        Account *destination_acc = nullptr;

        switch (transaction.GetType())
        {
        case OPEN:
            if (!accounts.Retrieve(transaction.GetAccountID(), account)) // see if account exists
            {
                if (account == nullptr)
                {
                    // Account does not exist, proceed with opening a new account
                    account = new Account(transaction.GetFirstName(), transaction.GetLastName(), transaction.GetAccountID());
                    if (!accounts.Insert(account))
                    {
                        delete account;
                    }
                }
            }
            else
            {
                // Account already exists
                cerr << "ERROR: Account ID " << transaction.GetAccountID() << " already exists." << endl;
            }
            break;
        case DEPOSIT:
            if (accounts.Retrieve(transaction.GetAccountID(), account))
            {
                account->Deposit(transaction.GetFundID(), transaction.GetAmount());
            }
            else
            {
                cerr << "ERROR: Account ID " << transaction.GetAccountID() << " not found." << endl;
            }
            break;
        case WITHDRAW:
            if (accounts.Retrieve(transaction.GetAccountID(), account))
            {
                account->Withdraw(transaction.GetFundID(), transaction.GetAmount());
            }
            else
            {
                cerr << "ERROR: Account ID " << transaction.GetAccountID() << " not found." << endl;
            }
            break;
        case TRANSFER:
            if (accounts.Retrieve(transaction.GetAccountID(), account) && accounts.Retrieve(transaction.GetDestinationAccID(), destination_acc)) // check if the 2 accounts exists in our tree
            {
                if (account->Transfer(transaction.GetFundID(), transaction.GetDestinationFundID(), transaction.GetAmount(), destination_acc, transaction.GetDestinationAccID()))
                {
                    // transfer function handles any joint account logic as well, with help of handle linked funds function and using prev withdraw and deposit functions. Helper function TrackTransfer exists to help with tracking same or diff client transfers
                }
                else
                {
                    cerr << "ERROR: Transfer failed. Not Enough Funds" << endl;
                }
            }
            else
            {
                cerr << "ERROR: Cannot transfer $" << transaction.GetAmount() << " As Account ID: " << transaction.GetAccountID() << " or " << transaction.GetDestinationAccID() << " is not found." << endl;
            }
            break;
        case DISPLAY_CLIENT_HISTORY:
            if (accounts.Retrieve(transaction.GetAccountID(), account))
            {
                account->DisplayAccountHistory();
            }
            else
            {
                cerr << "ERROR: Account ID " << transaction.GetAccountID() << " not found." << endl;
            }
            break;
        case DISPLAY_FUND_HISTORY:
            if (accounts.Retrieve(transaction.GetAccountID(), account))
            {
                account->DisplayFundHistory(transaction.GetFundID());
            }
            else
            {
                cerr << "ERROR: Account ID " << transaction.GetAccountID() << " not found." << endl;
            }
            break;
        default:
            cerr << "ERROR: Unknown transaction type." << endl;
            break;
        }
    }
}

void JollyBanker::DisplayAccounts() const
{
    accounts.Display();
}

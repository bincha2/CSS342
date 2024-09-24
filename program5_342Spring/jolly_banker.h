/*
JollyBanker class is how everything works together. Transactions work to help funds work, funds work to help accounts work, accounts work to help the BSTree work, and 
now BSTree works to help jolly banker work. This class now is in charge of reading in and storing the string into a queue
the queue now goes in order to create transaction objects from earlier, the transaction objects are created based on TYPE. 
Process transactions will execute these trans objects using functions created earlier in account.h
Once everything is complete, Phase 3, display the history and final balances for each client in the bank through display accounts. this will just
call display from the bstree for the accounts bstree. Account obj has been overloaded to output correctly, and the fund obj, trans obj and so forth.
*/

#ifndef JOLLY_BANKER_
#define JOLLY_BANKER_
#include "BSTree.h"
#include "transaction.h"
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class JollyBanker
{
public:
    JollyBanker();
    void ReadTransaction(const string &filename);
    void ProcessTransactions();
    void DisplayAccounts() const;

private:
    BSTree accounts;                 // BSTree to hold the client accs
    queue<Transaction> transactions; // queue that holds transactions objs, the transaction class knows how to create and deal with the actions of the transaction through the type enum, and switch cases
};
#endif

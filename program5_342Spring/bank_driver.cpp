/*
DAVID KIM - PROGRAM 5 JOLLY BANKER - 342 Spring 24 DIMPSEY
-
THIS IS THE DRIVER CODE USED TO EXECUTE THE JOLLY BANKER CLASS.
-
The Jolly Banker class has the functions read, process, and display the transactions of a given file. Jolly Banker utilizes the other classes
such as account, bstree, fund, and transaction to coheisvely work together, process, and output these transactions.
*/

#include "jolly_banker.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "No file provided" << endl;
        return 0;
    }
    else
    {
        JollyBanker employee;
        string file_name = argv[1];

        employee.ReadTransaction(file_name); 
        employee.ProcessTransactions();
        cout << "FINAL BALANCES:" << endl;
        employee.DisplayAccounts();
        return 0;
    }
}

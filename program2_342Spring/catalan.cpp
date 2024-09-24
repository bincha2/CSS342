/*
CATALAN BY DAVID KIM - DIMPSEY 342
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int Catalan(int n);

int main(int argc, char* argv[])
{
    int n = stoi(argv[1]);
    cout << Catalan(n) << endl;
}

int Catalan(int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n < 0)
    {
        cout << "Please enter a valid positive integer" << endl;
        return -1;
    }
    if (n >=20)
    {
        cout << "Entered value is too large to compute catalan" << endl;
        return -1;
    }
    else
    {
        int result = 0; 
        for (int i = 0; i < n; i++)
        {
            result += (Catalan(i) * Catalan(n - i - 1));
        }
        return result;
    }
}

// David Kim - Program 1 Vending Bank - 342 Spring 24 Dimpsey
#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>
using namespace std;

class VendingBank
{
public:
    // constructors
    VendingBank();
    VendingBank(int id);
    VendingBank(int id, double balance);
    VendingBank(int id, double pen, double nick, double dime, double quarter, double half_doll, double doll_coin);

    // getters
    int id() const;
    double GetBalance() const;
    double GetPen() const;
    double GetNick() const;
    double GetDime() const;
    double GetQuarter() const;
    double GetHalfDoll() const;
    double GetDollCoin() const;

    // setters
    bool SetID(int id_);
    bool SetBalance(double new_balance);

    // actions
    void ClearBalance();
    double ComputeBalance() const;
    bool AddCoins(double pen, double nick, double dime, double quarter, double half_doll, double doll_coin);
    bool DeductCoins(double pen, double nick, double dime, double quarter, double half_doll, double doll_coin);

    // op-overloads for bank
    VendingBank operator+(const VendingBank &bank) const;
    VendingBank &operator+=(const VendingBank &bank);
    VendingBank operator-(const VendingBank &bank) const;
    VendingBank &operator-=(const VendingBank &bank);

    // stream overload to display bank contents
    friend ostream &operator<<(ostream &stream, const VendingBank &bank);

private:
    // data types
    int id_;
    double balance_;
    double penn_;
    double nick_;
    double dime_;
    double quarter_;
    double half_doll_;
    double doll_coin_;
};
#endif
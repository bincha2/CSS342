// David Kim - Program 1 TimeSpan - 342 Spring 24 Dimpsey
#ifndef TIME_SPAN_H_
#define TIME_SPAN_H_
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class TimeSpan
{
public:
    // constructors
    TimeSpan();
    TimeSpan(double seconds);
    TimeSpan(double minutes, double seconds);
    TimeSpan(double hours, double minutes, double seconds);

    // getters
    int seconds() const;
    int minutes() const;
    int hours() const;

    // setter
    void set_time(int hours, int minutes, int seconds);

    // conversion action
    void TotalSeconds(const double hours, const double minutes, const double seconds);

    // operator overloads
    TimeSpan operator+(const TimeSpan &time) const;
    TimeSpan &operator+=(const TimeSpan &time);

    TimeSpan operator-(const TimeSpan &time) const;
    TimeSpan &operator-=(const TimeSpan &time);

    // unary negation
    TimeSpan operator-() const;

    // comparison overloads
    bool operator==(const TimeSpan &time) const;
    bool operator!=(const TimeSpan &time) const;
    bool operator<(const TimeSpan &time) const;
    bool operator<=(const TimeSpan &time) const;
    bool operator>(const TimeSpan &time) const;
    bool operator>=(const TimeSpan &time) const;

    // stream overloads
    friend ostream &operator<<(ostream &stream, const TimeSpan &time);
    friend istream &operator>>(istream &stream, TimeSpan &time);

private:
    int seconds_;
    int minutes_;
    int hours_;
};
#endif
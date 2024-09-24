// David Kim - Program 1 TimeSpan - 342 Spring 24 Dimpsey
#include "time_span.h"

// constructors
TimeSpan::TimeSpan()
{
    seconds_ = 0;
    minutes_ = 0;
    hours_ = 0;
}

TimeSpan::TimeSpan(double seconds)
{
    TotalSeconds(0, 0, seconds);
}

TimeSpan::TimeSpan(double minutes, double seconds)
{
    TotalSeconds(0, minutes, seconds);
}

TimeSpan::TimeSpan(double hours, double minutes, double seconds)
{
    TotalSeconds(hours, minutes, seconds);
}

// getters
int TimeSpan::seconds() const
{
    return seconds_;
}

int TimeSpan::minutes() const
{
    return minutes_;
}

int TimeSpan::hours() const
{
    return hours_;
}

// setter
void TimeSpan::set_time(int hours, int minutes, int seconds)
{
    seconds_ = seconds;
    minutes_ = minutes;
    hours_ = hours;
}

// convert function
void TimeSpan::TotalSeconds(const double hours, const double minutes, const double seconds)
{
    // find total secs
    int total_seconds = round((hours * 3600) + (minutes * 60) + seconds);

    // convert to hours, mins, secs
    hours_ = (total_seconds / 3600);
    minutes_ = ((total_seconds % 3600) / 60);
    seconds_ = ((total_seconds % 3600) % 60);
}

// addition overload
TimeSpan TimeSpan::operator+(const TimeSpan &time) const
{
    TimeSpan converted;
    converted.seconds_ = seconds_ + time.seconds_;
    converted.minutes_ = minutes_ + time.minutes_;
    converted.hours_ = hours_ + time.hours_;

    // converts for exceeding 60 values
    converted.minutes_ += converted.seconds_ / 60;
    converted.seconds_ %= 60;

    converted.hours_ += converted.minutes_ / 60;
    converted.minutes_ %= 60;

    return converted;
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &time)
{
    seconds_ += time.seconds_;
    minutes_ += time.minutes_;
    hours_ += time.hours_;

    // converts for exceeding 60 values
    minutes_ += seconds_ / 60;
    seconds_ %= 60;

    hours_ += minutes_ / 60;
    minutes_ %= 60;

    return *this;
}

// subtraction overload
TimeSpan TimeSpan::operator-(const TimeSpan &time) const
{
    TimeSpan converted;
    converted.seconds_ = seconds_ - time.seconds_;
    converted.minutes_ = minutes_ - time.minutes_;
    converted.hours_ = hours_ - time.hours_;

    // If sec, min, hr is neg, convert as necessary
    if (converted.seconds_ < 0)
    {
        converted.seconds_ += 60;
        converted.minutes_--;
    }
    if (converted.minutes_ < 0)
    {
        converted.minutes_ += 60;
        converted.hours_--;
    }
    if (converted.hours_ < 0)
    {
        // If hours are negative, TimeSpan is invalid / -1
        converted.hours_ = -1;
        converted.minutes_ = -1;
        converted.seconds_ = -1;
    }

    return converted;
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &time)
{
    seconds_ -= time.seconds_;
    minutes_ -= time.minutes_;
    hours_ -= time.hours_;

    // If sec, min, hr is neg, convert as necessary
    while (seconds_ < 0)
    {
        seconds_ += 60;
        minutes_--;
    }
    while (minutes_ < 0)
    {
        minutes_ += 60;
        hours_--;
    }
    if (hours_ < 0)
    {
        // If hours are negative, TimeSpan is invalid / -1
        hours_ = -1;
        minutes_ = -1;
        seconds_ = -1;
    }

    return *this;
}

// unary negation
TimeSpan TimeSpan::operator-() const
{
    TimeSpan converted;

    converted.seconds_ = seconds_ * -1;
    converted.minutes_ = minutes_ * -1;
    converted.hours_ = hours_ * -1;

    return converted;
}

// comparison operator overloads
bool TimeSpan::operator==(const TimeSpan &time) const
{
    return (hours_ == time.hours_) && (minutes_ == time.minutes_) && (seconds_ == time.seconds_);
}

bool TimeSpan::operator!=(const TimeSpan &time) const
{
    return !(*this == time);
}

bool TimeSpan::operator<(const TimeSpan &time) const
{
    if (hours_ != time.hours_)
    {
        return hours_ < time.hours_;
    }
    else if (minutes_ != time.minutes_)
    {
        return minutes_ < time.minutes_;
    }
    else
    {
        return seconds_ < time.seconds_;
    }
}

bool TimeSpan::operator<=(const TimeSpan &time) const
{
    return (*this < time) || (*this == time);
}

bool TimeSpan::operator>(const TimeSpan &time) const
{
    return !(*this <= time);
}

bool TimeSpan::operator>=(const TimeSpan &time) const
{
    return !(*this < time);
}

// output stream operator overload
ostream &operator<<(ostream &stream, const TimeSpan &time)
{
    stream << "Hours: " << time.hours_ << ", Minutes: " << time.minutes_ << ", Seconds: " << time.seconds_ << endl;
    return stream;
}

// input stream operator overload
istream &operator>>(istream &stream, TimeSpan &time)
{
    double hours, minutes, seconds;
    stream >> hours >> minutes >> seconds;
    time.TotalSeconds(hours, minutes, seconds);
    return stream;
}

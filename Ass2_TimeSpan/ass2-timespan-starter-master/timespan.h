//
// Created by Kez in F19.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <cmath>
#include <iostream>

using namespace std;

class TimeSpan {
    friend ostream &operator<<(ostream &Out, const TimeSpan &Ts);

public:
    // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
    explicit TimeSpan(double Hour = 0, double Minute = 0, double Second = 0);

    virtual ~TimeSpan() = default;

    // add
    TimeSpan operator+(const TimeSpan &Ts) const;

    // Change this value to the value of this plus Ts
    TimeSpan& operator+=(const TimeSpan& Ts);

    // subtract
    TimeSpan operator-(const TimeSpan &Ts) const;

    // Change this value to the value of this minus Ts
    TimeSpan& operator-=(const TimeSpan& Ts);

    // check equality
    bool operator==(const TimeSpan &Ts) const;

    // check if not equal
    bool operator!=(const TimeSpan &Ts) const;

    // check inequality less than or equal
    bool operator<=(const TimeSpan &Ts) const;

    // check inequality greater than or equal
    bool operator>=(const TimeSpan &Ts) const;

    // check inequality less than
    bool operator<(const TimeSpan &Ts) const;

    // check inequality greater than
    bool operator>(const TimeSpan &Ts) const;

    // multiply timespan by a number
    TimeSpan operator*(int Number);

private:
    int Second = 0;
    int Minute = 0;
    int Hour = 0;

    // Answers: This timespan is negative? T/F
    bool Negative = false;

    // Round a double to the nearest int
    static int round(double Num);

    // safely set the second, minute and hour with total seconds
    void setTime(double TotalSeconds);

    // ensures that all values are of one sign +/-
    void convertSigns();

    // Simplifies time if possible
    void simplify();

    // increments larger measure of time if smaller measure exceeds 60 (works for negative numbers too)
    static void simplify(int *Smaller, int *Larger);

    //converts all time to seconds, returning that value.
    int toSeconds() const;

};
#endif //ASS2_TIMESPAN_H


//
// Created by Kez in F19.
//

#include "timespan.h"

// Constructor: default values are zero. Changes internal values to simplest form.
// values converted to same sign +/-
TimeSpan::TimeSpan(double Hour, double Minute, double Second) {
    double TotalSeconds = Second
                        + (Minute * 60)
                        + (Hour * 60 * 60);
    setTime(TotalSeconds);
}

/**
 *  Data members are set to simplest version of given TotalSeconds
 * */
void TimeSpan::setTime(double TotalSeconds) {
    TimeSpan::Second = round(TotalSeconds);
    convertSigns();
    simplify();
}

/**
 *  Returns the rounded int of the given double
 * */
int TimeSpan::round(double Num) {
    if (Num < 0) {
        return static_cast<int> (Num - 0.5); // I am okay with the warning here
    }
    return static_cast<int> (Num + 0.5); // and here
}

/**
 *  Helper method identifies the sign +/- of this timespan
 *  Useful to operator<<
 * */
void TimeSpan::convertSigns() {
    if(Second < 0){
        Negative = true;
        Second *= -1;
    }
}

/**
 *  If more than 60 seconds, simplifies into minutes and seconds.
 *  If more than 60 minutes, simplifies to hours, minutes, and seconds.
 * */
void TimeSpan::simplify() {
    simplify(&Second, &Minute);
    simplify(&Minute, &Hour);
}

/**
 *  Helper saves repeat code in simplify()
 * */
void TimeSpan::simplify(int *Smaller, int *Larger) {
    if(*Smaller >= 60 || *Smaller <= -60){
        *Larger += (*Smaller / 60);
        *Smaller = *Smaller % 60;
    }
}

//Defines how a Timespan object is input to an output stream.
ostream &operator<<(ostream &Out, const TimeSpan &Ts) {
    if(Ts.Negative){
        Out << "-";
    }
    Out << Ts.Hour << ":";

    if (10 > Ts.Minute && Ts.Minute > -10){
        Out << 0;
    }
    Out << Ts.Minute << ":";

    if (10 > Ts.Second && Ts.Second > -10){
        Out << 0;
    }
    Out << Ts.Second;

  return Out;
}

// defines how to add timespans
TimeSpan TimeSpan::operator+(const TimeSpan &Ts) const {
  TimeSpan TsSum(0, 0, toSeconds() + Ts.toSeconds() );
  return TsSum;
}

/**
 * Converts Timespan (hours, minutes, seconds) to seconds
 * */
int TimeSpan::toSeconds() const{
    int TotalSeconds = Second;
    TotalSeconds += Hour * 60 * 60;
    TotalSeconds += Minute * 60;
    if (Negative){
        TotalSeconds *= -1;
    }
    return TotalSeconds;
}

//defines how to subtract timespans
TimeSpan TimeSpan::operator-(const TimeSpan &Ts) const {
TimeSpan TsSub(0, 0, toSeconds() - Ts.toSeconds() );
  return TsSub;
}

// defines how to multiply a timespan by an int
TimeSpan TimeSpan::operator*(int Number) {
  TimeSpan TsLarge(0, 0, toSeconds() * Number );
  return TsLarge;
}

// checks equality
bool TimeSpan::operator==(const TimeSpan &Ts) const {
  return toSeconds() == Ts.toSeconds();
}

// checks not equal
bool TimeSpan::operator!=(const TimeSpan &Ts) const {
  return !(*this == Ts);
}

// updates this timespan to this plus Ts
TimeSpan &TimeSpan::operator+=(const TimeSpan &Ts) {
    *this = *this + Ts;
    return *this;
}

// updates this timespan to this minus Ts
TimeSpan &TimeSpan::operator-=(const TimeSpan &Ts) {
    *this = *this - Ts;
    return *this;
}

// checks if this timespan is less than or equal to Ts
bool TimeSpan::operator<=(const TimeSpan &Ts) const {
    return !(*this > Ts);
}

// checks if this timespan is greater than or equal to Ts
bool TimeSpan::operator>=(const TimeSpan &Ts) const {
    return !(*this < Ts);
}

// checks if this timespan is less than Ts
bool TimeSpan::operator<(const TimeSpan &Ts) const {
    return toSeconds() < Ts.toSeconds();
}

// checks if this timespan is greater than Ts
bool TimeSpan::operator>(const TimeSpan &Ts) const {
    return toSeconds() > Ts.toSeconds();
}


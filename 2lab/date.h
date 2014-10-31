#pragma once
#include<string>
#include<iostream>

namespace lab2 {

  class Date {
  public:
    virtual Date& operator=(const Date& other) = 0;

    virtual int year()            const = 0;
    virtual int month()           const = 0;
    virtual int day()             const = 0;
    virtual int week_day()        const = 0;
    virtual int days_per_week()   const = 0;
    virtual int days_this_month() const = 0;
    virtual int months_per_year() const = 0;

    virtual std::string week_day_name() const = 0;
    virtual std::string month_name()    const = 0;

    virtual int mod_julian_day() const = 0;

    int  operator- (const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator< (const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator> (const Date& other) const;
    bool operator>=(const Date& other) const;

    virtual Date& operator++() = 0;
    virtual Date& operator--() = 0;
    virtual Date& operator+=(int) = 0;
    virtual Date& operator-=(int) = 0;

    virtual Date& add_year (int years  = 1) = 0;
    virtual Date& add_month(int months = 1) = 0;
  };

  std::ostream& operator<<(std::ostream&, const Date&);

}

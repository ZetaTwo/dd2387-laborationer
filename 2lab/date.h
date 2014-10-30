#pragma once
#include<string>
#include<iostream>

namespace lab2 {

class Date {
protected:
  int mjd_offset;
public:

  Date();
  explicit Date(int mjd_offset);
  Date(const Date& original);

  virtual Date& operator=(const Date& other);

  virtual int year()            const = 0;
  virtual int month()           const = 0;
  virtual int day()             const = 0;
  virtual int week_day()        const = 0;
  virtual int days_per_week()   const = 0;
  virtual int days_this_month() const = 0;
  virtual int months_per_year() const = 0;

  virtual std::string week_day_name() const = 0;
  virtual std::string month_name()    const = 0;

  int mod_julian_day() const;

  int  operator- (const Date& other) const;
  bool operator==(const Date& other) const;
  bool operator!=(const Date& other) const;
  bool operator< (const Date& other) const;
  bool operator<=(const Date& other) const;
  bool operator> (const Date& other) const;
  bool operator>=(const Date& other) const;

  virtual Date& operator++();
  virtual Date& operator--();
  virtual Date& operator+=(int);
  virtual Date& operator-=(int);

  virtual Date& add_year (int years  = 1) = 0;
  virtual Date& add_month(int months = 1) = 0;
};

std::ostream& operator<<(std::ostream&, const Date&);

}

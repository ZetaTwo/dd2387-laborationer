#!/usr/bin/python

from math import floor
from sys import argv, exit

def mjd(year, month, day):
    """Compute the modified Julian day number of the given day in the Gregorian calendar"""
    a = floor((14 - month) / 12)
    y = year + 4800 - a
    m = month + 12 * a - 3
    return day + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - floor(y / 100) + floor(y / 400) - 32045 - 2400001

def mjd_jul(year, month, day) :
    """Compute the modified Julian day number of the given day in the Julian calendar"""
    a = floor((14 - month) / 12)
    y = year + 4800 - a
    m = month + 12 * a - 3
    return day + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - 32083 - 2400001

USAGE = "Usage: mod_julian_day.py YEAR MONTH DAY"
if __name__ == "__main__":
    if len(argv) > 1:
        if len(argv) > 3:
            try:
                print(mjd(int(argv[1]), int(argv[2]), int(argv[3])))
            except Error:
                print(USAGE)
                exit(1)
        else:
            print(USAGE)
            exit(1)

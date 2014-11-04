#!/usr/bin/python

from math import floor
from sys import argv, exit

def mjd(year, month, day):
    a = floor((14 - month) / 12)
    y = year + 4800 - a
    m = month + 12 * a - 3
    return day + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - floor(y / 100) + floor(y / 400) - 32045 - 2400001

USAGE = "Usage: mod_julian_day.py YEAR MONTH DAY"
if __name__ == "__main__":
    if(len(argv) > 3):
        try:
            print(mjd(int(argv[1]), int(argv[2]), int(argv[3])))
        except Error:
            print(USAGE)
            exit(1)
    else:
        print(USAGE)

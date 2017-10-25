#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsedate.h"

/**
* parsedate.c - This is my solution to the first lab of eecs2031...
*
* Author: Sohrab Oryakhel
* Student Number: 214302145
* Date: 2017/09/13
*
*
*
* This c file consists of three function each of which take a date argument formatted as "XXXX/YY/ZZ" as an array of chars and returns the corresponding part (day, month, year) of the date as an int.
*
*/

int parse_year(const char *buf)
{
	int year;
    sscanf(buf, "%d/%*d/%*d", &year);
	return year;
}

int parse_month(const char *buf)
{
	int month;
	sscanf(buf, "%*d/%d/%*d", &month);
	return month;
}


int parse_day(const char *buf)
{
	int day;
    sscanf(buf, "%*d/%*d/%d", &day);
	return day;
}


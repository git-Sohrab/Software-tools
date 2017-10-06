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
	char year[4];
	int i;

	memset(year, '\0', sizeof(year));

	for (i = 0; i < 4; i++){
		year[i] = buf[i];
	}
	return atoi(year);
}

int parse_month(const char *buf)
{
	char month[3];
	int monthIndex = 0;
	int i;

	memset(month, '\0', sizeof(month));

	for (i = 5; i < strlen(buf); i++) {
		if (buf[i] == '/') {
			break;
		}
		else {
			month[monthIndex] = buf[i];
			monthIndex++;
		}
	}
	return atoi(month);
}


int parse_day(const char *buf)
{
	char day[3];
	int dayIndex = 0;
	int i;

	memset(day, '\0', sizeof(day));

	for (i = 7; i < strlen(buf); i++) {
		if (buf[i] != '/') {
			day[dayIndex] = buf[i];
			dayIndex++;
		}
	}
	return atoi(day);
}


#pragma once
#ifndef _COURSE_H_
#define _COURSE_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;
enum dayofweek
{
	Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
};
struct dateofyear
{
	string day;
	string month;
	string year;
};
struct timeofday
{
	string hour;
	string minute;
};
struct CourseYear
{
	string yearStart;
	string yearEnd;
};
struct course
{
	string CourseCode;
	CourseYear Year;
	int semester;
	string CourseName;
	string Lecturer;
	dateofyear DateStart;
	dateofyear DateEnd;
	timeofday TimeStart;
	timeofday TimeEnd;
	dayofweek day;
	int period;
};
struct nodecourse
{
	nodecourse* next;
	course data;
};
dateofyear StrToDate(string s);
timeofday StrToTime(string s);
dayofweek StrToDay(string s);
CourseYear StrToYear(string s);
int StrToPeriod(string a, string b);
string IntToStr(int s);
#endif // !_COURSE_H_

#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
#include <iomanip>
#include <time.h>
#include "Course.h"
#include <sstream>
using namespace std;

bool cmpTime(string a, string b);
dayofweek TimeToDay(int x);
int TimeToPeriod(string s);
void ViewScore(string ID);
void ViewScheduleStudent(string ID);
void CheckIn(string ID);
void ViewCheckInStudent(string ID);
void DesignStudent(string username, string password);
#endif // _ACADEMICSTAFF_H_


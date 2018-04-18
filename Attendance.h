#pragma once
#ifndef _ATTENDANCE_H_
#define _ATTENDANCE_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

struct attendance
{
	string ID;
	string fullname;
	string w[10];
};

struct nodeattendance
{
	attendance data;
	nodeattendance *next;
};

#endif // !_ATTENDANCE_H_

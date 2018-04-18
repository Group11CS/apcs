#pragma once
#ifndef _LECTURER_H_
#define _LECTURER_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
#include "Class.h"
#include "Course.h"
#include "Scoreboard.h"
#include "Attendance.h"
using namespace std;

void ImportScoreboard(int n, string username);
void ViewScoreboard(string Class, string course, nodescoreboard *cur);
void ViewCheckIn(string Class, string course, nodeattendance *cur);
void DesignLecturer(string username, string password);
#endif // _ACADEMICSTAFF_H_


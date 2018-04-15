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
using namespace std;

struct scoreboard {
	string ID;
	string fullname;
	float midterm;
	float final;
	float lab;
	float bonus;
	float total;
};
struct nodescoreboard {
	scoreboard data;
	nodescoreboard *next;
};

void ImportScoreboard(int n);
void ViewScoreboard(string Class, string course, nodescoreboard *cur);
void DesignLecturer(string username, string password);
#endif // _ACADEMICSTAFF_H_


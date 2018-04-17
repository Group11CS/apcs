#pragma once
#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
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
#endif // !_SCOREBOARD_H_

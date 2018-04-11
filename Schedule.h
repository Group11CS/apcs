#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
#include "Course.h"
using namespace std;

struct schedule
{
	string c[4][6];
};

void MakeSchedule(nodecourse *phead, string Class);
void ImportSchedule(int n);
void EditSchedule(nodecourse *&phead, schedule &sche);
void ViewSchedule(schedule a);
#endif // !_SCHEDULE_H_

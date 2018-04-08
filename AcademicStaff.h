#ifndef _ACADEMICSTAFF_H_
#define _ACADEMICSTAFF_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
#include "Course.h"
using namespace std;
struct student {
	string name;
	string MSSV;
};
struct nodestudent {
	nodestudent* next;
	student data;
};
void inputstudentlist(int n);
void ImportCourse(int n);
void ViewListofCourse(nodecourse *phead);
void AddNewCourse(nodecourse *&phead, string Class);
void DeleteCourse(nodecourse *&phead, string Class);
void DesignAcademicStaff(string username, string password);
#endif // _ACADEMICSTAFF_H_

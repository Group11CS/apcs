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
#include "Class.h"
using namespace std;
struct student {
	string name;
	string MSSV;
};
struct nodestudent {
	nodestudent* next;
	student data;
};
void ReleaseStudent(nodestudent *&phead);
void ReleaseCourse(nodecourse *&phead);
void ReleaseClass(listclass *&phead);
void Importstudentlist(int n);
void AddStudent(nodestudent *&phead, string Class);
void EditStudent(nodestudent *&phead, string Class);
void RemoveStudent(nodestudent *&phead, string Class);
void ChangeStudent();
void ExportClass(nodestudent *cur, string Class);
void AddEmptyClass(listclass *&phead);
void ViewListofStudent(nodestudent *cur, string Class);
void ImportCourse(int n);
void ViewListofCourse(nodecourse *phead);
void AddNewCourse(nodecourse *&phead, string Class);
void RemoveCourse(nodecourse *&phead, string Class);
void ExportCourse(nodecourse *cur, string Class);
void MakeSchedule(nodecourse *phead, string Class);
void SearchViewScoreboard(int n);
void DesignAcademicStaff(string username, string password);
#endif // _ACADEMICSTAFF_H_

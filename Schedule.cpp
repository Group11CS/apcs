#include "Schedule.h"
#include "Class.h"
#include "AcademicStaff.h"
#include "Course.h"

void MakeSchedule(nodecourse *phead, string Class)
{
	schedule a;
	nodecourse *cur = phead;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++) a.c[i][j] = "x";
	while (cur)
	{
		string s = cur->data.CourseCode;
		a.c[cur->data.period][cur->data.day] = s;
		cur = cur->next;
	}
	ofstream fout;
	fout.open(Class + "_schedule.csv");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if(j == 5) fout << a.c[i][j];
			else fout << a.c[i][j] << ",";
		}
		if (i != 3) fout << endl;
	}
	fout.close();
	return;
}

void ImportSchedule(int n)
{
	schedule sche;
	string s, Class;
	ifstream fin;
	fin.open("ListOfClass.csv");
	if (!fin.is_open()) return;
	//getline(fin, s, '\n');
	listclass* pclass = NULL, *cur = new listclass;
	while (fin.good())
	{
		if (pclass == NULL)
		{
			pclass = new listclass;
			pclass->next = NULL;
			cout << "List of classes's Code:" << endl;
			getline(fin, pclass->data, '\n');
			cout << pclass->data << endl;
			cur = pclass;
		}
		else
		{
			cur->next = new listclass;
			cur = cur->next;
			getline(fin, cur->data, '\n');
			cout << cur->data << endl;
			cur->next = NULL;
		}
	}
	fin.close();
	cout << "Input the Class: ";
	cin.ignore(1000, '\n');
	getline(cin, Class, '\n');
	cur = pclass;
	nodecourse *pcourse = NULL, *tmp = new nodecourse;
	while (cur)
	{
		if (cur->data == Class)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class + "_course.csv");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (j == 5) getline(fin, sche.c[i][j], '\n');
					else getline(fin, sche.c[i][j], ',');
				}
			}
			fin.close();
			if (n == 21) ViewSchedule(sche);
			fin.open(Class + "_course.csv");
			string a;
			//getline(fin, a, '\n');
			if (!fin.is_open()) return;
			while (fin.good())
			{
				if (!pcourse)
				{
					pcourse = new nodecourse;
					getline(fin, s, ',');
					pcourse->data.CourseCode = s;
					getline(fin, s, ',');
					pcourse->data.Year = s;
					getline(fin, s, ',');
					pcourse->data.semester = s[0] - '0';
					getline(fin, s, ',');
					pcourse->data.CourseName = s;
					getline(fin, s, ',');
					pcourse->data.Lecturer = s;
					getline(fin, s, ',');
					pcourse->data.DateStart = StrToDate(s);
					getline(fin, s, ',');
					pcourse->data.DateEnd = StrToDate(s);
					getline(fin, s, ',');
					string a = s;
					pcourse->data.TimeStart = StrToTime(s);
					getline(fin, s, ',');
					string b = s;
					pcourse->data.TimeEnd = StrToTime(s);
					pcourse->data.period = StrToPeriod(a, b);
					getline(fin, s, '\n');
					pcourse->data.day = StrToDay(s);
					pcourse->next = NULL;
					tmp = pcourse;
				}
				else
				{
					tmp->next = new nodecourse;
					tmp = tmp->next;
					getline(fin, s, ',');
					tmp->data.CourseCode = s;
					getline(fin, s, ',');
					tmp->data.Year = s;
					getline(fin, s, ',');
					tmp->data.semester = s[0] - '0';
					getline(fin, s, ',');
					tmp->data.CourseName = s;
					getline(fin, s, ',');
					tmp->data.Lecturer = s;
					getline(fin, s, ',');
					tmp->data.DateStart = StrToDate(s);
					getline(fin, s, ',');
					tmp->data.DateEnd = StrToDate(s);
					getline(fin, s, ',');
					string a = s;
					tmp->data.TimeStart = StrToTime(s);
					getline(fin, s, ',');
					string b = s;
					tmp->data.TimeEnd = StrToTime(s);
					tmp->data.period = StrToPeriod(a, b);
					getline(fin, s, '\n');
					tmp->data.day = StrToDay(s);
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
			if (n == 18) AddNewCourse(pcourse, Class);
			if (n == 19) EditSchedule(pcourse, sche);
			if (n == 20) RemoveCourse(pcourse, Class);
			cout << "Completed!" << endl;
			MakeSchedule(pcourse, Class);
			system("pause");
			return;
		}
		else cur = cur->next;
	}
	cout << "Invalid class!" << endl;
	system("pause");
	return;
}

void EditSchedule(nodecourse *&phead, schedule &sche)
{
	string s;
	cout << "Input Course's code: ";
	getline(cin, s, '\n');
	nodecourse *cur = phead;
	while (cur)
	{
		if (cur->data.CourseCode == s)
		{
			break;
		}
		else cur = cur->next;
	}
	if (!cur)
	{
		cout << "Invalid Course's code!" << endl;
		system("pause");
		return;
	}
	string a;
	cout << "Input Time Start(hh:mm): ";
	getline(cin, a, '\n');
	//cur->data.TimeStart = StrToTime(s);
	cout << "Input Time End(hh:mm): ";
	string b;
	getline(cin, b, '\n');
	//cur->data.TimeEnd = StrToTime(s);
	//cur->data.period = StrToPeriod(a, b);
	int period = StrToPeriod(a, b);
	cout << "Input Day of week: ";
	getline(cin, s, '\n');
	dayofweek day = StrToDay(s);
	if (sche.c[period][day] != "x") cout << "Collided! Cannot edit." << endl;
	else
	{
		cur->data.TimeStart = StrToTime(a);
		cur->data.TimeEnd = StrToTime(b);
		cur->data.period = StrToPeriod(a, b);
		cur->data.day = day;
		cout << "Edited!" << endl;
	}
	system("pause");
	return;
}

void ViewSchedule(schedule a)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 5) cout << a.c[i][j];
			else cout << a.c[i][j] << " ";
		}
		if (i != 3) cout << endl;
	}
}
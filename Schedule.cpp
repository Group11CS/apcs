#include "Schedule.h"
#include "Class.h"
#include "AcademicStaff.h"
#include "Course.h"

void MakeSchedule(nodecourse *phead, string Class)
{
	schedule a[3];
	nodecourse *cur = phead;
	for(int k = 0; k < 3; k++)
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 6; j++) a[k].c[i][j] = "x";
	while (cur)
	{
		string s = cur->data.CourseCode;
		a[cur->data.semester-1].c[cur->data.period][cur->data.day] = s;
		cur = cur->next;
	}
	for (int k = 0; k < 3; k++)
	{
		stringstream ss;
		ss << (k + 1);
		ofstream fout;
		fout.open(Class + "_2017-2018_" + ss.str() + + "_schedule.csv");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (j == 5) fout << a[k].c[i][j];
				else fout << a[k].c[i][j] << ",";
			}
			if (i != 3) fout << endl;
		}
		fout.close();
	}
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
	int semester;
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
			cout << "Import Semester: ";
			cin >> semester;
			cin.ignore(1000, '\n');
			stringstream ss;
			ss << semester;
			fin.open(Class + "_2017-2018_" + ss.str() + "_schedule.csv");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (j == 5) getline(fin, sche.c[i][j], '\n');
					else getline(fin, sche.c[i][j], ',');
				}
			}
			fin.close();
			if (n == 21)
			{
				cout << "Schedule of class " << Class << " in semester " << semester << " in 2017-2018:" << endl;
				ViewSchedule(sche);
				system("pause");
				return;
			}
			cout << "Input successfull!" << endl;
			system("pause");
			if (n == 18) AddCourseSchedule(sche);//AddNewCourse(pcourse, Class);
			else if (n == 19) EditSchedule(sche);
			else if (n == 20) RemoveSchedule(sche);
			cout << "Completed!" << endl;
			ExportSchedule(sche, Class, semester);
			system("pause");
			return;
		}
		else cur = cur->next;
	}
	cout << "Invalid class!" << endl;
	system("pause");
	return;
}

void AddCourseSchedule(schedule &sche)
{
	string s;
	cout << "Input Course's Code: ";
	getline(cin, s);
	bool check = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
		{
			if (sche.c[i][j] == s) check = true;
		}
	if (check)
	{
		cout << "Valid Course! Please add new course's schedule. " << endl;
		string a, b;
		cout << "Input Time Start(hh:mm): ";
		getline(cin, a);
		cout << "Input Time End(hh:mm): ";
		getline(cin, b);
		int period = StrToPeriod(a, b);
		cout << "Input day of week: ";
		getline(cin, a);
		dayofweek day = StrToDay(a);
		if (sche.c[period][day] == "x")
		{
			sche.c[period][day] = s;
			cout << "Added!" << endl;
		}
		else cout << "Collided! Cannot add." << endl;
	}
	return;
}

void EditSchedule(schedule &sche)
{
	string course, s;
	cout << "Input Course's code: ";
	bool check[4][6];
	memset(check, true, sizeof(check));
	getline(cin, course, '\n');
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
		{
			if (sche.c[i][j] == course && check[i][j])
			{
				cout << "The course is on " << IntToStr(j) << " in " << i + 1 << " period. Do you want to change?(y/n):";
				getline(cin, s);
				if (s == "y")
				{
					string a;
					cout << "Input Time Start(hh:mm): ";
					getline(cin, a, '\n');
					cout << "Input Time End(hh:mm): ";
					string b;
					getline(cin, b, '\n');
					int period = StrToPeriod(a, b);
					cout << "Input Day of week: ";
					getline(cin, s, '\n');
					dayofweek day = StrToDay(s);
					if (sche.c[period][day] != "x") cout << "Collided! Cannot edit." << endl;
					else
					{
						sche.c[i][j] = "x";
						sche.c[period][day] = course;
						check[period][day] = false;
					}
				}
			}
		}
	cout << "Edited!" << endl;
	//ExportSchedule(sche, Class);
	system("pause");
	return;
}

void RemoveSchedule(schedule &sche)
{
	string course;
	cout << "Input course's code: ";
	getline(cin, course);
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
		{
			if (sche.c[i][j] == course)
			{
				sche.c[i][j] = "x";
			}
		}
	cout << "Removed!" << endl;
	return;
}

void ExportSchedule(schedule a, string Class, int semester)
{
	stringstream ss;
	ss << (semester);
	ofstream fout;
	fout.open(Class + "_2017-2018_" + ss.str() + +"_schedule.csv");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 5) fout << a.c[i][j];
			else fout << a.c[i][j] << ",";
		}
		if (i != 3) fout << endl;
	}
	fout.close();
}

void ViewSchedule(schedule a)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << a.c[i][j] << " ";
		}
		cout << endl;
	}
}
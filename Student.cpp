#include "Student.h"
#include "Scoreboard.h"
#include "Login.h"
#include "Course.h"
#include "Schedule.h"

void ViewScore(string ID)
{
	string Class = GetClass(ID), s, course;
	ifstream fin;
	fin.open(Class + "_course.csv");
	if (!fin.is_open()) return;
	nodecourse *pcourse = NULL, *tmp = NULL;
	if (!fin.is_open()) return;
	while (fin.good())
	{
		getline(fin, s, ',');
		fin.ignore(1000, '\n');
			if (!pcourse)
			{
				pcourse = new nodecourse;
				pcourse->data.CourseCode = s;
				tmp = pcourse;
			}
			else
			{
				tmp->next = new nodecourse;
				tmp = tmp->next;
				tmp->data.CourseCode = s;
				//fin.ignore(1000, '\n');
				tmp->next = NULL;
			}
	}
	fin.close();
	tmp = pcourse;
	cout << "List of course in class " << Class << ":" << endl;
	while (tmp)
	{
		cout << tmp->data.CourseCode << endl;
		tmp = tmp->next;
	}
	cin.ignore(1000, '\n');
	cout << "Input the Course: ";
	getline(cin, course, '\n');
	tmp = pcourse;
	while (tmp)
	{
		if (tmp->data.CourseCode == course)
		{
			cout << "Valid course!" << endl;
			fin.open(Class + "_" + course + "_" + "scoreboard.csv");
			if (!fin.is_open()) return;
			nodescoreboard *pscoreboard = NULL, *tmp1 = NULL;
			while (!fin.eof())
			{
				getline(fin, s, ',');
				if (s == ID)
				{
					cout << fixed << setprecision(2);
					pscoreboard = new nodescoreboard;
					pscoreboard->data.ID = ID;
					cout << "ID: " << pscoreboard->data.ID << endl;
					getline(fin, pscoreboard->data.fullname, ',');
					cout << "Full name: " << pscoreboard->data.fullname << endl;
					getline(fin, s, ',');
					pscoreboard->data.midterm = stof(s);
					cout << "Midterm's score: " << pscoreboard->data.midterm << endl;
					getline(fin, s, ',');
					pscoreboard->data.final = stof(s);
					cout << "Final's score: " << pscoreboard->data.final << endl;
					getline(fin, s, ',');
					pscoreboard->data.lab = stof(s);
					cout << "Lab/TA's score: " << pscoreboard->data.lab << endl;
					getline(fin, s, ',');
					pscoreboard->data.bonus = stof(s);
					cout << "Bonus's score: " << pscoreboard->data.bonus << endl;
					getline(fin, s, '\n');
					pscoreboard->data.total = stof(s);
					cout << "Total's score: " << pscoreboard->data.total << endl;
					delete pscoreboard;
					break;
				}
				fin.ignore(1000, '\n');
			}
			fin.close();
			cout << "Completed!" << endl;
			system("pause");
			return;
		}
		else tmp = tmp->next;
	}
	return;
}

void ViewScheduleStudent(string ID)
{
	string Class = GetClass(ID), semester;
	cin.ignore(1000, '\n');
	cout << "Input semester: ";
	getline(cin, semester, '\n');
	ifstream fin;
	fin.open(Class + "_2017-2018_" + semester + "_schedule.csv");
	schedule a;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 5) getline(fin, a.c[i][j], '\n');
			else getline(fin, a.c[i][j], ',');
		}
	}
	fin.close();
	cout << "Schedule of class " << Class << " in semester " << semester << " in 2017-2018:" << endl;
	ViewSchedule(a);
	system("pause");
	return;
}

void DesignStudent(string username, string password)
{
	system("cls");
	cout << "+++++++++++++++ STUDENT +++++++++++++++" << endl;
	cout << "1.View info of your account" << endl;
	cout << "2.Change password" << endl;
	cout << "3.Log out" << endl;
	cout << "4.Check in" << endl;
	cout << "5.View check in result" << endl;
	cout << "6.View score of a course" << endl;
	cout << "7.View schedule" << endl;
	int option;
	cout << "PLEASE INPUT YOUR OPTION:"; cin >> option;
	switch (option) {
	case 1: {
		system("pause");
		GetInfo(username, password);
		DesignStudent(username, password);
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		system("cls");
		cin.ignore(1000, '\n');
		break;
	}
	case 4: {
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		system("cls");
		ViewScore(username);
		DesignStudent(username, password);
		break;
	}
	case 7: {
		system("cls");
		ViewScheduleStudent(username);
		DesignStudent(username, password);
		break;
	}
	default:
		cout << "wrong input" << endl;
	}
}

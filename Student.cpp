#include "Student.h"
#include "Scoreboard.h"
#include "Login.h"
#include "Course.h"
#include "Schedule.h"
#include "Attendance.h"

bool cmpTime(string a, string b)
{
	int n = a.size(), m = b.size();
	if (n != m) return (n > m);
	else return (a > b);
}

dayofweek TimeToDay(int x)
{
	switch (x)
	{
	case 2: return Monday;
	case 3: return Tuesday;
	case 4: return Wednesday;
	case 5: return Thursday;
	case 6: return Friday;
	default: return Saturday;
		break;
	}
}

int TimeToPeriod(string s)
{
	if (cmpTime(s,"7:30") && cmpTime("9:10",s)) return 0;
	if (cmpTime(s, "9:30") && cmpTime("11:10", s)) return 1;
	if (cmpTime(s, "13:30") && cmpTime("15:10", s)) return 2;
	if (cmpTime(s, "15:30") && cmpTime("17:10", s)) return 3;
	return 4;
}

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
				else fin.ignore(1000, '\n');
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

void CheckIn(string ID)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	dayofweek day = TimeToDay(1 + ltm->tm_wday);
	stringstream ss;
	ss << ltm->tm_hour;
	string s = ss.str();
	stringstream sss;
	sss << ltm->tm_min;
	s = s + ":" + sss.str();
	int period = TimeToPeriod(s);
	string Class = GetClass(ID), semester;
	if (period == 4)
	{
		cout << "There is no class at this time. Try later.";
		system("pause");
		return;
	}
	cin.ignore(1000, '\n');
	cout << "Input semester: ";
	getline(cin, semester, '\n');
	schedule a;
	ifstream fin;
	ofstream fout;
	fin.open(Class + "_2017-2018_" + semester + "_schedule.csv");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 5) getline(fin, a.c[i][j], '\n');
			else getline(fin, a.c[i][j], ',');
		}
	}
	fin.close();
	if (a.c[period][day] != "x")
	{
		cout << "There is Course " << a.c[period][day] << " at this time." << endl;
		fin.open(Class + "_" + a.c[period][day] + "_attendance.csv");
		nodeattendance *pattendance = NULL, *tmp1 = new nodeattendance;
		if (!fin.is_open()) return;
		while (!fin.eof())
		{
			if (!pattendance)
			{
				pattendance = new nodeattendance;
				getline(fin, pattendance->data.ID, ',');
				getline(fin, pattendance->data.fullname, ',');
				for (int i = 0; i < 9; i++)
				{
					getline(fin, pattendance->data.w[i], ',');
				}
				getline(fin, pattendance->data.w[9], '\n');
				tmp1 = pattendance;
			}
			else
			{
				tmp1->next = new nodeattendance;
				tmp1 = tmp1->next;
				getline(fin, tmp1->data.ID, ',');
				getline(fin, tmp1->data.fullname, ',');
				for (int i = 0; i < 9; i++)
				{
					getline(fin, tmp1->data.w[i], ',');
				}
				getline(fin, tmp1->data.w[9], '\n');
				tmp1->next = NULL;
			}
		}
		fin.close();
		cout << "Check in?(y/n)";
		getline(cin, s, '\n');
		tmp1 = pattendance;
		while (tmp1->data.ID != ID) tmp1 = tmp1->next;
		switch (s[0])
		{
		case 'y': tmp1->data.w[9] = "o"; break;
		default: tmp1->data.w[9] = "x";
		}
		fout.open(Class + "_" + a.c[period][day] + "_attendance.csv", ios::trunc);
		tmp1 = pattendance;
		while (tmp1->next)
		{
			fout << tmp1->data.ID << "," << tmp1->data.fullname << ",";
			for (int i = 0; i < 9; i++)
			{
				fout << tmp1->data.w[i] << ",";
			}
			fout << tmp1->data.w[9] << endl;
			tmp1 = tmp1->next;
		}
		fout << tmp1->data.ID << "," << tmp1->data.fullname << ",";
		for (int i = 0; i < 9; i++)
		{
			fout << tmp1->data.w[i] << ",";
		}
		fout << tmp1->data.w[9];
		fout.close();
	}
	cout << "Completed!" << endl;
	system("pause");
	return;
}

void ViewCheckInStudent(string ID)
{
	string Class = GetClass(ID), s, course;
	ifstream fin;
	ofstream fout;
	fin.open(Class + "_course.csv");
	nodecourse *pcourse = NULL, *tmp = new nodecourse;
	if (!fin.is_open()) return;
	cout << "List course of Class " << Class << ":" << endl;
	while (fin.good())
	{
		if (!pcourse)
		{
			pcourse = new nodecourse;
			getline(fin, s, ',');
			pcourse->data.CourseCode = s;
			cout << s << endl;
			tmp = pcourse;
		}
		else
		{
			tmp->next = new nodecourse;
			tmp = tmp->next;
			getline(fin, s, ',');
			tmp->data.CourseCode = s;
			cout << s << endl;
			tmp->next = NULL;
		}
		fin.ignore(1000, '\n');
	}
	fin.close();
	cin.ignore(1000, '\n');
	cout << "Input course's code: ";
	getline(cin, course, '\n');
	tmp = pcourse;
	while (tmp)
	{
		if (tmp->data.CourseCode == course)
		{
			fin.open(Class + "_" + course + "_attendance.csv");
			if (!fin.is_open()) return;
			while (fin.good())
			{
				getline(fin, s, ',');
				if (s == ID)
				{
					cout << "Class: " << Class << endl;
					cout << "Course: " << course << endl;
					cout << "ID: " << s << endl;
					getline(fin, s, ',');
					cout << "Full name: " << s << endl;
					for (int i = 0; i < 9; i++)
					{
						getline(fin, s, ',');
						cout << "Week " << i + 1 << ": ";
						switch (s[0])
						{
						case 'o': cout << "Present!" << endl; break;
						default: cout << "Absent!" << endl;
						}
					}
					getline(fin, s, '\n');
					cout << "Week " << 10 << ": ";
					switch (s[0])
					{
					case 'o': cout << "Present!" << endl; break;
					default: cout << "Absent!" << endl;
					}
					break;
				}
				fin.ignore(1000, '\n');
			}
			fin.close();
		}
		tmp = tmp->next;
	}
	cout << "Completed!" << endl;
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
		system("cls");
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
		system("cls");
		CheckIn(username);
		DesignStudent(username, password);
		break;
	}
	case 5: {
		system("cls");
		ViewCheckInStudent(username);
		DesignStudent(username, password);
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
		DesignStudent(username, password);
	}
}

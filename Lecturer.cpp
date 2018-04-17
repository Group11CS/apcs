#include "Lecturer.h"
#include "Login.h"
#include "Class.h"
#include "Course.h"

void ImportScoreboard(int n, string username)
{
	string Class,s, course;
	ifstream fin;
	fin.open(username + "_class.csv");
	if (!fin.is_open()) return;
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
	cin.ignore(1000, '\n');
	cout << "Input the Class: ";
	getline(cin, Class, '\n');
	cur = pclass;
	nodecourse *pcourse = NULL, *tmp = new nodecourse;
	nodescoreboard *pscoreboard = NULL, *tmp1 = new nodescoreboard;
	while (cur)
	{
		if (cur->data == Class)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class + "_course.csv");
			string a;
			//getline(fin, a, '\n');
			if (!fin.is_open()) return;
			while (fin.good())
			{
				getline(fin, s, ',');
				getline(fin, a, ',');
				getline(fin, a, ',');
				getline(fin, a, ',');
				getline(fin, a, ',');
				fin.ignore(1000, '\n');
				if (a == username)
				{
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
			}
			fin.close();
			tmp = pcourse;
			cout << "List of course in class " << Class << ":" << endl;
			while (tmp)
			{
				cout << tmp->data.CourseCode << endl;
				tmp = tmp->next;
			}
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
					while (!fin.eof())
					{
						if (!pscoreboard)
						{
							pscoreboard = new nodescoreboard;
							getline(fin, pscoreboard->data.ID, ',');
							getline(fin, pscoreboard->data.fullname, ',');
							getline(fin, s, ',');
							pscoreboard->data.midterm = stof(s);
							getline(fin, s, ',');
							pscoreboard->data.final = stof(s);
							getline(fin, s, ',');
							pscoreboard->data.lab = stof(s);
							getline(fin, s, ',');
							pscoreboard->data.bonus = stof(s);
							getline(fin, s, '\n');
							pscoreboard->data.total = stof(s);
							tmp1 = pscoreboard;
						}
						else
						{
							tmp1->next = new nodescoreboard;
							tmp1 = tmp1->next;
							getline(fin, tmp1->data.ID, ',');
							getline(fin, tmp1->data.fullname, ',');
							getline(fin, s, ',');
							tmp1->data.midterm = stof(s);
							getline(fin, s, ',');
							tmp1->data.final = stof(s);
							getline(fin, s, ',');
							tmp1->data.lab = stof(s);
							getline(fin, s, ',');
							tmp1->data.bonus = stof(s);
							getline(fin, s, '\n');
							tmp1->data.total = stof(s);
							tmp1->next = NULL;
						}
					}
					cout << "Input successfull!" << endl;
					system("pause");
					if (n == 6) ViewScoreboard(Class, course, pscoreboard);
					cout << "Completed!" << endl;
					system("pause");
					return;
				}
				else tmp = tmp->next;
			}
		}
		else cur = cur->next;
	}
	cout << "Invalid class!" << endl;
	system("pause");
	return;
}

void ViewScoreboard(string Class, string course, nodescoreboard *cur)
{
	cout << "Scoreboard of Class: " << Class << ", Course:" << course << endl;
	cout << "Student ID,Fullname,Midterm,Final,Lab,Bonus,Total" << endl;
	while (cur)
	{
		cout << cur->data.ID << "," << cur->data.fullname << "," << cur->data.midterm << "," << cur->data.final << "," << cur->data.lab << ","<< cur->data.bonus << "," << cur->data.total << endl;
		cur = cur->next;
	}
	return;
}

void DesignLecturer(string username, string password)
{
	system("cls");
	cout << "+++++++++++++ LECTURER +++++++++++++" << endl;
	cout << "1.View info of your account" << endl;
	cout << "2.Change password" << endl;
	cout << "3.Log out" << endl;
	cout << "4.Import screboard of a course" << endl;
	cout << "5.Edit a student score" << endl;
	cout << "6.View a scoreboard" << endl;
	int option;
	cout << "PLEASE INPUT YOUR OPTION "; cin >> option;
	switch (option) {
	case 1: {
		system("cls");
		GetInfo(username, password);
		DesignLecturer(username, password);
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		system("cls");
		cin.ignore(1000, '\n');
		//ViewLogin(username, password);
		break;
	}
	case 4: {
		ImportScoreboard(4, username);
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		system("cls");
		ImportScoreboard(6, username);
		DesignLecturer(username, password);
		break;
	}
	default:
		system("cls");
		cout << "wrong input" << endl;
		system("pause");
	}
}
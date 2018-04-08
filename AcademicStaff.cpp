#include "AcademicStaff.h"
#include "Course.h"
#include "Class.h"
#include "Login.h"
void inputstudentlist(int n) 
{
	string Class, s;
	ifstream fin;
	fin.open("ListOfClass.csv");
	if (!fin.is_open()) return;
	getline(fin, s, '\n');
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
	nodestudent *head = NULL;
	while (cur)
	{
		if (cur->data == Class)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class + ".csv", ios::in);
			nodestudent *tmp = head;
			while (!fin.eof()) 
			{
				if (head == NULL) 
				{
					head = new nodestudent;
					head->next = NULL;
					cout << "inputing: ";
					getline(fin, head->data.MSSV, ',');
					cout << head->data.MSSV << " :";
					getline(fin, head->data.name, '\n');
					cout << head->data.name << "\n";
					tmp = head;
				}
				else 
				{
					tmp->next = new nodestudent;
					tmp = tmp->next;
					getline(fin, tmp->data.MSSV, ',');
					cout << tmp->data.MSSV << " :";
					getline(fin, tmp->data.name, '\n');
					cout << tmp->data.name << "\n";
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
		}
		else cur = cur->next;
	}
	cout << "done" << endl;
	fin.close();
}////this function also show list of student in a class;

void ImportCourse(int n)
{
	string Class, s;
	ifstream fin;
	fin.open("ListOfClass.csv");
	if (!fin.is_open()) return;
	getline(fin, s, '\n');
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
	while (cur)
	{
		if (cur->data == Class)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class + "_course.csv");
			string a;
			//getline(fin, a, '\n');
			if (!fin.is_open()) return;
			nodecourse *pcourse = NULL, *tmp = new nodecourse;
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
					pcourse->data.TimeStart = StrToTime(s);
					getline(fin, s, ',');
					pcourse->data.TimeEnd = StrToTime(s);
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
					tmp->data.TimeStart = StrToTime(s);
					getline(fin, s, ',');
					tmp->data.TimeEnd = StrToTime(s);
					getline(fin, s, '\n');
					tmp->data.day = StrToDay(s);
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
			if (n == 13) AddNewCourse(pcourse, Class);
			if (n == 14) DeleteCourse(pcourse, Class);
			else if (n == 15) ViewListofCourse(pcourse);
			cout << "Completed!" << endl;
			system("pause");
			return;
		}
		else cur = cur->next;
	}
	cout << "Invalid class!" << endl;
	system("pause");
	return;
}

void AddNewCourse(nodecourse *&phead, string Class)
{
	string s;
	nodecourse *cur = phead;
	while (cur->next) cur = cur->next;
	cur->next = phead;
	cur = cur->next;
	cout << "Input Course's Code: ";
	getline(cin, s, '\n');
	cur->data.CourseCode = s;
	cout << "Input Course's Year(yyyy-yyyy): ";
	getline(cin, s, '\n');
	cur->data.Year = s;
	cout << "Input Course's semester: ";
	getline(cin, s, '\n');
	cur->data.semester = s[0] - '0';
	cout << "Input Course's Name: ";
	getline(cin, s, '\n');
	cur->data.CourseName = s;
	cout << "Input Lecturer: ";
	getline(cin, s, '\n');
	cur->data.Lecturer = s;
	cout << "Input Date Start(dd/mm/yy): ";
	getline(cin, s, '\n');
	cur->data.DateStart = StrToDate(s);
	cout << "Input Date End(dd/mm/yy): ";
	getline(cin, s, '\n');
	cur->data.DateEnd = StrToDate(s);
	cout << "Input Time Start(hh:mm): ";
	getline(cin, s, '\n');
	cur->data.TimeStart = StrToTime(s);
	cout << "Input Time End(hh:mm): ";
	getline(cin, s, '\n');
	cur->data.TimeEnd = StrToTime(s);
	cout << "Input Day of week: ";
	getline(cin, s, '\n');
	cur->data.day = StrToDay(s);
	cur->next = NULL;
	ofstream fout;
	fout.open(Class + "_course.csv", ios::app);
	fout << endl;
	fout << cur->data.CourseCode << ",";
	fout << cur->data.Year << ",";
	fout << cur->data.semester << ",";
	fout << cur->data.CourseName << ",";
	fout << cur->data.Lecturer << ",";
	fout << cur->data.DateStart.day << "/" << cur->data.DateStart.month << "/" << cur->data.DateStart.year << ",";
	fout << cur->data.DateEnd.day << "/" << cur->data.DateEnd.month << "/" << cur->data.DateEnd.year << ",";
	fout << cur->data.TimeStart.hour << ":" << cur->data.TimeStart.minute << ",";
	fout << cur->data.TimeEnd.hour << ":" << cur->data.TimeEnd.minute << ",";
	if (cur->data.day == Monday) fout << "Monday";
	else if (cur->data.day == Tuesday) fout << "Tuesday";
	else if (cur->data.day == Wednesday) fout << "Wednesday";
	else if (cur->data.day == Thursday) fout << "Thursday";
	else if (cur->data.day == Friday) fout << "Friday";
	else if (cur->data.day == Saturday) fout << "Saturday";
	else fout << "Sunday";
	fout.close();
	return;
}

void DeleteCourse(nodecourse *&phead, string Class)
{
	string s;
	cout << "Input Course's code: ";
	cin >> s;
	if (phead->data.CourseCode == s)
	{
		phead = phead->next;
		return;
	}
	nodecourse *cur = phead;
	while (cur->next)
	{
		if (cur->next->data.CourseCode == s)
		{
			nodecourse *tmp = cur->next;
			cur->next = cur->next->next;
			delete tmp;
			break;
		}
		else cur = cur->next;
	}
	ofstream fout;
	fout.open(Class + "_course.csv", ios::trunc);
	cur = phead;
	while (cur)
	{
		fout << endl;
		fout << cur->data.CourseCode << ",";
		fout << cur->data.Year << ",";
		fout << cur->data.semester << ",";
		fout << cur->data.CourseName << ",";
		fout << cur->data.Lecturer << ",";
		fout << cur->data.DateStart.day << "/" << cur->data.DateStart.month << "/" << cur->data.DateStart.year << ",";
		fout << cur->data.DateEnd.day << "/" << cur->data.DateEnd.month << "/" << cur->data.DateEnd.year << ",";
		fout << cur->data.TimeStart.hour << ":" << cur->data.TimeStart.minute << ",";
		fout << cur->data.TimeEnd.hour << ":" << cur->data.TimeEnd.minute << ",";
		if (cur->data.day == Monday) fout << "Monday";
		else if (cur->data.day == Tuesday) fout << "Tuesday";
		else if (cur->data.day == Wednesday) fout << "Wednesday";
		else if (cur->data.day == Thursday) fout << "Thursday";
		else if (cur->data.day == Friday) fout << "Friday";
		else if (cur->data.day == Saturday) fout << "Saturday";
		else fout << "Sunday";
		cur = cur->next;
	}
	fout.close();
}
void ViewListofCourse(nodecourse *phead)
{
	nodecourse *cur = phead;
	while (cur)
	{
		cout << cur->data.CourseCode << ": " << cur->data.CourseName << endl;
		cur = cur->next;
	}
	return;
}
void DesignAcademicStaff(string username, string password)
{
	system("cls");
	cout << "+++++++++++++++ ACADEMIC STAFF ++++++++++++++" << endl;
	cout << endl;
	cout << endl;
	cout << ">> =============== GENERAL ================ <<" << endl;
	cout << "1.View info of your account" << endl;
	cout << "2.Change password" << endl;
	cout << "3.Log out" << endl;
	cout << endl;
	cout << ">> ============== STUDENTS ================ <<" << endl;
	cout << "4.Import students from file" << endl;
	cout << "5.Add a new student from class " << endl;
	cout << "6. Edit a existing student" << endl;
	cout << "7.Remove a student" << endl;
	cout << "8.Change a student from class A to class B" << endl;
	cout << "9.Add a new empty class" << endl;
	cout << "10.View list of classes" << endl;
	cout << "11.View student lists of a class" << endl;
	cout << endl;
	cout << ">> =============== COURSES ================ <<" << endl;
	cout << "12.Import courses from file" << endl;
	cout << "13.Add new course" << endl;
	cout << "14.Remove a course" << endl;
	cout << "15.View list of courses" << endl;
	cout << endl;
	cout << ">> ============== SCHEDULES =============== <<" << endl;
	cout << "16.Import courses's schedule from file" << endl;
	cout << "17.Add a new course" << endl;
	cout << "18.Edit an existing course" << endl;
	cout << "19.Remove a course" << endl;
	cout << "20.View lists of courses" << endl;
	cout << endl;
	cout << ">> ============== ATTENDANCE ================ <<" << endl;
	cout << "21.Search and view an attendance list of a course" << endl;
	cout << "22.Export an existing attendance list to a csv file" << endl;
	cout << endl;
	cout << ">> ============== SCOREBOARD ================ <<" << endl;
	cout << "23.Search and view a scoreboard of a course" << endl;
	cout << "24.Export score board to a csv file" << endl;
	cout << endl;
	cout << "PLEASE CHOOSE YOUR OPTION: ";
	int option;
	cin >> option;
	switch (option) {
	case 1: {
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
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		break;
	}
	case 7: {
		break;
	}
	case 8: {
		break;
	}
	case 9: {
		break;
	}
	case 10: {
		break;
	}
	case 11: {
		break;
	}
	case 12: {
		system("cls");
		ImportCourse(12);
		DesignAcademicStaff(username,password);
		break;
	}
	case 13: {
		system("cls");
		ImportCourse(13);
		DesignAcademicStaff(username,password);
		break;
	}
	case 14: {
		system("cls");
		ImportCourse(14);
		DesignAcademicStaff(username,password);
		break;
	}
	case 15: {
		system("cls");
		ImportCourse(15);
		DesignAcademicStaff(username, password);
		break;
	}
	case 16: {
		break;
	}
	case 17: {
		break;
	}
	case 18: {
		break;
	}
	case 19: {
		break;
	}
	case 20: {
		break;
	}
	case 21: {
		break;
	}
	case 22: {
		break;
	}
	case 23: {
		break;
	}
	case 24: {
		break;
	}
	default:
		cout << "Wrong input" << endl;
	}
}

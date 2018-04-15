#include "AcademicStaff.h"
#include "Course.h"
#include "Class.h"
#include "Login.h"
#include "Schedule.h"
#include "Lecturer.h"

void ReleaseStudent(nodestudent *&phead)
{
	nodestudent *cur = phead;
	while (cur)
	{
		nodestudent *tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

void ReleaseCourse(nodecourse *&phead)
{
	nodecourse *cur = phead;
	while (cur)
	{
		nodecourse *tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

void ReleaseClass(listclass *&phead)
{
	listclass *cur = phead;
	while (cur)
	{
		listclass *tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

void Importstudentlist(int n) 
{
	string Class, s;
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
	if (n == 9)
	{
		AddEmptyClass(pclass);
		cout << "Complete!" << endl;
		ReleaseClass(pclass);
		system("pause");
		return;
	}
	if (n == 10)
	{
		cout << "Complete!" << endl;
		system("pause");
		return;
	}
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
			fin.open(Class + ".csv");
			if (!fin.is_open()) return;
			nodestudent *tmp = head;
			while (fin.good()) 
			{
				if (head == NULL) 
				{
					head = new nodestudent;
					head->next = NULL;
					cout << "inputing: " << endl;
					getline(fin, head->data.MSSV, ',');
					//cout << head->data.MSSV << " :";
					getline(fin, head->data.name, '\n');
					//cout << head->data.name << "\n";
					tmp = head;
				}
				else 
				{
					tmp->next = new nodestudent;
					tmp = tmp->next;
					getline(fin, tmp->data.MSSV, ',');
					//cout << tmp->data.MSSV << " :";
					getline(fin, tmp->data.name, '\n');
					//cout << tmp->data.name << "\n";
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
			if (n == 5) AddStudent(head, Class);
			else if (n == 6) EditStudent(head, Class);
			else if (n == 7) RemoveStudent(head, Class);
			else if (n == 11) ViewListofStudent(head, Class);
			ReleaseClass(pclass);
			ReleaseStudent(head);
			break;
		}
		else cur = cur->next;
	}
	//cout << "done" << endl;
	fin.close();
} ////this function also show list of student in a class;

void AddEmptyClass(listclass *&phead)
{
	listclass *cur = phead;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new listclass;
	cur = cur->next;
	cin.ignore(1000, '\n');
	cout << "Input new class: ";
	getline(cin, cur->data);
	ofstream fout;
	fout.open("ListOfClass.csv", ios::app);
	fout << endl;
	fout << cur->data;
	fout.close();
}

void AddStudent(nodestudent *&phead, string Class)
{
	nodestudent *cur = phead;
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = new nodestudent;
	cur = cur->next;
	//cin.ignore(1000, '\n');
	cout << "input new student name: ";
	getline(cin, cur->data.name, '\n');
	//cin.ignore(1000, '\n');
	cout << "input new student id: ";
	getline(cin, cur->data.MSSV, '\n');
	cur->next = NULL;
	cout << "inputed: " << cur->data.MSSV << "," << cur->data.name << " into current list" << endl;
	ExportClass(phead, Class);
	system("pause");
}

void EditStudent(nodestudent *&phead, string Class)
{
	bool f = true;
	while (f) {
		cout << "please enter the student ID: ";
		string a;
		//cin.ignore(1000, '\n');
		getline(cin, a, '\n');
		cout << "finding..." << endl;
		nodestudent *tmp = phead;
		while (tmp != NULL) 
		{
			if (tmp->data.MSSV == a)
			{
				cout << "FOUND!" << endl;
				int a;
				cout << "press 1 to edit MSSV, 2 to edit name: ";
				cin >> a;
				switch (a) {
				case 1: {
					cout << "Enter the student's new ID: ";
					string mssv;
					cin.ignore(100, '\n');
					getline(cin, mssv, '\n');
					tmp->data.MSSV = mssv;
					cout << "Edited the student's ID, returning" << endl;
					break;
				}
				case 2: {
					cout << "Enter the student's new name: ";
					string name;
					cin.ignore(100, '\n');
					getline(cin, name, '\n');
					tmp->data.name = name;
					cout << "Edited the student's name, returning" << endl;
					break;
				}
				}
				break;
			}
			else tmp = tmp->next;
		}
		if (!tmp) cout << "Cannot found student!" << endl;
		cout << "Press 1 to find a student, 0 to stop : ";
		cin >> f;
	}
	system("pause");
	ExportClass(phead, Class);
}

void RemoveStudent(nodestudent *&phead, string Class)
{
	bool f = true;
	while (f) {
		cout << "enters student ID: ";
		string mssv;
		cin.ignore(1000, '\n');
		getline(cin, mssv, '\n');
		nodestudent *tmp = phead;
		if (tmp->data.MSSV == mssv) {
			cout << "Removing " << mssv << "..." << endl;
			phead = tmp->next;
			delete tmp;
			cout << "Removed";
		}
		else while (tmp->next != NULL) {
			if (tmp->next->data.MSSV == mssv)
			{

				cout << "Removing" << tmp->next->data.MSSV << "..." << endl;
				nodestudent *del = tmp->next;
				tmp->next = del->next;
				delete del;
				cout << "Removed";
				break;
			}
			else tmp = tmp->next;
			if (tmp->next == NULL) {
				cout << "No student with this ID";
				break;
			}
		}
		system("pause");
		ExportClass(phead, Class);
		cout << endl << "enters 1 to remove a student, 0 to stop" << endl;
		cin >> f;
	}
}

void ChangeStudent()
{
	string Class1, Class2, s;
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
	cin.ignore(1000, '\n');
	cout << "Input Class 1: ";
	getline(cin, Class1, '\n');
	cout << "Input Class 2: ";
	getline(cin, Class2, '\n');
	cur = pclass;
	nodestudent *tmp;
	nodestudent *head1 = NULL;
	while (cur)
	{
		if (cur->data == Class1)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class1 + ".csv");
			if (!fin.is_open()) return;
			tmp = head1;
			while (fin.good())
			{
				if (head1 == NULL)
				{
					head1 = new nodestudent;
					head1->next = NULL;
					cout << "inputing class 1: " << endl;
					getline(fin, head1->data.MSSV, ',');
					//cout << head->data.MSSV << " :";
					getline(fin, head1->data.name, '\n');
					//cout << head->data.name << "\n";
					tmp = head1;
				}
				else
				{
					tmp->next = new nodestudent;
					tmp = tmp->next;
					getline(fin, tmp->data.MSSV, ',');
					//cout << tmp->data.MSSV << " :";
					getline(fin, tmp->data.name, '\n');
					//cout << tmp->data.name << "\n";
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
			break;
		}
		else cur = cur->next;
	}
	fin.close();
	cur = pclass;
	nodestudent *head2 = NULL;
	while (cur)
	{
		if (cur->data == Class2)
		{
			cout << "Valid Class!" << endl;
			fin.open(Class2 + ".csv");
			if (!fin.is_open()) return;
			tmp = head2;
			while (fin.good())
			{
				if (head2 == NULL)
				{
					head2 = new nodestudent;
					head2->next = NULL;
					cout << "inputing class 2: " << endl;
					getline(fin, head2->data.MSSV, ',');
					//cout << head->data.MSSV << " :";
					getline(fin, head2->data.name, '\n');
					//cout << head->data.name << "\n";
					tmp = head2;
				}
				else
				{
					tmp->next = new nodestudent;
					tmp = tmp->next;
					getline(fin, tmp->data.MSSV, ',');
					//cout << tmp->data.MSSV << " :";
					getline(fin, tmp->data.name, '\n');
					//cout << tmp->data.name << "\n";
					tmp->next = NULL;
				}
			}
			cout << "Input successfull!" << endl;
			system("pause");
			break;
		}
		else cur = cur->next;
	}
	fin.close();
	//cin.ignore(1000, '\n');
	cout << "Input the student's ID: ";
	string mssv;
	nodestudent *cur1 = NULL;
	getline(cin, mssv, '\n');
	tmp = head1;
	//nodestudent *tmp = a.head;
	if (head1->data.MSSV == mssv) {
		head1 = head1->next;
	}

	else while (tmp != NULL) {
		if (tmp->data.MSSV == mssv) {
			break;
		}
		cur1 = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << "no student with this ID" << endl;
		return;
	}
	cur1->next = tmp->next;
	nodestudent *cur2 = head2;
	while (cur2->next != NULL)
	{
		cur2 = cur2->next;
	}
	cur2->next = tmp;
	tmp->next = NULL;
	ExportClass(head1, Class1);
	ExportClass(head2, Class2);
}

void ViewListofStudent(nodestudent *cur, string Class)
{
	cout << "List of student in class " << Class << ":" << endl;
	while (cur)
	{
		cout << cur->data.MSSV << ": " << cur->data.name << endl;
		cur = cur->next;
	}
	system("pause");
	return;
}

void ExportClass(nodestudent *cur, string Class)
{
	ofstream fout;
	fout.open(Class + ".csv", ios::trunc);
	if (!fout.is_open()) {
		cout << "error";
		return;
	}
	while (cur->next)
	{
		//cout << cur->data.MSSV << "," << cur->data.name << endl;
		fout << cur->data.MSSV << "," << cur->data.name << endl;
		cur = cur->next;
	}
	fout << cur->data.MSSV << "," << cur->data.name;
	fout.close();
}

void ImportCourse(int n)
{
	string Class, s;
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
			if (!fin.is_open()) return;
			while (fin.good())
			{
				if (!pcourse)
				{
					pcourse = new nodecourse;
					getline(fin, s, ',');
					pcourse->data.CourseCode = s;
					getline(fin, s, ',');
					pcourse->data.Year = StrToYear(s);
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
					tmp->data.Year = StrToYear(s);
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
			if (n == 13) AddNewCourse(pcourse, Class);
			else if (n == 15) RemoveCourse(pcourse, Class);
			else if (n == 16) ViewListofCourse(pcourse);
			cout << "Completed!" << endl;
			MakeSchedule(pcourse, Class);
			ReleaseClass(pclass);
			ReleaseCourse(pcourse);
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
	cur->next = new nodecourse;
	cur = cur->next;
	cout << "Input Course's Code: ";
	getline(cin, s, '\n');
	cur->data.CourseCode = s;
	cout << "Input Course's Year(yyyy-yyyy): ";
	getline(cin, s, '\n');
	cur->data.Year = StrToYear(s);
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
	string a = s;
	cur->data.TimeStart = StrToTime(s);
	cout << "Input Time End(hh:mm): ";
	getline(cin, s, '\n');
	string b = s;
	cur->data.TimeEnd = StrToTime(s);
	cur->data.period = StrToPeriod(a, b);
	cout << "Input Day of week: ";
	getline(cin, s, '\n');
	cur->data.day = StrToDay(s);
	cur->next = NULL;
	ExportCourse(phead, Class);
	return;
}

void RemoveCourse(nodecourse *&phead, string Class)
{
	string s;
	cout << "Input Course's code: ";
	getline(cin, s, '\n');
	if (phead->data.CourseCode == s)
	{
		nodecourse *tmp = phead;
		phead = phead->next;
		delete tmp;
		ExportCourse(phead, Class);
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
	ExportCourse(phead, Class);
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

void ExportCourse(nodecourse *cur, string Class)
{
	ofstream fout;
	fout.open(Class + "_course.csv");
	while (cur->next!=NULL)
	{
		fout << cur->data.CourseCode << ",";
		fout << cur->data.Year.yearStart << "-" << cur->data.Year.yearEnd << ",";
		fout << cur->data.semester << ",";
		fout << cur->data.CourseName << ",";
		fout << cur->data.Lecturer << ",";
		fout << atoi(cur->data.DateStart.day.c_str()) << "/" << atoi(cur->data.DateStart.month.c_str()) << "/" << atoi(cur->data.DateStart.year.c_str()) << ",";
		fout << atoi(cur->data.DateEnd.day.c_str()) << "/" << atoi(cur->data.DateEnd.month.c_str()) << "/" << atoi(cur->data.DateEnd.year.c_str()) << ",";
		fout << atoi(cur->data.TimeStart.hour.c_str()) << ":" << atoi(cur->data.TimeStart.minute.c_str()) << ",";
		fout << atoi(cur->data.TimeEnd.hour.c_str()) << ":" << atoi(cur->data.TimeEnd.minute.c_str()) << ",";
		if (cur->data.day == Monday) fout << "Monday";
		else if (cur->data.day == Tuesday) fout << "Tuesday";
		else if (cur->data.day == Wednesday) fout << "Wednesday";
		else if (cur->data.day == Thursday) fout << "Thursday";
		else if (cur->data.day == Friday) fout << "Friday";
		else if (cur->data.day == Saturday) fout << "Saturday";
		else fout << "Sunday";
		cur = cur->next;
		fout << endl;
	}
	fout << cur->data.CourseCode << ",";
	fout << cur->data.Year.yearStart << "-" << cur->data.Year.yearEnd << ",";
	fout << cur->data.semester << ",";
	fout << cur->data.CourseName << ",";
	fout << cur->data.Lecturer << ",";
	fout << atoi(cur->data.DateStart.day.c_str()) << "/" << atoi(cur->data.DateStart.month.c_str()) << "/" << atoi(cur->data.DateStart.year.c_str()) << ",";
	fout << atoi(cur->data.DateEnd.day.c_str()) << "/" << atoi(cur->data.DateEnd.month.c_str()) << "/" << atoi(cur->data.DateEnd.year.c_str()) << ",";
	fout << atoi(cur->data.TimeStart.hour.c_str()) << ":" << atoi(cur->data.TimeStart.minute.c_str()) << ",";
	fout << atoi(cur->data.TimeEnd.hour.c_str()) << ":" << atoi(cur->data.TimeEnd.minute.c_str()) << ",";
	if (cur->data.day == Monday) fout << "Monday";
	else if (cur->data.day == Tuesday) fout << "Tuesday";
	else if (cur->data.day == Wednesday) fout << "Wednesday";
	else if (cur->data.day == Thursday) fout << "Thursday";
	else if (cur->data.day == Friday) fout << "Friday";
	else if (cur->data.day == Saturday) fout << "Saturday";
	else fout << "Sunday";
	cur = cur->next;
	fout.close();
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
	cout << "6.Edit an existing student" << endl;
	cout << "7.Remove a student" << endl;
	cout << "8.Change a student from class A to class B" << endl;
	cout << "9.Add a new empty class" << endl;
	cout << "10.View list of classes" << endl;
	cout << "11.View student lists of a class" << endl;
	cout << endl;
	cout << ">> =============== COURSES ================ <<" << endl;
	cout << "12.Import courses from file" << endl;
	cout << "13.Add new course" << endl;
	cout << "14.Edit an existing course" << endl;
	cout << "15.Remove a course" << endl;
	cout << "16.View list of courses" << endl;
	cout << endl;
	cout << ">> ============== SCHEDULES =============== <<" << endl;
	cout << "17.Import courses's schedule from file" << endl;
	cout << "18.Add a course's schedule" << endl;
	cout << "19.Edit a course's schedule" << endl;
	cout << "20.Remove a course's schedule" << endl;
	cout << "21.View lists of Schedules" << endl;
	cout << endl;
	cout << ">> ============== ATTENDANCE ================ <<" << endl;
	cout << "22.Search and view an attendance list of a course" << endl;
	cout << "23.Export an existing attendance list to a csv file" << endl;
	cout << endl;
	cout << ">> ============== SCOREBOARD ================ <<" << endl;
	cout << "24.Search and view a scoreboard of a course" << endl;
	cout << "25.Export scoreboard to a csv file" << endl;
	cout << endl;
	cout << "PLEASE CHOOSE YOUR OPTION: ";
	int option;
	cin >> option;
	switch (option) {
	case 1: {
		system("cls");
		GetInfo(username, password);
		cin.ignore(1000, '\n');
		DesignAcademicStaff(username, password);
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
		system("cls");
		Importstudentlist(4);
		DesignAcademicStaff(username, password);
		break;
	}
	case 5: {
		system("cls");
		Importstudentlist(5);
		DesignAcademicStaff(username, password);
		break;
	}
	case 6: {
		system("cls");
		Importstudentlist(6);
		DesignAcademicStaff(username, password);
		break;
	}
	case 7: {
		system("cls");
		Importstudentlist(7);
		DesignAcademicStaff(username, password);
		break;
	}
	case 8: {
		system("cls");
		ChangeStudent();
		DesignAcademicStaff(username, password);
		break;
	}
	case 9: {
		system("cls");
		Importstudentlist(9);
		DesignAcademicStaff(username, password);
		break;
	}
	case 10: {
		system("cls");
		Importstudentlist(10);
		DesignAcademicStaff(username, password);
		break;
	}
	case 11: {
		system("cls");
		Importstudentlist(11);
		DesignAcademicStaff(username, password);
		break;
	}
	case 12: {
		system("cls");
		ImportCourse(12);
		DesignAcademicStaff(username, password);
		break;
	}
	case 13: {
		system("cls");
		ImportCourse(13);
		DesignAcademicStaff(username, password);
		break;
	}
	case 14: {
		system("cls");
		ImportCourse(14);
		DesignAcademicStaff(username, password);
		break;
	}
	case 15: {
		system("cls");
		ImportCourse(15);
		DesignAcademicStaff(username, password);
		break;
	}
	case 16: {
		system("cls");
		ImportCourse(16);
		DesignAcademicStaff(username, password);
		break;
	}
	case 17: {
		system("cls");
		ImportSchedule(17);
		DesignAcademicStaff(username, password);
		break;
	}
	case 18: {
		system("cls");
		ImportSchedule(18);
		DesignAcademicStaff(username, password);
		break;
	}
	case 19: {
		system("cls");
		ImportSchedule(19);
		DesignAcademicStaff(username, password);
		break;
	}
	case 20: {
		system("cls");
		ImportSchedule(20);
		DesignAcademicStaff(username, password);
		break;
	}
	case 21: {
		system("cls");
		ImportSchedule(21);
		DesignAcademicStaff(username, password);
		break;
	}
	case 22: {
		break;
	}
	case 23: {
		break;
	}
	case 24: {
		system("cls");
		ImportScoreboard(24);
		DesignAcademicStaff(username, password);
		break;
	}
	case 25: {
		break;
	}
	default:
		system("cls");
		cout << "Wrong input" << endl;
		system("pause");
	}
}

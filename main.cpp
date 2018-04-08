#include "AcademicStaff.h"
#include "Login.h"
#include "Student.h"
#include "Lecturer.h"

//using namespace std;

int main()
{
	string username;
	string password;
	char c;
    //DesignStudent();
	while (true)
	{
		cout << "Shall we start? (y/n): ";
		cin >> c;
		cin.ignore(1000, '\n');
		if (c == 'y')
		{
			switch (ViewLogin(username, password))
			{
			case 0: DesignStudent(username, password); break;
			case 1: DesignAcademicStaff(username, password); break;
			default: DesignLecturer(username, password);
			}
		}
		else break;
	}
	system("pause");
    //DesignAcademicStaff();
    return 0;
}

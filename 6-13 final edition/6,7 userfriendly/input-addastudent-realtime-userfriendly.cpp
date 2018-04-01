#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <stdlib.h>
using namespace std;
struct student {
	string name;
	string MSSV;
};
struct node {
	node* next;
	student data;
};
struct studentlist {
	node*head;
};
void ignore() {
	cin.ignore(100, '\n');
}
void inputstudentlist(string path,studentlist &list) {
	ifstream fin;

	fin.open(path) //file format is mssv,name\nmssv,name\n...
		;
	if (!fin.is_open()) {
		cout << "error";
		return;
	}
	node*cur = list.head;
	while (!fin.eof()) {
		if (list.head == NULL) {
			list.head = new node;
			list.head->next = NULL;
			cout << "inputing: ";
			getline(fin,list.head->data.MSSV,',');
			cout << list.head->data.MSSV<<" :";
			getline(fin,list.head->data.name,'\n');
			cout << list.head->data.name << "\n";
			cur = list.head;
		}
		else {
			node*tmp = new node;
			cur->next = tmp;
			cur = cur->next;
			getline(fin,tmp->data.MSSV, ',');
			cout << tmp->data.MSSV << " :";
			getline(fin, tmp->data.name, '\n');
			cout << tmp->data.name << "\n";
			tmp->next = NULL;
		}
		
	}
	cout << "done" << endl;
	fin.close();
}////this function also show list of student in a class;
void realtimecsv(string path, studentlist &list)
{
	cout << "outputing: " << endl;
	ofstream fout;
	fout.open(path);
	if (!fout.is_open()) {
		cout << "error";
		return;
	}
	node*cur = list.head;
	while (cur->next!=NULL)
	{
		cout << cur->data.MSSV << "," << cur->data.name << endl;
		fout << cur->data.MSSV << "," << cur->data.name << endl;
	
		cur = cur->next;
	}
	cout << cur->data.MSSV << "," << cur->data.name;
	fout << cur->data.MSSV << "," << cur->data.name;
	fout.close();
	cout << "done" << endl;
}
void inputclasses(string *path,int& k) {
	ifstream fin;
	fin.open("list.txt");
	fin >> k;
	fin.ignore(100, '\n');
	int i = 0;
	while(i<k){
		i++;
		
		getline(fin, path[i], ',');
	}
	fin.close();
}
void addastudent(studentlist& list,string path) {
	node*tmp = new node;
	node*cur = list.head;
	while (cur->next!=NULL) {
		cur = cur->next;
	}
	cur->next = tmp;
	cout << "input new student name: ";
	cin.ignore(100, '\n');
	getline(cin, tmp->data.name, '\n');
	cout << "input new student id: ";
	getline(cin, tmp->data.MSSV, '\n');
	tmp->next = NULL;
	cout << "inputed: " << tmp->data.MSSV << "," << tmp->data.name << " into current list" << endl;
	cout << "do you want to edit the full list?";
	bool a;
	cin >> a;
	if (a) {
		cin.ignore(1000, '\n');
		realtimecsv(path, list);
	}
}
void editastudent(studentlist& list, string path) {
	bool f = true;
	while (f) {
		cout << "please enter the student ID(mssv): ";
		string a;
		cin.ignore(1000, '\n');
		getline(cin, a, '\n');
		cout << endl << "finding...";
		node*tmp = list.head;
		while (tmp != NULL) {
			if (tmp->data.MSSV == a)
			{
				cout << endl << "FOUND!" << endl;
				int a;
				cout << "press 1 to edit MSSV, 2 to edit name: ";
				cin >> a;
				switch (a) {
				case 1: {
					cout << "enter the student's new ID: ";
					string mssv;
					cin.ignore(100, '\n');
					getline(cin, mssv, '\n');
					tmp->data.MSSV = mssv;
					realtimecsv(path, list);
					cout << "edited the student's ID, returning";

					return;
				}
				case 2: {
					cout << "enter the student's new Name: ";
					string name;
					cin.ignore(100, '\n');
					getline(cin, name, '\n');
					tmp->data.name = name;
					realtimecsv(path, list);
					cout << "edited the student's name, returning";
					
					return;
				}
				}
			}
			tmp = tmp->next;
		}
		cout << "cannot found student,press 1 to find a new student,0 to stop: ";
		cin >> f;
	}
}
void removeastudent(studentlist&list, string path) {
	bool f = true;
	while (f) {
		cout << "enters student ID: ";
		string mssv;
		cin.ignore(1000, '\n');
		getline(cin, mssv, '\n');
		node*tmp = list.head;
		if (tmp->data.MSSV == mssv) {
			cout << "removing " << mssv << "..." << endl;
			list.head = tmp->next;
			delete tmp;
			cout << "removed";
		}
		else while (tmp->next!= NULL) {
			if (tmp->next->data.MSSV == mssv)
			{

				cout << "removing" << tmp->next->data.MSSV << "..." << endl;
				node*del = tmp -> next;
				tmp->next = del->next;
				delete del;
				cout << "removed";
				break;
			}
			else tmp = tmp->next;
			if (tmp->next == NULL) {
				cout << "no student with this ID";
				break;
			}
		}
		realtimecsv(path, list);
		cout <<endl<< "enters 1 to remove a student, 0 to stop" << endl;
		cin >> f;
	}
}
void changestudent(studentlist&a, studentlist&b, string patha, string pathb) {
	cout << "input the student's ID that u want to change to another class: ";
	string mssv;
	ignore();
	node*cur = NULL;
	getline(cin, mssv, '\n');
	node*tmp = a.head;
	if (a.head->data.MSSV == mssv) {
		a.head = a.head->next;
	}

	else	while (tmp != NULL) {
		if (tmp->data.MSSV == mssv) {
			break;
		}
		cur = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << "no student with this ID" << endl;
		return;
	}
	cur->next = tmp->next;
	node*cur2 = b.head;
	while (cur2->next != NULL)
	{
		cur2 = cur2->next;
	}
	cur2->next = tmp;
	tmp->next = NULL;
	realtimecsv(patha, a);
	realtimecsv(pathb, a);
}
void newclass(string *path,int&k) {
	cout << "enter new class file name (.csv): ";
	string classs;
	ignore();
	getline(cin, classs, '\n');
	for(int i=1;i<=k;i++){
		if (path[i] == classs) {
			cout << "file name already taken!"<<endl;
			return;
		}
	}
	ofstream newfile(classs);
	ofstream fout;
	fout.open("list.txt");
	if (!fout.is_open()) {
		cout << "error";
		return;
	}
	k++;
	path[k] = classs;
	fout << k << endl;
	int i = 0;
	while (i < k)
	{
		i++;
		fout << path[i] << ",";
	}
	fout.close();
	cout << "create new class successfully";
}
void showlist(string*path, int k) {
	cout << "we have " << k << " classes:" << endl;
	for (int i = 1; i <= k; i++) {
		cout << path[i] << endl;
	}
	cout << "done" << endl;
}
int main() {

	studentlist list, list1;
	list.head = NULL;
	list1.head = NULL;
	string *path;
	path = new string[100];
	int x = 0, y = 0;
	int k = 0;
	inputclasses(path, k); //number of class right now;
	bool a = false;
	while (!a) {
		int b = 0;
		int c = 1;
		while (c != 0) {
			cout << "enter 0 to exit program" << endl;
			cout << "press 1 to edit a class file: " << endl;
			cout << "press 2 to change swap students from this class to another class" << endl;
			cout << "press 3 to create a new class" << endl;
			cout << "press 4 to show list of classes" << endl;
			cout << "press 5 to show list of students in a class" << endl;
			
			cin >> b;
			if (b == 0)
			{
				a = false;
				break;
			}
			
		
			switch (b) {
			case 1: {

				cout << "input class number: ";
				cin >> x;
				inputstudentlist(path[x], list);
				break;
			}
			case 2: {

				cout << "input first class number: ";
				cin >> x;
				cout << "input second class number: ";
				cin >> y;
				inputstudentlist(path[x], list);
				inputstudentlist(path[y], list1);
				changestudent(list, list1, path[x], path[y]);
				cout << "1 to continue, 0 to stop: ";
				cin >> c;
				break;
			}
			case 3: {
				newclass(path,k);
				k++;
				cout << "1 to continue, 0 to stop: ";
				cin >> c;
				break;

			}
			case 4: {
				showlist(path, k);
				cout << "1 to continue, 0 to stop: ";
				cin >> c;
				break;
			}
			case 5: {

				cout << "1 to continue, 0 to stop: ";
				cin >> c;
				break;
			}

			}
		}

		if (!a)
			break;

		cout << endl << "enters 1 to input a new student" << endl << " 2 to edit a student" << endl << "3 to remove a student" << endl << " 0 to quit";
				cin >> b;
				while (b != 0) {
					switch (b) {
					case 1: {
						addastudent(list, path[x]);
						break;
					}
					case 2: {
						editastudent(list, path[x]);
						break;
					}
					case 3: {
						removeastudent(list, path[x]);
					}
					case 0: {
						a = true;
						break;
					}
					}
					cout << endl << "enters 1 to input a new student" << endl << " 2 to edit a student" << endl << "3 to remove a student" << endl<<" 0 to quit";
					cin >> b;
				}
							system("cls");
	}
					node*cur = list.head;
					while (cur != NULL)
					{
						node*tmp = cur;
						cur = cur->next;
						delete tmp;
					}
					cur = list1.head;
					while (cur != NULL)
					{
						node*tmp = cur;
						cur = cur->next;
						delete tmp;
					}
					
					return 0;
}
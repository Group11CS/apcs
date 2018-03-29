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

void inputstudentlist(string path,studentlist &list) {
	fstream fin;

	fin.open(path) //file format is mssv,name\nmssv,name\n...
		;
	node*cur = NULL;
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
}
void realtimecsv(string path, studentlist &list)
{
	cout << "outputing: " << endl;
	fstream fout;
	fout.open(path);
	node*cur = list.head;
	while (cur->next!=NULL)
	{
		fout << cur->data.MSSV << "," << cur->data.name << endl;
		cout << cur->data.MSSV << "," << cur->data.name << endl;
		cur = cur->next;
	}
	fout << cur->data.MSSV << "," << cur->data.name;
	cout << cur->data.MSSV << "," << cur->data.name << endl;
	fout.close();
	cout << "done" << endl;
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
	cin.ignore(1000, '\n');
	realtimecsv(path, list);
}
int main() {
	studentlist list1;
	string path;
	list1.head = NULL;
	bool a=false;
	while (!a) {
		cout << "enter 0 to exit program" << endl;
		cout << "class number u want to input student from,eg 1,2: ";
		int b;
		cin >> b;
		if (b == 0)
		{
			break;
		}
		switch (b) {
		case 1: {
			path = "class1.csv";
		}
		case 2: {
			path = "class2.csv";
		}
		}
		list1.head = NULL;
		inputstudentlist(path, list1);
		cout << "do you want to input a new student into this class?eg 1=yes, 0 = no: " << endl;
		bool a;
		cin >> a;
		if (a)
		{
			addastudent(list1, path);
		}
		cout << "enter 0 to exit, enter 1 to return to main page: ";
		cin >> a;
		system("cls");
	}
	node*cur = list1.head;
	while (cur != NULL)
	{
		node*tmp = cur;
		cur = cur->next;
		delete tmp;
	}
	return 0;
}
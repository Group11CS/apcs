#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
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
void inputstudentlist(studentlist &list) {
	fstream fin;

	fin.open("easy.csv") //file format is mssv,name\nmssv,name\n...
		;
	while (!fin.eof()) {
		if (list.head == NULL) {
			list.head = new node;
			list.head->next = NULL;
			cout << "inputing: ";
			getline(fin,list.head->data.MSSV,',');
			cout << list.head->data.MSSV<<" :";
			getline(fin,list.head->data.name,'\n');
			cout << list.head->data.name << "\n";
			
		}
		else {
			node*cur = list.head;
			node*tmp = new node;
			cout << "inputing: ";
			getline(fin,tmp->data.MSSV, ',');
			cout << tmp->data.MSSV << " :";
			getline(fin,tmp->data.name, '\n');
			cout << tmp->data.name << "\n";
			tmp->next = NULL;
		}
		
	}
	fin.close();
}
int main() {
	studentlist list1;
	list1.head = NULL;
	inputstudentlist(list1);
	cout << "done";
	int t;
	cin >> t;
	node*cur = list1.head;
	while (cur != NULL)
	{
		node*tmp = cur;
		cur = cur->next;
		delete tmp;
	}
	return 0;
}
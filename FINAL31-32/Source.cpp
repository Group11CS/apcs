#include<iostream>
using namespace std;
#include<string>
#include<fstream>
struct student {
	string id;
	string name;
	string checked[10];
};
void checkin(student*&st, int k) {
	string id;
	cout << "your student ID: ";
	getline(cin, id, '\n');
	
	int w;
	cout << "what week is it? Week:" << endl;
	cin >> w;
	for (int i = 0; i < k; i++) {
		if (st[i].id == id) {
			cout << "lets check in...";
			st[i].checked[w - 1] = 'o';
			cout << endl << "checked in!" << endl;
			return;
		}
	}
	cout << "no student with this ID, returning";
}
void view(student*st,int k, string a) {
	ofstream fout;
	cout << "updating..." << endl;
	fout.open(a);
	if (!fout.is_open()) {
		cout << "fail";
		return;
	}
	fout << "ID,name,Week1,week2,week3,week3,week4,week5,week6,week7,week8,week9,week10" << endl;
	for (int i = 0; i < k; i++) {
		fout << st[i].id << ",";
		fout << st[i].name << ",";
		cout << st[i].id << ",";
		cout << st[i].name << ",";
		int j = 0;
		for (j = 0; j < 9; j++) {
			fout << st[i].checked[j] << ",";
			cout << st[i].checked[j] << ",";
		}
		if (i == k - 1) {
			fout << st[i].checked[k];
			cout << st[i].checked[k];
		}
		else {
			fout << st[i].checked[k] << endl; 
			cout << st[i].checked[k] << endl;
		}
	}
	cout << endl << "updated" << endl;
	fout.close();
}

int main() {
	string clas, course;
	ifstream fin;
	cout << "enter your class name: ";
	getline(cin, clas, '\n');
	cout << "enter your course code: ";
	getline(cin, course, '\n');
	string a = clas + "_" + course + "_attendance.csv";
	fin.open(a);
	if (!fin.is_open()) {
		cout << "wrong please run again" << endl;
		return;
	}
	getline(fin, clas, '\n');
	student *st;
	st = new student[100];
	int k = 0,i=0;
	while (!fin.eof()) {
		getline(fin, st[k].id, ',');
		cout << st[k].id << ",";
		getline(fin, st[k].name, ',');
		cout << st[k].name << ",";
		for (i = 0; i < 9; i++) {
			getline(fin, st[k].checked[i], ',');
			cout << st[k].checked[i] << ",";
		}
		getline(fin, st[k].checked[i], '\n');
		cout << st[k].checked[i] << endl;
		k++;
	}
	fin.close();
	checkin(st, k);
	view(st, k, a);
	cin >> clas;
	delete[]st;
	return 0;
}
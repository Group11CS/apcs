#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct course {
	string semester;
	string code, year, name, lecturer, start, end, from, to, Dow;
};
struct schedule {
	string datetime[4][6];
};
void update(schedule a,string c,string sem) {
	
	ofstream fout;
	fout.open(c + "_semester_" + sem + ".csv");
	cout << "updating..." << endl;
	cout << "Monday,Tuesday,Wednesday,Thursday,Friday,Saturday" << endl;
	fout << "Monday,Tuesday,Wednesday,Thursday,Friday,Saturday" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (i == 3 && j == 5) {
				fout << a.datetime[i][j];
				cout << a.datetime[i][j] << endl;
				break;
			}
			if (j == 5) {
				fout << a.datetime[i][j] << endl;
				cout << a.datetime[i][j] << endl;
				break;
			}
			fout << a.datetime[i][j] << ",";
			cout << a.datetime[i][j] << ",";
		}
	}
	cout << "updated";
	fout.close();
}
void importschedule(schedule &a,string c,string sem) {
	ifstream fin;
	fin.open(c + "_semester_" + sem+".csv");
	if (!fin.is_open()) {
		cout << "cannot open this schedule" << endl;
		return;
	}
	getline(fin, c, '\n');
	cout << c << endl;
	while (!fin.eof()) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 6; j++) {
				if (j == 5) {
					getline(fin, a.datetime[i][j], '\n');
					cout << a.datetime[i][j] << endl;
					break;
				}
				getline(fin, a.datetime[i][j], ',');
				cout << a.datetime[i][j] << ",";
			}
		}
	}
	fin.close();
	cout << "schedule imported, you can now add, edit, remove, view"<<endl;
}
void addschedule(schedule &a,string from,string dow,string code,string semester,string c,string sem) {
	int t = 4;
	int d = 6;
	if (from == "7:30")  t = 0;if (from == "9:30") t = 1;if (from == "1:30")  t = 2;if (from == "3:30") t = 3;
	if (dow == "Monday")d = 0; if (dow == "Tuesday") d = 1; if (dow == "Wednesday") d = 2; if (dow == "Thursday") d = 3; if (dow == "Friday") d = 4; if (dow == "Saturday") d = 5;
	if (t != 4 && d != 6 && a.datetime[t][d] == "0") {
		a.datetime[t][d] = code;
		cout << "add course to schedule success";
		update(a,c,sem);
	}
	else cout << "collided, add course failed";
}
void editschedule(schedule&a,string code,string &dow,string&from, string semester, string c, string sem) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (a.datetime[i][j] == code) {
				a.datetime[i][j] = "0";
				cout << "enter the day of your new course schedule(mon-sat): ";
				getline(cin, dow, '\n');
				if (dow == "Monday")j = 0; if (dow == "Tuesday") j = 1; if (dow == "Wednesday") j = 2; if (dow == "Thursday") j = 3; if (dow == "Friday") j = 4; if (dow == "Saturday") j = 5;
				cout << "enter course start time: ";
				getline(cin, from, '\n');
				if (from == "7:30")  i = 0; if (from == "9:30") i = 1; if (from == "1:30")  i = 2; if (from == "3:30") i = 3;
				a.datetime[i][j] = code;
				update(a, c, sem);
				return;
			}
		}
	}
	cout << "Nothing to edit!" << endl;
	
}
void removeschedule(schedule&a, string code, string semester, string c, string sem) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (a.datetime[i][j] == code) {
				a.datetime[i][j] = "0";
				update(a, c, sem);
				cout << "removed";
				return;
			}
		}
	}
	cout << "Nothing to remove!" << endl;
}
int main() {
	cout << "enter your class";
	string c;
	getline(cin, c, '\n');
	cout << "enter your semester";
	string sem;
	getline(cin, sem, '\n');
	schedule s;
	importschedule(s,c,sem);
	course course[1000];
	string a;
	int t = 0;
	bool d = true;;
	while (d) {
		ifstream fin;
		fin.open(c + "_course.csv");
		if (!fin.is_open()) {
			cout << "error opening file";
			fin.close();
		}
		else {
			
			string trash;
			getline(fin, trash, '\n');
			cout << "getting class's courses info..." << endl;
			while (!fin.eof()) {
				
				getline(fin, course[t].code, ','); 
				getline(fin, course[t].year, ','); 
				getline(fin, course[t].semester, ','); 
				getline(fin, course[t].name, ',');
				getline(fin, course[t].lecturer, ','); 
				getline(fin, course[t].start, ','); 
				getline(fin, course[t].end, ','); 
				getline(fin, course[t].from, ',');
				getline(fin, course[t].to, ','); 
				getline(fin, course[t].Dow, '\n');
				t++;
				cout << "order: code, year, name, lecturer, start, end, from, to, Dow;";
				cout << " course "<<t<<" info: " << endl << course[t-1].code << endl << course[t-1].year << endl << course[t-1].semester << endl << course[t-1].name << endl << course[t-1].lecturer << endl << course[t-1].start << endl << course[t-1].end << endl << course[t-1].from << endl << course[t-1].to << endl << course[t-1].Dow << endl;
			}
			fin.close();
		}
		d = false;
	}	
	int g;
	cout << "enter 1 to add, 2 to edit, 3 to remove,4 to view the class schedule: ";
	cin >> g;
	cin.ignore(100, '\n');
	switch (g) {
		case 1: {
			cout << "enter course code that you want to add to the schedule: ";
			getline(cin, a, '\n');
			for (int b = 0; b < t; b++) {
				if (a == course[b].code) {
					addschedule(s, course[b].from, course[b].Dow, course[b].code, course[b].semester, c, sem);
					return 0;
				}
			}
			cout << "no course with that code!" << endl;
			break;
		}
		case 2: {
			cout << "enter course code of the course schedule that you want to edit: ";
			getline(cin, a, '\n');
			for (int b = 0; b < t; b++) {
				if (a == course[b].code) {
					editschedule(s, course[b].code, course[b].Dow, course[b].from, course[b].semester, c, sem);
					return 0;;
				}
			}
				cout << "no course with that code!" << endl;
			break;
		}
		case 3: {
			cout << "enter course code of the course schedule that you want to remove: ";
			getline(cin, a, '\n');
			for (int b = 0; b < t; b++) {
				if (a == course[b].code) {
					removeschedule(s, course[b].code, course[b].semester, c, sem);
					return 0;;
				}
			}
			cout << "no course with that code!" << endl;
			break;
		}
		case 4: {
			cout << "here is the list of all course of schedule of that clas: " << endl;
				update(s, c, sem);
				break;
		}
	}
	cin >> d;
	return 0;
}
#include "Login.h"
bool cmp(string a, string b)
{
	if (a.length() != b.length()) return false;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i]) return false;
	return true;
}
int ViewLogin(string &username, string &password)
{
	nodeuser *phead = NULL, *cur = NULL;
	while (true)
	{
		system("cls");
		cout << "PLEASE LOGIN BEFORE PROCEEDING  " << endl;
		cout << "Enter your username: ";
		getline(cin, username);
		cout << "Enter your password: ";
		getline(cin, password);
		ifstream in("login.csv");
		if (!in.is_open())
			cout << "Couldn't open file";
		bool checkuser = false;
		while (in.good())
		{
			if (!phead)
			{
				phead = new nodeuser;
				getline(in, phead->data.user, ',');
				getline(in, phead->data.pass, ',');
				getline(in, phead->data.type, ',');
				in.ignore(1000, '\n');
				if (cmp(phead->data.user, username) && cmp(phead->data.pass, password))
				{
					phead->next = NULL;
					cur = phead;
					checkuser = true;
					break;
				}
				phead->next = NULL;
				cur = phead;
			}
			else
			{
				cur->next = new nodeuser;
				cur = cur->next;
				getline(in, cur->data.user, ',');
				getline(in, cur->data.pass, ',');
				getline(in, cur->data.type, ',');
				in.ignore(1000, '\n');
				if (cmp(cur->data.user, username) && cmp(cur->data.pass, password))
				{
					checkuser = true;
					break;
				}
			}
		}
		in.close();
		if (checkuser)
		{
			cout << "Login success!" << endl;
			system("pause");
			break;
		}
		else
		{
			cout << "Login fail!" << endl;
			system("pause");
			continue;
		}
	}
	char c = cur->data.type[0];
	return c - '0';
}

void GetInfo(string username, string password)
{
	nodeuser *phead = NULL, *cur = NULL;
	ifstream in("login.csv");
	if (!in.is_open())
		cout << "Couldn't open file";
	bool checkuser = false;
	while (in.good())
	{
		if (!phead)
		{
			phead = new nodeuser;
			getline(in, phead->data.user, ',');
			getline(in, phead->data.pass, ',');
			getline(in, phead->data.type, ',');
			if (cmp(phead->data.user, username) && cmp(phead->data.pass, password))
			{
				getline(in, phead->data.fullname, ',');
				getline(in, phead->data.email, ',');
				getline(in, phead->data.phone, ',');
				if (phead->data.type == "0") getline(in, phead->data.Class, '\n');
				else in.ignore(1000, '\n');
				phead->next = NULL;
				cur = phead;
				checkuser = true;
				break;
			}
			in.ignore(1000, '\n');
			phead->next = NULL;
			cur = phead;
		}
		else
		{
			cur->next = new nodeuser;
			cur = cur->next;
			getline(in, cur->data.user, ',');
			getline(in, cur->data.pass, ',');
			getline(in, cur->data.type, ',');
			if (cmp(cur->data.user, username) && cmp(cur->data.pass, password))
			{
				getline(in, cur->data.fullname, ',');
				getline(in, cur->data.email, ',');
				getline(in, cur->data.phone, ',');
				if (cur->data.type == "0") getline(in, cur->data.Class, '\n');
				else in.ignore(1000, '\n');
				checkuser = true;
				break;
			}
			in.ignore(1000, '\n');
		}
	}
	ShowInfo(cur);
	system("pause");
	in.close();
}

string GetClass(string username)
{
	string s;
	ifstream in("login.csv");
	if (!in.is_open())
		cout << "Couldn't open file";
	bool checkuser = false;
	while (in.good())
	{
		getline(in, s, ',');
		if (s == username)
		{
			getline(in, s, ',');
			getline(in, s, ',');
			getline(in, s, ',');
			getline(in, s, ',');
			getline(in, s, ',');
			getline(in, s, '\n');
			in.ignore(1000, '\n');
			break;
		}
		else in.ignore(1000, '\n');
	}
	in.close();
	return s;
}

void ShowInfo(nodeuser *cur)
{
	cout << "User: " << cur->data.user << endl;
	cout << "Full name: " << cur->data.fullname << endl;
	cout << "Type: ";
	switch (atoi(cur->data.type.c_str()))
	{
	case 0: cout << "Student" << endl; break;
	case 1: cout << "Acadamic Staff" << endl; break;
	default: cout << "Lecturer" << endl; 
	}
	cout << "Email: " << cur->data.email << endl;
	cout << "Phone: " << cur->data.phone << endl;
	if (cur->data.type == "0") cout << "Class: " << cur->data.Class << endl;
	return;
}
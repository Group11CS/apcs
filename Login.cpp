#include "Login.h"
bool cmp(string a, string b)
{
	if (a.length() != b.length()) return false;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i]) return false;
	return true;
}
int ViewLogin(string username, string password)
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

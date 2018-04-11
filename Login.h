#ifndef _LOGIN_H_
#define _LOGIN_H_
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

struct userlogin
{
	string user;
	string pass;
	string type;
	string fullname;
	string email;
	string phone;
	string Class;
};

struct nodeuser
{
	userlogin data;
	nodeuser *next;
};

bool cmp(string a, string b);
int ViewLogin(string &username, string &password);
void GetInfo(string username, string password);
void ShowInfo(nodeuser *cur);
#endif // _LOGIN_H_

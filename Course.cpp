#include "Course.h"

dateofyear StrToDate(string s)
{
	dateofyear data;
	data.day = ""; data.month = ""; data.year = "";
	int i = 0;
	while (s[i] != '/')
	{
		data.day += s[i];
		i++;
	}
	i++;
	while (s[i] != '/')
	{
		data.month += s[i];
		i++;
	}
	i++;
	while (i < s.size())
	{
		data.year += s[i];
		i++;
	}
	return data;
}
timeofday StrToTime(string s)
{
	timeofday data;
	int i = 0;
	data.hour = "";
	data.minute = "";
	while (s[i] != ':')
	{
		data.hour += s[i];
		i++;
	}
	i++;
	while (i < s.size())
	{
		data.minute += s[i];
		i++;
	}
	return data;
}
CourseYear StrToYear(string s)
{
	CourseYear data;
	int i = 0;
	data.yearEnd = "";
	data.yearStart = "";
	while (s[i] != '-')
	{
		data.yearStart += s[i];
		i++;
	}
	i++;
	while (i < s.size())
	{
		data.yearEnd += s[i];
		i++;
	}
	return data;
}
dayofweek StrToDay(string s)
{
	if (s == "Monday") return Monday;
	if (s == "Tuesday") return Tuesday;
	if (s == "Wednesday") return Wednesday;
	if (s == "Thursday") return Thursday;
	if (s == "Friday") return Friday;
	return Saturday;
}

string IntToStr(int s)
{
	if (s == 0) return "Monday";
	if (s == 1) return "Tuesday";
	if (s == 2) return "Wednesday";
	if (s == 3) return "Thursday";
	if (s == 4) return "Friday";
	return "Saturday";
}

int StrToPeriod(string a, string b)
{
	if (a == "7:30" && b == "9:10") return 0;
	if (a == "9:30" && b == "11:10") return 1;
	if (a == "13:30" && b == "15:10") return 2;
	return 3;
}
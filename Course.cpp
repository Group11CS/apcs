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
dayofweek StrToDay(string s)
{
	if (s == "Monday") return Monday;
	if (s == "Tuesday") return Tuesday;
	if (s == "Wednesday") return Wednesday;
	if (s == "Thursday") return Thursday;
	if (s == "Friday") return Friday;
	if (s == "Saturday") return Saturday;
	return Sunday;
}
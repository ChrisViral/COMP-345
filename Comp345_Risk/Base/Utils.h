#pragma once
#include <string>
#include <iterator>
#include <locale>
#include <sstream>
#include <vector>

using namespace std;


// Taken from 
// https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-string-starts-with-a-certain-string-and-convert-a-sub
static bool startsWith(string str, string prefix)
{
	return (str.substr(0, prefix.size()) == prefix);
}


// Taken from
//https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
template <typename Out>
void split(const string& s, char delim, Out result)
{
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim))
	{
		*(result++) = item;
	}
}

vector<string> split(const string& s, char delim)
{
	vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

locale loc;
//Shortcut tolower method
string tolower(string str)
{
	return tolower(str, loc);
}

bool boolFromYesNo(string str)
{
	return tolower(str) == "yes";
}

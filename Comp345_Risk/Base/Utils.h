// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <locale>
#include <sstream>

using std::string;

//Taken from 
//https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-string-starts-with-a-certain-string-and-convert-a-sub
static bool startsWith(string str, string prefix)
{
	return str.substr(0, prefix.size()) == prefix;
}


// Taken from
//https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
template <typename Out>
void split(const string& s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim))
	{
		*(result++) = item;
	}
}

inline std::vector<string> split(const string& s, char delim)
{
	std::vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

inline char charToLower(char c)
{
	std::locale loc;
	return tolower(c, loc);
}

//Shortcut tolower method, taken from
// https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
inline string stringToLower(string str)
{
	transform(str.begin(), str.end(), str.begin(), charToLower);
	return str;
}

inline bool boolFromYesNo(string str)
{
	return stringToLower(str) == "yes";
}

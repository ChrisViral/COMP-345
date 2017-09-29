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

//Taken from 
//https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-string-starts-with-a-certain-string-and-convert-a-sub
static bool startsWith(std::string str, std::string prefix)
{
	return str.substr(0, prefix.size()) == prefix;
}


// Taken from
//https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
template <typename Out>
void split(const std::string& s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (getline(ss, item, delim))
	{
		*(result++) = item;
	}
}

inline std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
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
inline std::string stringToLower(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), charToLower);
	return str;
}

inline bool boolFromYesNo(std::string str)
{
	return stringToLower(str) == "yes";
}

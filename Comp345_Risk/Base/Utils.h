#pragma once
#include <iterator>
#include <locale>
#include <vector>

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
	stringstream ss;
	ss.str(s);
	string item;
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

std::locale loc;
//Shortcut tolower method
inline std::string tolower(std::string str)
{
	return tolower(str, loc);
}

inline bool boolFromYesNo(std::string str)
{
	return tolower(str) == "yes";
}

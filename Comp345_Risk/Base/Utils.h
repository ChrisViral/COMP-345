// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <locale>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;

//Taken from 
//https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-string-starts-with-a-certain-string-and-convert-a-sub
static bool startsWith(string str, string prefix)
{
	return str.substr(0, prefix.size()) == prefix;
}


inline std::string toBinary(int n) {
	// I'm sure there is a better way to do this with bit twidlling, but it's 1 in the morning
	if (n == 0) return "000";
	if (n == 1) return "001";
	if (n == 2) return "010";
	if (n == 3) return "011";
	if (n == 4) return "100";
	if (n == 5) return "101";
	if (n == 6) return "110";
	if (n == 7) return "111";
	// Special case for when the user doesnt want to be asked anymore
	if (n == -1) return "0000";
	return "000";
}

inline bool strBitToBool(std::string bit) {
	return bit != "0";
}

static void printOutputOptionFlags() {

	std::cout << "D = Player Domination" << std::endl;
	std::cout << "H = Players Hands " << std::endl;
	std::cout << "C = Player Continent Control" << std::endl;

	
	std::cout << "7 for DHC" << std::endl;
	std::cout << "6 for DH-" << std::endl;
	std::cout << "5 for D-C" << std::endl;
	std::cout << "4 for D--" << std::endl;
	std::cout << "3 for -HC" << std::endl;
	std::cout << "2 for -H-" << std::endl;
	std::cout << "1 for --H" << std::endl;
	std::cout << "0 for ---" << std::endl;

	std::cout << "-1 to never be asked again" << std::endl;
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

inline vector<string> split(const string& s, char delim)
{
	vector<string> elems;
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

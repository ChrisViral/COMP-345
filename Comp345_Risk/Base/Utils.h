// ==============================
//           COMP-345 D
//          Assignment 3
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

//https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
std::string toBinary(int n) {
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}

inline bool charBitToBool(char bit) {
	return bit != '0';
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

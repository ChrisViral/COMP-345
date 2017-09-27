#pragma once
#include <string>
#include <iterator>
#include <locale>
#include <sstream>
#include <vector>


// Taken from 
// https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-string-starts-with-a-certain-string-and-convert-a-sub
static bool startsWith(std::string str, std::string prefix) {
	return (str.substr(0, prefix.size()) == prefix);
}



// Taken from
//https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

bool boolFromYesNo(std::string str) {
	// TODO: change to lowercase
	return  str == "yes";

}

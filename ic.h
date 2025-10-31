

#ifndef _IC_H_
#define _IC_H_

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// lang class
class Ic
{

private:

	// SYNTAX
	const char DELIMITER = ':';
	const char COMMENT_PREFIX = ';';
	const char OPEN_SECTION = '[';
	const char CLOSE_SECTION = ']';
	const std::string MAIN_SECTION = "[]";
	const std::string MAIN_SECTION_TITLE = "main";
	const std::string FORMAT = ".ic";

	// DATA
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

	// LOAD FILE
	void load(const std::string& filename);
	// PARSE LINE
	void parse(const std::string& line);
	// SECTION
	std::string section = MAIN_SECTION_TITLE;

public:
	Ic();
	Ic(const std::string& filename) { load(filename); }
	
	// Get Value
	std::string getVal(const std::string& target, const std::string& key);
	std::string getVal(const std::string& key);

	// has methods
	bool has(const std::string& target_section);
	bool has(const std::string& target_section, const std::string& key);

	// int methods

	int as_int(const std::string& target, const std::string& key);
	int as_int(const std::string& key);

	// double methods
	double as_double(const std::string& target, const std::string& key);
	double as_double(const std::string& key);

	// bool methods
	bool as_bool(const std::string& target, const std::string& key);
	bool as_bool(const std::string& key);
};

// ERRORS
class FileNotExistence {};
class KeyError {};
class BoolError {};

// trim line
std::string trim(const std::string& str);

#endif

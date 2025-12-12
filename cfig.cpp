
#include "cfig.h"

std::string strip(const std::string& str)
{
	if (str.empty())
		return str;
				
	if (str.at(0) == '"' && str.at(str.size() - 1) == '"')
		return str.substr(1, str.length() - 2);

	if (str.at(0) == '\'' && str.at(str.size() - 1) == '\'')
		return str.substr(1, str.length() - 2);
		
	return str;
}

const CfigValue& Cfig::get(const std::string& section, const std::string& key) const
{
	auto sec_it = data.find(section);

	if (sec_it == data.end())
		throw SectionError();

	auto key_it = sec_it->second.find(key);

	if (key_it == sec_it->second.end())
		throw KeyError();

	return key_it->second;
}

std::ostream& operator<<(std::ostream& out, const Type& type)
{
	switch(type)
	{
		case STRING:
			out << "string"; break;
		case INT:
			out << "int";break;
		case FLOAT:
			out << "float";break;
		case BOOL:
			out << "bool";break;
		case CHAR:
			out << "char"; break;
		default:
			out << "string";			
	}
	return out;
}

Type CfigValue::detectType(const std::string& val)
{
	if (val.empty())
		return STRING;

	if (strip(val).size() == 1)
	{
		return CHAR;
	}

	if (val == "true" || val == "false")
		return BOOL;

	const char* start = val.c_str();
	char* endptr;

	std::strtod(start, &endptr);

	if (endptr == start + val.size())
	{
		const char* p = start;
		while (p < endptr)
		{
			if (*p == '.' || *p == 'e' || *p == 'E') return FLOAT;
			p++;
		}
		return INT;
	}	
	return STRING;		
}

char CfigValue::toChar() const
{
	switch (type_)
	{
		case INT:
		case BOOL:
		case CHAR:
			try {
				return raw_.front();
			} catch (const std::exception& e) {
				throw std::runtime_error("Cannot convert to char: " + raw_);
			}
		default:
			throw std::runtime_error("Cannot convert to int: " + raw_);			
	}
}

int CfigValue::toInt() const
{
	switch (type_)
	{
		case INT:
		case FLOAT:
			try { 
				return std::stoi(raw_); 
			} catch (const std::exception& e) {
				throw std::runtime_error("Cannot convert to int: " + raw_);
			}
			break;
		case BOOL:
			return toBool() ? 1 : 0;
		default:
			throw std::runtime_error("Cannot convert to int: " + raw_);
	}
}

double CfigValue::toDouble() const
{
	switch (type_)
	{
		case INT:
		case FLOAT:
			try { 
				return std::stod(raw_); 
			} catch (const std::exception& e) {
				throw std::runtime_error("Cannot convert to double: " + raw_);
			}
			break;
		case BOOL:
			return toBool() ? 1.0 : 0.0;
		default:
			throw std::runtime_error("Cannot convert to double: " + raw_);
	}
}

float CfigValue::toFloat() const
{
	return static_cast<float>(toDouble());
}

bool CfigValue::toBool() const
{

	switch (type_)
	{
		case BOOL:
			return raw_ == "true";
		case INT:
			return toInt() != 0;
		case FLOAT:
			return toDouble() != 0.0;
		default:
			throw std::runtime_error("Cannot convert to bool: " + raw_);
	}
}

std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first) return "";
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void Cfig::load(const std::string& filename)
{

	std::ifstream in(filename);

	if (!in.is_open())
		throw FileNotExistence();

	std::string line;
	while (getline(in, line))
		parse(line);
	in.close();
		
}

void Cfig::setDelimiter(const Delimiter& del_)
{
	switch (del_)
	{
		case EQUAL:
			DELIMITER = '='; break;
		case COLON:
		default:
			DELIMITER = ':';
	}
}

void Cfig::setCommentPrefix(const CommentStyle& comment_style_)
{
	switch (comment_style_)
	{
		case HASH:
			COMMENT_PREFIX = '#'; break;
		case SEMICOLON:
		default:
			COMMENT_PREFIX = ';';
	}
}

void Cfig::parse(const std::string& line)
{

	std::string cline = trim(line.substr(0, line.find(COMMENT_PREFIX)));

	if (cline.empty())
		return;

	if (cline == MAIN_SECTION)
	{
		section = MAIN_SECTION_TITLE;
		return;
	}

	if (cline[0] == OPEN_SECTION && cline[cline.length() - 1] == CLOSE_SECTION)
	{
		section = trim(cline.substr(1, cline.length() - 2));
		return;
	}

	size_t del_pos = cline.find(DELIMITER);

	if (del_pos == std::string::npos)
		return;

	std::string	key = trim(cline.substr(0, del_pos));
	CfigValue val = CfigValue(
		strip(trim(cline.substr(del_pos + 1)))
	);
	
	if (!key.empty())
		data[section][key] = val;
}

bool Cfig::has(const std::string& target_section) const
{
	return data.find(target_section) != data.end();
}

bool Cfig::has(const std::string& target_section, const std::string& key) const
{
	auto it = data.find(target_section);
	return it != data.end() && it->second.find(key) != it->second.end();
}


int CfigValue::toInt(int defaultValue) const
{
	try {
		return toInt();
	} catch (const std::exception&) {
		return defaultValue;
	}
}

char CfigValue::toChar(char defaultValue) const
{
	try {
		return toChar();
	} catch (const std::exception&) {
		return defaultValue;
	}
}

bool CfigValue::toBool(bool defaultValue) const
{
	try {
		return toBool();
	} catch (const std::exception&) {
		return defaultValue;
	}
}

float CfigValue::toFloat(float defaultValue) const
{
	try {
		return toFloat();
	} catch (const std::exception&) {
		return defaultValue;
	}
}


double CfigValue::toDouble(double defaultValue) const
{
	try {
		return toDouble();
	} catch (const std::exception&) {
		return defaultValue;
	}
}

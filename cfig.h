

#ifndef _CFIG_H_
#define _CFIG_H_

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>

// // ERRORS
class FileNotExistence {};
class KeyError {};
class SectionError {};
class ValueError {};

// lang class
std::string trim(const std::string& str);

std::string strip(const std::string& str);

enum Type { STRING, INT, FLOAT, BOOL, CHAR, PAIR };

std::ostream& operator<<(std::ostream& out, const Type& type);



class CfigValue
{
	std::string raw_;
	Type type_;
	Type detectType(const std::string& val);

	std::pair<std::string, std::string> toStringPair() const 
	{
		if (type_ != PAIR)
			throw std::runtime_error("Not a pair");
		return parsePair();
	}

	std::pair<std::string, std::string> parsePair() const
	{
		if (raw_.size() < 3 || raw_[0] != '(' || raw_.back() != ')')
			throw std::runtime_error("Invalid pair format");

		std::string inner = raw_.substr(1, raw_.size() - 2);
		size_t comma = inner.find(',');
		if (comma == std::string::npos)
			throw std::runtime_error("No comma in pair");

		return {
			strip(inner.substr(0, comma)),
			strip(inner.substr(comma+1))
		};
	}

public:
	CfigValue(const std::string& value) : raw_(trim(value)) {
		type_ = detectType(raw_);
	}
	CfigValue() : type_(STRING), raw_("") {}

	Type type() { return type_; }
	std::string raw() const { return raw_;  }

	std::string toString() const { return raw_; }

	template<typename T>
	std::pair<T, T> toPair() const
	{
	    auto str_pair = toStringPair();
	    
	    if constexpr (std::is_same_v<T, std::string>) {
	        return str_pair;
	    }
	    else if constexpr (std::is_same_v<T, int>) {
	        return { std::stoi(str_pair.first), std::stoi(str_pair.second) };
	    }
	    else if constexpr (std::is_same_v<T, float>) {
	        return { std::stof(str_pair.first), std::stof(str_pair.second) };
	    }
	    else if constexpr (std::is_same_v<T, double>) {
	        return { std::stod(str_pair.first), std::stod(str_pair.second) };
	    }
	    else if constexpr (std::is_same_v<T, bool>) {
	        auto to_bool = [](const std::string& s) { return s == "true" || s == "1"; };
	        return { to_bool(str_pair.first), to_bool(str_pair.second) };
	    }
	    else if constexpr (std::is_same_v<T, char>) {
	        if (str_pair.first.size() != 1 || str_pair.second.size() != 1)
	            throw std::runtime_error("Invalid char pair");
	        return { str_pair.first[0], str_pair.second[0] };
	    }
	    else {
	        throw std::runtime_error("Unsupported pair type");
	    }
	}

	int toInt() const;
	bool toBool() const;
	float toFloat() const;
	double toDouble() const;
	char toChar() const;
	operator std::string() const { return raw_; }
};



class Cfig
{

public:
	enum CommentStyle {
		HASH, SEMICOLON, DOUBLE_SLASH
	};
	enum Delimiter {
		EQUAL, COLON
	};
private:
	char DELIMITER = ':';
	char COMMENT_PREFIX = ';';
	const char OPEN_SECTION = '[';
	const char CLOSE_SECTION = ']';
	const std::string MAIN_SECTION = "[]";
	const std::string MAIN_SECTION_TITLE = "main";

	std::unordered_map<std::string, std::unordered_map<std::string, CfigValue>> data;

	std::string section = MAIN_SECTION_TITLE;
	void parse(const std::string& line);

	void setDelimiter(const Delimiter& del_);	
	void setCommentPrefix(const CommentStyle& comment_style_);

public:

	Cfig() {};
	Cfig(const CommentStyle& style) { setCommentPrefix(style); }
	Cfig(const Delimiter& del) { setDelimiter(del); }
	Cfig(const std::string& filename) { load(filename); }
	Cfig(const CommentStyle& style, const Delimiter& del);
	Cfig(const Delimiter& del, const CommentStyle& style);
	Cfig(const std::string& filename, const Delimiter& del, const CommentStyle& style);
	bool has(const std::string& target_section) const;
	bool has(const std::string& target_section, const std::string& key) const;
	const CfigValue& get(const std::string& section, const std::string& key) const;
	const CfigValue& get(const std::string& key) const { return get(MAIN_SECTION_TITLE, key); }

	const CfigValue& operator()(const std::string& section, const std::string& key) const {
		return get(section, key);
	}

	template<typename T>
	T get(const std::string& section, const std::string& key, const T& defaultValue) const;
	template<typename T>
	T get(const std::string& key, const T& defaultValue) const;
		
	void load(const std::string& filename);	

    std::set<std::string> sections() const;

    std::set<std::string> keys(const std::string& section) const;

};


#endif

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <sstream>
#include "QueryResult.h"


class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
private:
	
	std::shared_ptr<std::vector<std::string>> m_file;

	std::map<std::string, std::shared_ptr<std::set<line_no>>> m_wordMap;


public:

	

	TextQuery(std::ifstream &inFile);


	QueryResult query(const std::string &sought) const;
	
};
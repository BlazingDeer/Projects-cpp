#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <sstream>


class QueryResult
{
private:
	friend std::ostream &print(std::ostream &os, const QueryResult &result);
	using line_no = std::vector<std::string>::size_type;
	std::string m_word;
	std::shared_ptr<std::set<line_no>> m_lines;
	std::shared_ptr<std::vector<std::string>> m_file;

public:
	QueryResult(std::string word, std::shared_ptr<std::set<line_no>> lineNumbers, std::shared_ptr<std::vector<std::string>> file);

	std::set<QueryResult::line_no>::iterator end();
	std::set<QueryResult::line_no>::iterator begin();
	std::shared_ptr<std::vector<std::string>> get_file();


};
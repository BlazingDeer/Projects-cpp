#include "QueryResult.h"

QueryResult::QueryResult(std::string word, std::shared_ptr<std::set<line_no>> lineNumbers, std::shared_ptr<std::vector<std::string>> file):
	m_word(word), m_lines(lineNumbers), m_file(file)
{
}

std::set<QueryResult::line_no>::iterator QueryResult::end()
{
	return m_lines->end();
}

std::set<QueryResult::line_no>::iterator QueryResult::begin()
{
	return m_lines->begin();
}

std::shared_ptr<std::vector<std::string>> QueryResult::get_file()
{
	return m_file;
}

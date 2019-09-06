#include "QueryResult.h"

QueryResult::QueryResult(std::string word, std::shared_ptr<std::set<line_no>> lineNumbers, std::shared_ptr<std::vector<std::string>> file):
	m_word(word), m_lines(lineNumbers), m_file(file)
{
}

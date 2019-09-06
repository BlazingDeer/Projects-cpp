#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream &inFile) : m_file(new std::vector<std::string>)
{
	
	std::string text;
	while (std::getline(inFile, text))
	{
		m_file->push_back(text);
		int lineNumber = m_file->size() - 1;

		std::istringstream line(text);
		std::string words;
		while (line >> words)
		{
			auto &lineSet = m_wordMap[words];
			if (!lineSet)
			{
				lineSet.reset(new std::set<line_no>);
			}
			lineSet->insert(lineNumber);
		}
	}

	
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto locIter = m_wordMap.find(sought);
	if (locIter == m_wordMap.end())
	{
		return QueryResult(sought, nodata, m_file);
	}
	else
	{
		return QueryResult(sought, locIter->second, m_file);
	}

}

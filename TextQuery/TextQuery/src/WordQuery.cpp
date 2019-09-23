#include "WordQuery.h"

WordQuery::WordQuery(const std::string &s):
	query_word(s)
{
}

QueryResult WordQuery::eval(const TextQuery &t) const
{
	return t.query(query_word);
}

std::string WordQuery::rep() const
{
	return query_word;
}

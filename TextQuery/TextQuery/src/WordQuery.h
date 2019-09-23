#pragma once
#include "Query_base.h"

class WordQuery : public Query_base
{
	friend class Query;

	WordQuery(const std::string &s);

	QueryResult eval(const TextQuery &t) const;
	std::string rep() const;
	std::string query_word;
};
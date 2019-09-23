#pragma once
#include "Query.h"

class NotQuery : public Query_base
{
	friend Query operator~(const Query &);
	NotQuery(const Query &);

	std::string rep() const;

	QueryResult eval(const TextQuery &) const;
	Query query;
};



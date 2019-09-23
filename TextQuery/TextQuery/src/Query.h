#pragma once
#include "Query_base.h"
#include "WordQuery.h"


class Query
{
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);

public:
	Query(const std::string &);
	QueryResult eval(const TextQuery &t)const;
	std::string rep() const;

private:
	Query(std::shared_ptr<Query_base> query);
	std::shared_ptr<Query_base> q;
};


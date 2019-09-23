#include "Query.h"

Query::Query(const std::string &s):
	q(new WordQuery(s))
{
}

QueryResult Query::eval(const TextQuery &t) const
{
	return q->eval(t);
}

std::string Query::rep() const
{
	return q->rep();
}

Query::Query(std::shared_ptr<Query_base> query):
	q(query)
{
}

std::ostream &operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}

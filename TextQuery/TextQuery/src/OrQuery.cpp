#include "OrQuery.h"

OrQuery::OrQuery(const Query &left, const Query &right):
	BinaryQuery(left,right,"|")
{
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
	auto right = rhs.eval(text);
	auto left = lhs.eval(text);

	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());

	return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
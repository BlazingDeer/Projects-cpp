#include "AndQuery.h"
#include <algorithm>
#include <iterator>

AndQuery::AndQuery(const Query &left, const Query &right):
	BinaryQuery(left,right,"&")
{
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
	auto left = lhs.eval(text);
	auto right = rhs.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>();

	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
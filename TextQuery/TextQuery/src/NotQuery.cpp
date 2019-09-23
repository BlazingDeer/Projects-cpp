#include "NotQuery.h"

NotQuery::NotQuery(const Query &q):
	query(q)
{
}

std::string NotQuery::rep() const
{
	return "~(" + query.rep() + ")";
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
	auto result = query.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	auto beg = result.begin();
	auto end = result.end();
	auto sz = result.get_file()->size();

	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n) ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}


Query operator~(const Query &operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}
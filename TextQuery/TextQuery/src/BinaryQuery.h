#pragma once
#include "Query.h"

class BinaryQuery : public Query_base
{
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s);

	std::string rep() const;

	Query lhs, rhs;
	std::string opSym;
};
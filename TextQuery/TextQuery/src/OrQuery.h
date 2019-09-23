#pragma once
#include "BinaryQuery.h"

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query &, const Query &);

	OrQuery(const Query &left, const Query &right);
	QueryResult eval(const TextQuery&)const;
};


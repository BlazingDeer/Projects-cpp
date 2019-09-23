#pragma once
#include "BinaryQuery.h"

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &left, const Query &right);
	QueryResult eval(const TextQuery &) const;
	
};




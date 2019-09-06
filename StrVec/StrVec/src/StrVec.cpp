#include "StrVec.h"

void StrVec::chk_n_alloc()
{
	if (size() == capacity()) reallocate();
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
	auto data = alloc.allocate(e - b);
	return {data,std::uninitialized_copy(b,e,data)};
}

void StrVec::free()
{
	if (elements)
	{
		for (auto p = first_free; p != elements;)
		{
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate()
{

	auto newcapacity = size() ? 2 * size() : 1;
	auto first = alloc.allocate(newcapacity);
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
	free();
	elements = first;
	first_free = last;
	cap = first+newcapacity;
}





StrVec::StrVec(): 
	elements(nullptr), first_free(nullptr), cap(nullptr)
{
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec::~StrVec()
{
	free();
}







void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}

size_t StrVec::size()
{
	return first_free - elements;
}

size_t StrVec::capacity()
{
	return cap - elements;
}

std::string *StrVec::begin() const
{
	return elements;
}

std::string *StrVec::end() const
{
	return first_free;
}

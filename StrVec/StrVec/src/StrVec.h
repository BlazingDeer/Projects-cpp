#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

class StrVec
{
private:
	std::allocator<std::string> alloc;
	void chk_n_alloc();
	std::pair<std::string *, std::string *> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

	std::string *elements;
	std::string *first_free;
	std::string *cap;



public:
	StrVec();
	StrVec(const StrVec &);
	StrVec &operator=(const StrVec &);
	~StrVec();
	void push_back(const std::string&);
	void push_back(std::string&&);
	size_t size();
	size_t capacity();
	std::string *begin() const;
	std::string *end() const;


};
#pragma once
#include <iostream>
#include <string>
#include "Folder.h"
#include <set>
#include <algorithm>

class Message
{
	friend class Folder;
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message &);
	void remove_from_Folders();
	void move_Folders(Message *m);
public:

	Message &operator=(Message &&);
	Message(Message &&);
	explicit Message(const std::string &);
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();
	void save(Folder &);
	void remove(Folder &);
	void swap(Message &, Message &);
};
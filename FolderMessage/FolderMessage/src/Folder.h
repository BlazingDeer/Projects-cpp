#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Message.h"

class Folder
{
	friend class Message;
private:
	std::set<Message *> messages;
	void remove_from_Messages();

public:
	Folder(const Folder &);
	Folder &operator=(const Folder &);
	~Folder();
	void addMsg(Message *);
	void remMsg(Message *);
};
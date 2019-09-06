#include "Folder.h"

void Folder::remove_from_Messages()
{
	std::set<Message *> cpMessages(messages);

	for (auto m : cpMessages)
	{
		m->remove(*this);
	}
}

Folder::Folder(const Folder &f)
{
	for (auto m : f.messages)
	{
		m->save(*this);
	}
}

Folder &Folder::operator=(const Folder &f)
{
	remove_from_Messages();

	for (auto m : f.messages)
	{
		m->save(*this);
	}

	return *this;
}

Folder::~Folder()
{
	remove_from_Messages();
}

void Folder::addMsg(Message *m)
{
	messages.insert(m);
}

void Folder::remMsg(Message *m)
{
	messages.erase(m);
}

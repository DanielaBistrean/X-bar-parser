#ifndef NODELIST_H
#define NODELIST_H 1

#include <list>
#include "struct.h"

struct NodeList
{
	NodeList() = default;
	NodeList(const NodeList& other);
	NodeList& operator=(const NodeList& other);
	NodeList(NodeList&& other);
	NodeList& operator=(NodeList&& other);

	std::list<Node*> nodes;
};

#endif

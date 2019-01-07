#include "nodeList.h"

NodeList::NodeList(const NodeList& other)
{
	for(const auto it : other.nodes)
	{
		nodes.push_back(new Node{*it});
	}
}

NodeList&
NodeList::operator=(const NodeList& other)
{
	nodes.clear();

	for(const auto it : other.nodes)
	{
		nodes.push_back(new Node{*it});
	}
}

NodeList::NodeList(NodeList&& other)
: nodes{std::move(other.nodes)}
{}

NodeList&
NodeList::operator=(NodeList&& other)
{
	nodes.clear();
	nodes = std::move(other.nodes);
}

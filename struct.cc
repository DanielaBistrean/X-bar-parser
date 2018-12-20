#ifndef STRUCT_H
#define STRUCT_H 1

#include <sstream>

#include "struct.h"

Node::Node (const NodeType &type)
: m_left {nullptr}
, m_right {nullptr}
, m_type  {type}
{}

std::string
Node::convertTypeToString(Node *node)
{
	switch(node->m_type)
	{
		case IP:
			return "IP";
		case IBAR:
			return "\\=I";
		case CP:
			return "CP";
		case CBAR:
			return "\\=C";
		case NP:
			return "NP";
		case NBAR:
			return "\\=N";
		case VP:
			return "VP";
		case VBAR:
			return "\\=V";
		case PP:
			return "PP";
		case PBAR:
			return "\\=P";
		case I:
		case C:
		case N:
		case V:
		case P:
		case SPECIFIER:
			return node->m_value;
	}
	throw std::runtime_error("Unknown type");
}

std::string
Node::printTree(const std::string& prefix)
{
	std::stringstream buffer;

	buffer << "[.";
	if (m_type == SPECIFIER)
		buffer << "Specifier ";
	if (m_type == I)
		buffer << "I ";
	if (m_type == V)
		buffer << "V ";
	if (m_type == P)
		buffer << "P ";
	if (m_type == C)
		buffer << "C ";
	if (m_type == N)
		buffer << "N ";
    buffer << convertTypeToString(this) << " ";

    // enter the next tree level - left and right branch
    if (m_left)
    {
    	buffer << m_left->printTree(prefix + "    ");
    }

    if (m_right)
	{
		buffer << m_right->printTree(prefix + "    ");
	}

	buffer << "] ";
	return buffer.str();
}

#endif

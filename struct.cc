#include <sstream>

#include "struct.h"

Node::Node (const NodeType &type)
: m_left {nullptr}
, m_right {nullptr}
, m_type  {type}
{}

Node::Node (const Node& other)
: m_type  {other.m_type}
, m_value {other.m_value}
, m_left  {nullptr}
, m_right {nullptr}
{
	if (other.m_left)
		m_left = new Node{*(other.m_left)};
	if (other.m_right)
		m_right = new Node{*(other.m_right)};
}

std::string
Node::convertTypeToString(const Node *node)
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

Node*
Node::combine(Node* first, Node* second)
{
	switch (first->getType())
	{
		case IP:
		{
			if (second->getType() == CP && !second->getLeft())
			{
				second->setLeft(first);
				return second;
			}
			break;
		}
		case NP:
		{
			if ((second->getType() == IP || second->getType() == CP) && !second->getLeft())
			{
				second->setLeft(first);
				return second;
			}
			else if (second->getType() == VP)
			{
				Node *ip = new Node{IP};
				ip->setRight(new Node(IBAR));
				ip->getRight()->setLeft(new Node(I));
				ip->getRight()->setRight(second);
				ip->setLeft(first);

				return ip;
			}
			break;
		}
		case PP:
		{
			if (second->getType() == NP)
			{
				first->getRight()->setRight(second);
				return first;
			}
			break;
		}
		case CP:
		{
			if (second->getType() == IP && !first->getRight()->getRight())
			{
				first->getRight()->setRight(second);
				return first;
			}
			break;
		}
		case VP:
		{
			if (second->getType() == NP || second->getType() == PP)
			{
				Node *bar = first->getRight();
				if (bar->getRight())
				{
					Node *newBar = new Node{VBAR};
					first->setRight(newBar);
					newBar->setLeft(bar);
					bar = newBar;
				}

				bar->setRight(second);
				return first;
			}
			break;
		}
		default:
			std::runtime_error("Invalid type");
	}

	return nullptr;
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

std::ostream&
operator<<(std::ostream& stream, const Node& n)
{
	return stream << Node::convertTypeToString(&n);
}

#include <iostream>
#include <string.h>

enum NodeType
{
	IP, IBAR, I,
	CP, CBAR, C,
	NP, NBAR, N,
	VP, VBAR, V,
	PP, PBAR, P,
	SPECIFIER,
};

class Node
{
public:
	Node(const NodeType &type);
	void setValue(const std::string &value) { m_value = value; 	}
	void setLeft(Node *left)	 			{ m_left = left;	}
	void setRight(Node *right)				{ m_right = right; 	}
	void setType(const NodeType &type) 		{ m_type = type; 	}
	std::string getValue() const			{ return m_value;	} // does not modify the value
	Node *getLeft() const				 	{ return m_left; 	}
	Node *getRight() const				 	{ return m_right;  	}
	NodeType getType() const			 	{ return m_type;	}
	std::string printTree(const std::string& prefix = "");
	static std::string convertTypeToString(Node *node);

private:
	std::string m_value;
	Node *m_left;
	Node *m_right;
	NodeType m_type;
};

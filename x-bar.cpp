#include "struct.h"
#include "lists.h"
#include "texcaller.h"

#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <stack>

int
main(int argc, char const *argv[])
{
	std::string input;
	std::vector<std::string> v;
	std::stack myStack;

	std::getline(std::cin, input);

	std::istringstream tmp {input};
	std::string word;

	while (tmp >> word)
	{
		v.push_back(word);
	}

	Node *current = nullptr;

	for (int i = v.size() - 1; i >= 0; --i)
	{
		auto foundD = std::find(determinersList.begin(), determinersList.end(), v[i]);

		if (foundD != determinersList.end())
		{
			Node *currentN = new Node(NP);
			currentN->setLeft(new Node(SPECIFIER));
			currentN->getLeft()->setValue(v[i]);

			currentN->setRight(new Node(NBAR));
			currentN->getRight()->setLeft(new Node(N));
			currentN->getRight()->getLeft()->setValue(v[i + 1]);
			// myStack.push(currentN);

			if (current != nullptr)
			{
				if (current->getType() == VP)
					current->setLeft(currentN);
				else
				{
					currentN->getRight()->setRight(current);
					current = currentN;
				}
			}
			else
				current = currentN;
			continue;
		}

		auto foundP = std::find(prepositionsList.begin(), prepositionsList.end(), v[i]);

		if (foundP != prepositionsList.end())
		{
			Node *currentN = new Node(PP);
			currentN->setRight(new Node(PBAR));
			currentN->getRight()->setLeft(new Node(P));
			currentN->getRight()->getLeft()->setValue(v[i]);

			if (current != nullptr)
			{
				currentN->getRight()->setRight(current);
			}

			current = currentN;
			continue;
		}

		auto foundV = std::find(verbsList.begin(), verbsList.end(), v[i]);

		if (foundV != verbsList.end())
		{
			Node *currentN = new Node(VP);
			currentN->setRight(new Node(VBAR));
			currentN->getRight()->setLeft(new Node(V));
			currentN->getRight()->getLeft()->setValue(v[i]);

			if (current != nullptr)
			{
				currentN->getRight()->setRight(current);
			}

			current = currentN;
			continue;
		}

		Node *stack = myStack.top();
		if (currentN->getType() == VP)
		{

		}
	}

	std::cout << current->printTree() << "\n";

	std::string latex =
        "\\documentclass[margin=5mm]{standalone} "
		"\\usepackage{tikz-qtree}"
		"\\begin{document}"
        "\\Tree " + current->printTree() + ""
        "\\end{document}";

	try {
        std::string pdf;
        std::string info;

        texcaller::convert(pdf, info, latex, "LaTeX", "PDF", 5);
        std::ofstream f("x-bar.pdf");
        f << pdf;

    } catch (std::domain_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
	
	return 0;
}

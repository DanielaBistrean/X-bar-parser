#include "struct.h"
#include "lists.h"
#include "texcaller.h"

#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <stack>
#include <functional>

struct special_compare : public std::unary_function<std::string, bool>
{
  explicit special_compare(const std::string &sword) : word(sword) {};
  bool operator() (const std::string &verb)
  {
  	auto it = word.find(verb);
  	auto dif = word.size() - verb.size();
  	if (it == 0)
  	{
  		std::string newWord = word.substr(verb.size(), dif);

  		if ((dif == 0) || (newWord == "ed" || newWord == "ded"))
  			return true;
  	}
  	
  	return false;
  };
  std::string word;
};


int
main(int argc, char const *argv[])
{
	std::string input;
	std::vector<std::string> v;
	std::stack<Node *> myStack;

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

			if ((!myStack.empty()) && (myStack.top()->getType() == VP))
			{
				Node *stack = myStack.top();
				Node *nodeIP = new Node(IP);
				nodeIP->setLeft(currentN);
				nodeIP->setRight(new Node(IBAR));
				nodeIP->getRight()->setRight(stack);
				nodeIP->getRight()->setLeft(new Node(I));
				currentN = nodeIP;
				myStack.push(currentN);
			}
			else if ((!myStack.empty()) && (myStack.top()->getType() == IP))
			{
				Node *stack = myStack.top();
				stack->setLeft(currentN);
			}
			else
				myStack.push(currentN);

			// if (current != nullptr)
			// {
			// 	if (current->getType() == VP)
			// 		current->setLeft(currentN);
			// 	else
			// 	{
			// 		currentN->getRight()->setRight(current);
			// 		current = currentN;
			// 	}
			// }
			// else
			// 	current = currentN;
			continue;
		}

		auto foundC = std::find(complementizersList.begin(), complementizersList.end(), v[i]);

		if (foundC != complementizersList.end())
		{
			Node *currentN = new Node(CP);
			currentN->setLeft(new Node(SPECIFIER));
			currentN->getLeft()->setValue(v[i]);

			currentN->setRight(new Node(CBAR));
			currentN->getRight()->setLeft(new Node(C));
			// currentN->getRight()->getLeft()->setValue(v[i + 1]);
			// while ((!myStack.empty()) && (myStack.top()->getType() == IP))
			// {
			// 	Node *prev = myStack.top();

			// 	myStack.pop();
				
			// 	Node *bar = currentN->getRight();
			// 	if (bar->getRight())
			// 	{
			// 		Node *newBar = new Node{CBAR};
			// 		currentN->setRight(newBar);
			// 		newBar->setLeft(bar);
			// 		bar = newBar;
			// 	}
			// 	bar->setRight(prev);
			// 	// currentN->getRight()->setRight(prev);
			// }
		}
		

		auto foundP = std::find(prepositionsList.begin(), prepositionsList.end(), v[i]);

		if (foundP != prepositionsList.end())
		{
			Node *currentN = new Node(PP);
			currentN->setRight(new Node(PBAR));
			currentN->getRight()->setLeft(new Node(P));
			currentN->getRight()->getLeft()->setValue(v[i]);

			if ((!myStack.empty()) && (myStack.top()->getType() == NP))
			{
				Node *stack = myStack.top();
				myStack.pop();
				currentN->getRight()->setRight(stack);
				myStack.push(currentN);
			}
			else
				myStack.push(currentN);

			// if (current != nullptr)
			// {
			// 	currentN->getRight()->setRight(current);
			// }

			// current = currentN;
			continue;
		}

		auto foundV = std::find_if(verbsList.begin(), verbsList.end(), special_compare{v[i]});

		if (foundV != verbsList.end())
		{
			Node *currentN = new Node(VP);
			currentN->setRight(new Node(VBAR));
			currentN->getRight()->setLeft(new Node(V));
			currentN->getRight()->getLeft()->setValue(*foundV);

			
			while ((!myStack.empty()) && (myStack.top()->getType() == NP || myStack.top()->getType() == PP))
			{
				Node *prev = myStack.top();

				myStack.pop();
				
				Node *bar = currentN->getRight();
				if (bar->getRight())
				{
					Node *newBar = new Node{VBAR};
					currentN->setRight(newBar);
					newBar->setLeft(bar);
					bar = newBar;
				}
				bar->setRight(prev);
				// currentN->getRight()->setRight(prev);
			}

			// std::string suffix = v[i].substr(foundV->size());

			// Node *nodeIP = new Node(IP);
			// // nodeIP->setLeft(currentN);
			// nodeIP->setRight(new Node(IBAR));
			// nodeIP->getRight()->setRight(currentN);
			// nodeIP->getRight()->setLeft(new Node(I));
			// nodeIP->getRight()->getLeft()->setValue("-" + suffix);
			// currentN = nodeIP;

			// myStack.push(currentN);

			// // if (current != nullptr)
			// // {
			// // 	currentN->getRight()->setRight(current);
			// // }

			// // current = currentN;
			// continue;
		}

		Node *currentN = new Node(NP);

		currentN->setRight(new Node(NBAR));
		currentN->getRight()->setLeft(new Node(N));
		currentN->getRight()->getLeft()->setValue(v[i]);
		// myStack.push(currentN);

		if ((!myStack.empty()) && (myStack.top()->getType() == VP))
		{
			Node *stack = myStack.top();
			Node *nodeIP = new Node(IP);
			nodeIP->setLeft(currentN);
			nodeIP->setRight(new Node(IBAR));
			nodeIP->getRight()->setRight(stack);
			nodeIP->getRight()->setLeft(new Node(I));
			currentN = nodeIP;
			myStack.push(currentN);
		}
		else if ((!myStack.empty()) && (myStack.top()->getType() == IP))
		{
			Node *stack = myStack.top();
			stack->setLeft(currentN);
		}
		else
			myStack.push(currentN);
	}

	std::cout << myStack.top()->printTree() << "\n";

	std::string latex =
        "\\documentclass[margin=5mm]{standalone} "
		"\\usepackage{tikz-qtree}"
		"\\begin{document}"
        "\\Tree " + myStack.top()->printTree() + ""
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

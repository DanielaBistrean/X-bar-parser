#include "struct.h"
#include "grammar.h"
#include "nodeList.h"
#include "texcaller.h"

#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <stack>
#include <functional>
#include <wn.h>
#include <vector>

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
	wninit();

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

	// Node *current = nullptr;

	// for (int i = v.size() - 1; i >= 0; --i)
	// {
	// 	auto foundD = std::find(determinersList.begin(), determinersList.end(), v[i]);

	// 	if (foundD != determinersList.end())
	// 	{
	// 		Node *currentN = new Node(NP);
	// 		currentN->setLeft(new Node(SPECIFIER));
	// 		currentN->getLeft()->setValue(v[i]);

	// 		currentN->setRight(new Node(NBAR));
	// 		currentN->getRight()->setLeft(new Node(N));
	// 		currentN->getRight()->getLeft()->setValue(v[i + 1]);
	// 		// myStack.push(currentN);

	// 		if ((!myStack.empty()) && (myStack.top()->getType() == VP))
	// 		{
	// 			Node *stack = myStack.top();
	// 			myStack.pop();
	// 			Node *nodeIP = new Node(IP);
	// 			nodeIP->setLeft(currentN);
	// 			nodeIP->setRight(new Node(IBAR));
	// 			nodeIP->getRight()->setRight(stack);
	// 			nodeIP->getRight()->setLeft(new Node(I));
	// 			currentN = nodeIP;
	// 			myStack.push(currentN);
	// 		}
	// 		else if ((!myStack.empty()) && (myStack.top()->getType() == IP))
	// 		{
	// 			Node *stack = myStack.top();
	// 			stack->setLeft(currentN);
	// 		}
	// 		else
	// 			myStack.push(currentN);

	// 		// if (current != nullptr)
	// 		// {
	// 		// 	if (current->getType() == VP)
	// 		// 		current->setLeft(currentN);
	// 		// 	else
	// 		// 	{
	// 		// 		currentN->getRight()->setRight(current);
	// 		// 		current = currentN;
	// 		// 	}
	// 		// }
	// 		// else
	// 		// 	current = currentN;
	// 		continue;
	// 	}

	// 	auto foundC = std::find(complementizersList.begin(), complementizersList.end(), v[i]);

	// 	if (foundC != complementizersList.end())
	// 	{
	// 		Node *currentN = new Node(CP);
	// 		currentN->setLeft(new Node(SPECIFIER));
	// 		// currentN->getLeft()->setValue(v[i]);

	// 		currentN->setRight(new Node(CBAR));
	// 		currentN->getRight()->setLeft(new Node(C));
	// 		currentN->getRight()->getLeft()->setValue(v[i]);
			
	// 		while ((!myStack.empty()) && (myStack.top()->getType() == IP))
	// 		{
	// 			Node *prev = myStack.top();

	// 			myStack.pop();
				
	// 			Node *bar = currentN->getRight();
	// 			if (bar->getRight())
	// 			{
	// 				Node *newBar = new Node{CBAR};
	// 				currentN->setRight(newBar);
	// 				newBar->setLeft(bar);
	// 				bar = newBar;
	// 			}
	// 			bar->setRight(prev);
	// 			// currentN->getRight()->setRight(prev);
	// 		}

	// 		myStack.push(currentN);
	// 		continue;
	// 	}
		

	// 	auto foundP = std::find(prepositionsList.begin(), prepositionsList.end(), v[i]);

	// 	if (foundP != prepositionsList.end())
	// 	{
	// 		Node *currentN = new Node(PP);
	// 		currentN->setRight(new Node(PBAR));
	// 		currentN->getRight()->setLeft(new Node(P));
	// 		currentN->getRight()->getLeft()->setValue(v[i]);

	// 		if ((!myStack.empty()) && (myStack.top()->getType() == NP))
	// 		{
	// 			Node *stack = myStack.top();
	// 			myStack.pop();
	// 			currentN->getRight()->setRight(stack);
	// 			myStack.push(currentN);
	// 		}
	// 		else
	// 			myStack.push(currentN);

	// 		// if (current != nullptr)
	// 		// {
	// 		// 	currentN->getRight()->setRight(current);
	// 		// }

	// 		// current = currentN;
	// 		continue;
	// 	}

	// 	auto foundV = std::find_if(verbsList.begin(), verbsList.end(), special_compare{v[i]});

	// 	// if (foundV != verbsList.end())
	// 	if (isVerb(v[i]))
	// 	{
	// 		Node *currentN = new Node(VP);
	// 		currentN->setRight(new Node(VBAR));
	// 		currentN->getRight()->setLeft(new Node(V));
	// 		currentN->getRight()->getLeft()->setValue(v[i]);

			
	// 		while ((!myStack.empty()) && (myStack.top()->getType() == NP || myStack.top()->getType() == PP))
	// 		{
	// 			Node *prev = myStack.top();

	// 			myStack.pop();
				
	// 			Node *bar = currentN->getRight();
	// 			if (bar->getRight())
	// 			{
	// 				Node *newBar = new Node{VBAR};
	// 				currentN->setRight(newBar);
	// 				newBar->setLeft(bar);
	// 				bar = newBar;
	// 			}
	// 			bar->setRight(prev);
	// 			// currentN->getRight()->setRight(prev);
	// 		}

	// 		// std::string suffix = v[i].substr(foundV->size());

	// 		// Node *nodeIP = new Node(IP);
	// 		// // nodeIP->setLeft(currentN);
	// 		// nodeIP->setRight(new Node(IBAR));
	// 		// nodeIP->getRight()->setRight(currentN);
	// 		// nodeIP->getRight()->setLeft(new Node(I));
	// 		// nodeIP->getRight()->getLeft()->setValue("-" + suffix);
	// 		// currentN = nodeIP;

	// 		myStack.push(currentN);

	// 		// // if (current != nullptr)
	// 		// // {
	// 		// // 	currentN->getRight()->setRight(current);
	// 		// // }

	// 		// // current = currentN;
	// 		continue;
	// 	}

	// 	// Node *currentN = new Node(NP);

	// 	// currentN->setRight(new Node(NBAR));
	// 	// currentN->getRight()->setLeft(new Node(N));
	// 	// currentN->getRight()->getLeft()->setValue(v[i]);
	// 	// // myStack.push(currentN);

	// 	// if ((!myStack.empty()) && (myStack.top()->getType() == VP))
	// 	// {
	// 	// 	Node *stack = myStack.top();
	// 	// 	Node *nodeIP = new Node(IP);
	// 	// 	nodeIP->setLeft(currentN);
	// 	// 	nodeIP->setRight(new Node(IBAR));
	// 	// 	nodeIP->getRight()->setRight(stack);
	// 	// 	nodeIP->getRight()->setLeft(new Node(I));
	// 	// 	currentN = nodeIP;
	// 	// 	myStack.push(currentN);
	// 	// }
	// 	// else if ((!myStack.empty()) && (myStack.top()->getType() == IP))
	// 	// {
	// 	// 	Node *stack = myStack.top();
	// 	// 	stack->setLeft(currentN);
	// 	// }
	// 	// else
	// 	// 	myStack.push(currentN);
	// }

	// // for (auto it : myStack)
	// // {
	// // 	auto aux = it->getType();
	// // 	std::cout << convertTypeToString(aux);
	// // }

	// if (myStack.size() > 1)
	// {
	// 	if (myStack.top()->getType() == IP)
	// 	{
	// 		Node *IPelem = myStack.top();
	// 		myStack.pop();

	// 		Node *tmp = myStack.top();
	// 		std::cout << Node::convertTypeToString(tmp);
	// 		if (myStack.top()->getType() == CP)
	// 		{
	// 			Node *CPelem = myStack.top();

	// 			CPelem->setLeft(IPelem);
	// 		}
	// 		else
	// 		{
	// 			myStack.push(IPelem);
	// 		}
	// 	}
	// }

	std::vector <NodeList> posibilities;
	posibilities.push_back(std::move(NodeList{}));

	for (auto it = v.rbegin(); it != v.rend(); ++it)
	{
		std::vector <NodeList> current;
		std::string word = *it;
		bool found = false;

		if (isDet(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (!it.nodes.empty() && it.nodes.front()->getType() == NP)
				{
					NodeList n{it};

					Node *currentN = n.nodes.front();
					currentN->getLeft()->setValue(word);

					{
						// auto merge
						auto it = std::next(n.nodes.begin());
						if (it != n.nodes.end() && (*it)->getType() == IP)
						{
							// remove the NP
							n.nodes.pop_front();

							Node *ip = n.nodes.front();
							ip->setLeft(currentN);
						}

					}

					current.push_back(std::move(n));
				}
			}
		}

		if (isAdj(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (!it.nodes.empty() && it.nodes.front()->getType() == NP)
				{
					// ToDo: add adjectiv support
					// NodeList n{it};

					// Node *currentN = n.nodes.front();
					// currentN->getLeft()->setValue(word);

					// current.push_back(std::move(n));
				}
			}
		}

		if (isVerb(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (it.nodes.empty() || it.nodes.front()->getType() == PP || it.nodes.front()->getType() == NP)
				{
					NodeList n{it};

					Node *currentN = new Node(VP);
					currentN->setRight(new Node(VBAR));
					currentN->getRight()->setLeft(new Node(V));
					currentN->getRight()->getLeft()->setValue(word);

					{
						// auto merge
						while (!n.nodes.empty() && (n.nodes.front()->getType() == PP || n.nodes.front()->getType() == NP))
						{
							Node *tmp = n.nodes.front();
							n.nodes.pop_front();

							Node *bar = currentN->getRight();
							if (bar->getRight())
							{
								Node *newBar = new Node{VBAR};
								currentN->setRight(newBar);
								newBar->setLeft(bar);
								bar = newBar;
							}

							bar->setRight(tmp);
						}

						Node *ip = new Node{IP};
						ip->setRight(new Node(IBAR));
						ip->getRight()->setLeft(new Node(I));
						ip->getRight()->setRight(currentN);
						currentN = ip;
					}

					n.nodes.push_front(currentN);
					current.push_back(std::move(n));
				}
			}
		}

		if (isAdv(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (!it.nodes.empty() && it.nodes.front()->getType() == VP)
				{
					// ToDo: add adv support
					// NodeList n{it};

					// Node *currentN = n.nodes.front();
					// currentN->getLeft()->setValue(word);

					// current.push_back(std::move(n));
				}
			}
		}

		if (isPrep(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (!it.nodes.empty() && it.nodes.front()->getType() == NP)
				{
					NodeList n{it};

					Node *currentN = new Node(PP);
					currentN->setRight(new Node(PBAR));
					currentN->getRight()->setLeft(new Node(P));
					currentN->getRight()->getLeft()->setValue(word);

					{
						// auto merge
						Node *np = n.nodes.front();
						n.nodes.pop_front();

						currentN->getRight()->setRight(np);
					}

					n.nodes.push_front(currentN);
					current.push_back(std::move(n));
				}
			}
		}

		if (isComp(word))
		{
			found = true;
			for (const auto & it : posibilities)
			{
				if (!it.nodes.empty() && (it.nodes.front()->getType() == IP || it.nodes.front()->getType() == NP))
				{
					NodeList n{it};

					Node *currentN = new Node(CP);
					currentN->setRight(new Node(CBAR));
					currentN->getRight()->setLeft(new Node(C));
					currentN->getRight()->getLeft()->setValue(word);

					{
						// auto merge
						bool cont = false;
						if (n.nodes.front()->getType() == NP)
						{
							auto it = std::next(n.nodes.begin());
							if (it != n.nodes.end() && (*it)->getType() == IP)
							{
								Node *np = n.nodes.front();
								n.nodes.pop_front();

								Node *ip = n.nodes.front();
								ip->setLeft(np);

								cont = true;
							}
						}
						else
							cont = true;

						if (cont)
						{
							Node *ip = n.nodes.front();
							n.nodes.pop_front();

							currentN->getRight()->setRight(ip);
						}
					}

					n.nodes.push_front(currentN);
					current.push_back(std::move(n));
				}
			}
		}

		if (isNoun(word) || found == false)
		{
			for (const auto & it : posibilities)
			{
				if (it.nodes.empty() || it.nodes.front()->getType() == PP || it.nodes.front()->getType() == IP || it.nodes.front()->getType() == CP)
				{
					NodeList n{it};

					Node *currentN = new Node(NP);
					currentN->setLeft(new Node(SPECIFIER));
					currentN->setRight(new Node(NBAR));
					currentN->getRight()->setLeft(new Node(N));
					currentN->getRight()->getLeft()->setValue(word);

					n.nodes.push_front(currentN);
					current.push_back(std::move(n));
				}
			}
		}

		posibilities.swap(current);
		unsigned cnt = 0;
		for (auto &it : posibilities)
		{
			std::cout << cnt++ << " \t:\t\t";
			for (auto i : it.nodes)
				std::cout << " " << *i;
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	std::vector<NodeList> solution;

	for (auto &p : posibilities)
	{
		if (p.nodes.size() == 1)
		{
			solution.push_back(std::move(p));
		}
		else
		{
			bool nok = false;

			auto first = p.nodes.begin();
			auto second = std::next(first);
			int i = 0;
			int j = 1;
			while (p.nodes.size() > 1)
			{
				if (second == p.nodes.end())
				{
					nok = true;
					break;
				}

				Node *tmp = Node::combine(*first, *second);

				if (tmp == *first)
				{
					second = p.nodes.erase(second);
				}
				else if (tmp == *second)
				{
					first = p.nodes.erase(first);
				}
				else if (tmp == nullptr)
				{
					first = second++;
				}
				else
				{
					second = p.nodes.erase(second);
					*first = tmp;
				}
			}

			if (!nok)
				solution.push_back(std::move(p));
		}
	}


	if (!solution.empty())
	{
		NodeList& n = solution[0];
		std::cout << "Is here?\n";

		if (!n.nodes.empty())
		{
			std::cout << "Is here?\n";
			std::cout << n.nodes.front()->printTree() << "\n";

			std::string latex =
		        "\\documentclass[margin=5mm]{standalone} "
				"\\usepackage{tikz-qtree}"
				"\\begin{document}"
		        "\\Tree " + n.nodes.front()->printTree() + ""
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
		}
	}


	// std::cout << myStack.top()->printTree() << "\n";

	
	return 0;
}

#include "grammar.h"
#include <wn.h>
#include <algorithm>
#include <vector>

std::vector<std::string> determinersList =
{
	"the",
	"a",
	"an",
	"this",
	"that",
	"these",
	"those",
	"my",
	"your",
	"his",
	"her",
	"its",
	"our",
	"their",
	"a few",
	"a little",
	"much",
	"many",
	"a lot of",
	"most",
	"some",
	"any",
	"enough",
	"one",
	"ten",
	"thirty",
	"all",
	"both",
	"half",
	"either",
	"neither",
	"each",
	"every",
	"other",
	"another",
	"such",
	"what",
	"rather",
	"quite"
};

std::vector<std::string> prepositionsList =
{
	"on",
	"in",
	"at",
	"since",
	"for",
	"ago",
	"before",
	"to",
	"past",
	"to",
	"till",
	"until",
	"by",
	"next to",
	"beside",
	"under",
	"below",
	"over",
	"above",
	"across",
	"through",
	"into",
	"towards",
	"onto",
	"from",
	"of",
	"off",
	"out of",
	"about"
};

std::vector<std::string> complementizersList =
{
	"what",
	"who",
	"when",
	"where",
	"that",
	"whose",
	"which",
	"whom"
};

bool
isVerb(std::string word)
{
	auto found = morphstr((char *) word.c_str(), VERB);
	auto found2 = in_wn((char *) word.c_str(), VERB);

	if (found != nullptr || found2 > 0)
		return true;
	else
		return false;
}

bool
isNoun(std::string word)
{
	auto found = morphstr((char *) word.c_str(), NOUN);
	auto found2 = in_wn((char *) word.c_str(), NOUN);

	if (found != nullptr || found2 > 0)
		return true;
	else
		return false;
}

bool
isAdj(std::string word)
{
	auto found = morphstr((char *) word.c_str(), ADJ);
	auto found2 = in_wn((char *) word.c_str(), ADJ);

	if (found != nullptr || found2 > 0)
		return true;
	else
		return false;
}

bool
isAdv(std::string word)
{
	auto found = morphstr((char *) word.c_str(), ADV);
	auto found2 = in_wn((char *) word.c_str(), ADV);

	if (found != nullptr || found2 > 0)
		return true;
	else
		return false;
}

bool
isDet(std::string word)
{
	auto foundD = std::find(determinersList.begin(), determinersList.end(), word);

	return (foundD != determinersList.end());
}

bool
isPrep(std::string word)
{
	auto foundP = std::find(prepositionsList.begin(), prepositionsList.end(), word);

	return (foundP != prepositionsList.end());
}

bool
isComp(std::string word)
{
	auto foundC = std::find(complementizersList.begin(), complementizersList.end(), word);

	return (foundC != complementizersList.end());
}

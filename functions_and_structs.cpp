/** 
*	@file functions_and_structs.cpp
*	@brief File containing the functions outlined in this file's header.
*	@details Contains bodies of functions declared in the functions_and_structs header.
*	@author Jakub Daz
*	@bug No known bugs.
*/

/* -- Includes -- */

/* functions_and_structs header file. */
#include "functions_and_structs.h"

std::map<char, int> CreateMap(const std::string& fileName)
{
	std::map<char, int > resultMap;
	std::ifstream inputFileStream(fileName);

	if (inputFileStream)
	{
		std::string tempString;
		while (std::getline(inputFileStream, tempString))
		{
			for (const char character : tempString)
			{
				if (!resultMap.contains(character))
					resultMap.insert({ character, 0 });
				resultMap[character]++;
			}
		}
		inputFileStream.close();
	}
	return resultMap;
}

std::vector<std::pair<int, char>> CreateVector(const std::map<char, int> takeFromMap)
{
	std::vector<std::pair<int, char>> resultVector;
	std::pair<int, char> tempPair;

	for (const std::pair<char, int> el : takeFromMap)
	{
		tempPair.first = el.second;
		tempPair.second = el.first;
		resultVector.push_back(tempPair);
	}
	return resultVector;
}

std::vector<std::pair<char, int>> SortVectorMinToMax(const std::vector<std::pair<int, char>>& inVect)
{
	std::vector<std::pair<char, int>> resultVector;

	std::priority_queue <std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<std::pair<int, char>>> sortingPriorityQueue;
	for (const auto& el : inVect)
	{
		sortingPriorityQueue.push(el);
	}

	std::pair<char, int> tempPair;

	while (!sortingPriorityQueue.empty())
	{
		tempPair.first = sortingPriorityQueue.top().second;
		tempPair.second = sortingPriorityQueue.top().first;
		resultVector.push_back(tempPair);
		sortingPriorityQueue.pop();
	}

	return resultVector;
}

void CompressToDiffrentFile(const std::string& fromFile, const std::string& toFile, const std::map<char, std::string>& dictionary)
{
	std::ifstream fromFileStream(fromFile);
	std::ofstream toFileStream(toFile);
	if (fromFileStream)
	{
		if (toFileStream)
		{
			std::string temp;

			bool isNotEmpty = bool(std::getline(fromFileStream, temp));

			while (isNotEmpty)
			{
				for (const char el : temp)
				{
					toFileStream << dictionary.find(el)->second;
				}
				isNotEmpty = bool(std::getline(fromFileStream, temp));
				if (isNotEmpty) toFileStream << std::endl;
			}
			toFileStream.close();
		}
		fromFileStream.close();
	}
}

void DecompressToDiffrentFile(const std::string& fromFile, const std::string& toFile, const std::map<char, std::string>& dictionary)
{
	std::ifstream From(fromFile);
	std::ofstream To(toFile);

	if (From)
	{
		if (To)
		{
			std::map<std::string, char> tempDictionary;
			std::pair<std::string, char> tempPairToEmplace;
			for (const auto el : dictionary)
			{
				tempPairToEmplace = { el.second, el.first };
				tempDictionary.emplace(tempPairToEmplace);
			}

			std::string tempLine, tempKey;

			bool isNotEmpty = bool(std::getline(From, tempLine));
			while (isNotEmpty)
			{
				for (const char el : tempLine)
				{
					tempKey += el;
					if (tempDictionary.contains(tempKey))
					{
						To << tempDictionary[tempKey];
						tempKey.clear();
					}
				}

				isNotEmpty = bool(std::getline(From, tempLine));
				if (isNotEmpty)
					To << std::endl;
			}
			To.close();
		}
		From.close();
	}
}

void DeleteHuff(HuffNode*& pRoot)
{
	if (!pRoot)
		return;

	DeleteHuff(pRoot->leftNode);
	delete(pRoot->leftNode);
	pRoot->leftNode = nullptr;

	DeleteHuff(pRoot->rightNode);
	delete(pRoot->rightNode);
	pRoot->rightNode = nullptr;
}

void DeleteHuffEntirely(HuffNode*& pRoot)
{
	DeleteHuff(pRoot);
	delete(pRoot);
	pRoot = nullptr;
}

HuffNode* findMinNode(std::queue<HuffNode*>& leafQueue, std::queue<HuffNode*>& nodeQueue)
{
	HuffNode* temp;

	if (leafQueue.empty()) {
		temp = nodeQueue.front();
		nodeQueue.pop();
		return temp;
	}
	if (nodeQueue.empty())
	{
		temp = leafQueue.front();
		leafQueue.pop();
		return temp;
	}

	if (leafQueue.front()->frequency < nodeQueue.front()->frequency)
	{
		temp = leafQueue.front();
		leafQueue.pop();
		return temp;
	}
	else
	{
		temp = nodeQueue.front();
		nodeQueue.pop();
		return temp;
	}
}

HuffNode* HuffmanCoding(std::vector<std::pair<char, int>>& vect)
{
	if (vect.empty())
	{
		std::cout << "Empty Vector, Failed";
		return NULL;
	}
	std::queue<HuffNode*> leafNodeQueue;
	std::queue<HuffNode*> regularNodeQueue;
	for (const std::pair<char, int>& el : vect)
	{
		leafNodeQueue.push(new HuffNode(el.first, el.second));
	}
	while (!leafNodeQueue.empty() || regularNodeQueue.size() > 1)
	{
		HuffNode* left = findMinNode(leafNodeQueue, regularNodeQueue);
		HuffNode* right = findMinNode(leafNodeQueue, regularNodeQueue);
		HuffNode* brandNew = new HuffNode((left->frequency + right->frequency), left, right);
		regularNodeQueue.push(brandNew);
	}
	return regularNodeQueue.front();
}

void MakeDictionary(HuffNode* pRoot, std::map<char, std::string>& resultMap, std::string hold)
{
	if (!pRoot)
		return;
	if (!pRoot->isHuffNodeWithoutChar)
	{
		resultMap.emplace(pRoot->character, hold);
	}
	MakeDictionary(pRoot->leftNode, resultMap, hold + '0');
	MakeDictionary(pRoot->rightNode, resultMap, hold + '1');

	return;
}

std::string RestOfString(const std::string& operatee)
{
	std::string result;
	for (int i = 2; i < operatee.length(); ++i)
	{
		result += operatee[i];
	}
	return result;
}

std::map<char, std::string> ReadDictionary(const std::string& fileName)
{
	std::map<char, std::string> resultDictionary;
	std::ifstream inFileStream(fileName);
	if (inFileStream)
	{
		std::string temp;
		std::string rtemp;
		while (std::getline(inFileStream, temp))
		{
			rtemp = RestOfString(temp);
			resultDictionary.emplace(temp[0], rtemp);
		}
		inFileStream.close();
	}
	return resultDictionary;
}

void SaveDictionary(const std::map<char, std::string>& dictionary, const std::string& fileName)
{
	std::ofstream outStream(fileName);
	if (outStream)
	{
		for (const auto& el : dictionary)
		{
			outStream << el.first << ' ' << el.second << std::endl;
		}
		outStream.close();
	}
}
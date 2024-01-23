/** 
*	@file functions_and_structs.h
*	@brief Structures and declaration of functions for the project.
*	@details Contains the HuffNode structure used in the Huffman Compression to create the binary tree from which codes may be read,
*   as well as declarations of functions used in it.
*	@author Jakub Daz
*	@bug No known bugs.
*/

#ifndef functions_and_structs_h
#define functions_and_structs_h

/* -- Includes -- */

/* map library. */
#include <map>

/* string library. */
#include <string>

/* fstream library. */
#include <fstream>

/* vector library. */
#include <vector>

/* queue library. */
#include <queue>

/* iostream library.*/
#include <iostream>

/**
* @brief Structure to make nodes and leafes for Huffman's binary tree.
* @details
*/
struct HuffNode
{
/**
* @brief Character of a node (used for leaf nodes).
*/
	char character;
	
/**
* @brief Frequency of the character or characters in associated leaf nodes of this node.
*/
	unsigned int frequency;
	
/**
* @brief Pointer to a node/leaf that is smaller (has lower frequency than the right node/leaf.
*/
	struct HuffNode* leftNode;
	
/**
* @brief Pointer to a node/leaf that is bigger (has higher frequency than the left node/leaf).
*/
	struct HuffNode* rightNode;

/**
* @brief Determines whether the node is a leaf node or a coupling of leaf/regular nodes.
*/
	bool isHuffNodeWithoutChar;
	
//! A constructor for leaf nodes (Nodes with characters and without associated pointers).
	HuffNode(char inputedCharacter, unsigned int inputedFrequency, HuffNode* lftNode = nullptr, HuffNode* rghtNode = nullptr)
	{
		character = inputedCharacter;
		frequency = inputedFrequency;
		leftNode = lftNode;
		rightNode = rghtNode;
		isHuffNodeWithoutChar = false;
	}
	
//! A constructor for non-leaf nodes ("Regular nodes").
	HuffNode(unsigned int inputedFrequency, HuffNode* lftNode, HuffNode* rghtNode)
	{
		character = NULL;
		frequency = inputedFrequency;
		leftNode = lftNode;
		rightNode = rghtNode;
		isHuffNodeWithoutChar = true;
	}
};

/**
* @brief Create a frequency map of characters from file.
* @details Creates a frequency map consisting of the character as map's key and frequency as the key's value.
* @param fileName Addres of file from which to create the frequency map.
* @return Frequency map.
*/
std::map<char, int> CreateMap(const std::string& fileName);

/**
* @brief Creates vector from the frequency map.
* @details Creates a vector of pairs (pair of int by char) from the frequency map.
* @param takeFromMap Frequency map from which to create vector.
* @return Vector of pair's int and char
*/
std::vector<std::pair<int, char>> CreateVector(const std::map<char, int> takeFromMap);

/**
* @brief Make vector of pairs (char by int) that is sorted from min to max.
* @details Creates a vector of pairs (char by int), from a vector of pairs int by char,
* that is sorted from smallest int value to biggest int value (non-decreasing pairs).
* @param inVect Vector of pairs int by char.
* @return Vector of pair's char by int that is sorted non-decreasingly.
*/
std::vector<std::pair<char, int>> SortVectorMinToMax(const std::vector<std::pair<int, char>>& inVect);

/**
* @brief Compress from inputed file to output file and make dictionary.
* @details Compresses from inputed file to output file and make dictionary of that file.
* @param fromFile Address of the inputed file.
* @param toFile Address of the file where data is to be saved.
* @param dictionary Address of the file where dictionary is to be saved.
*/
void CompressToDiffrentFile(const std::string& fromFile, const std::string& toFile, const std::map<char, std::string>& dictionary);

/**
* @brief Decompress from inputed file to output file with the use of provided dictionary.
* @details Decompresses from inputed file to output file with the use of provided dictionary.
* @param fromFile Address of the inputed file.
* @param toFile Address of the file where data is to be saved.
* @param dictionary Address of the file where the dictionary file of inputed file is.
*/
void DecompressToDiffrentFile(const std::string& fromFile, const std::string& toFile, const std::map<char, std::string>& dictionary);

/**
* @brief Delete all nodes of huffman tree besides the root.
* @details Recursively delete all nodes and leafes of the huffman's tree except for the root node.
* @param pRoot pointer to the huffman's trees root.
*/
void DeleteHuff(HuffNode*& pRoot);

/**
* @brief Delete all nodes of huffman tree including the root.
* Invokes DeleteHuff and then deletes and assignes nullptr to pRoot.
* @param pRoot pointer to the huffman's trees root.
*/
void DeleteHuffEntirely(HuffNode*& pRoot);

/**
* @brief Finds the smallest HuffNode in Queues.
* @details Takes in two queues and compares them, leafQueue is checked first if nodeQueue is empty,
* nodeQueue is checked first if leafQueue is empty, if neither is empty it check against leafQueue against nodeQueue,
* if frequencies of nodes on both queues are the same it prioritizes nodeQueue.
* @param leafQueue Queue of HuffNode's leafes (nodes with chars).
* @param nodeQueue Queue of Huffnode's regular nodes.
*/
HuffNode* findMinNode(std::queue<HuffNode*>& leafQueue, std::queue<HuffNode*>& nodeQueue);

/**
* @brief Makes huffman's binary tree from a non-decreasing vector.
* @details Takes a non-decreasing vector of pairs char by int as input and generates a huffman tree from it.
* The generation work in the following algorythm:
* 1. Take an element from the sorted vector.
* 2. Generate a HuffNode from it using the first variable of the pair as the character of the leaf node, 
* and second as the frequency of it, push that to the leafQueue node.
* 3. Repeat steps 1. and 2. untill you have iterated through the entire vector.
* 4. Find two smallest nodes from the leafQueue and the nodeQueue
* 5. Assign those two nodes two the pointer's of a brand new node that has frequency equal to the sum of those two nodes.
* 6. Push the brand new node pointer onto the nodeQueue
* 7. Repeat steps 4. through 6. untill leafQueue is empty and nodeQueue has no more than one element
* 8. On the nodeQueue there will be the pointer to the root, return it as the result.
* @param vect Vector of pairs (char by int) sorted in an non-decreasing manner.
* @return Pointer to the root.
*/
HuffNode* HuffmanCoding(std::vector<std::pair<char, int>>& vect);

/**
* @brief Makes a map where keys are characters and values are corresponding huffman codes.
* @details Recursively goes through a huffman tree and emplaces onto the given map corresponding pair of
* characters and their codes.
* @param pRoot Pointer to the root of the tree.
* @param resultMap Map onto which characters and their codes will be emplaced, passed as a reference.
* @param hold String which is used through recursive huffman tree traversal to hold onto the value of codes.
*/
void MakeDictionary(HuffNode* pRoot, std::map<char, std::string>& resultMap, std::string hold = "");

/**
* @brief Function which assists during ReadDictionary.
* @details Function which assists during the fuction ReadDictionary which reads dictionary from file.
* the functions takes from a string all characters that have index of two and upwards and places them into the resulting string.
* The format in which the dictionary is saved is done so there is a character, a space, and then the huffman code of the character. 
* @param operatee String from which the code is to be taken.
* @return String with the huffman code to return.
*/
std::string RestOfString(const std::string& operatee);

/**
* @brief Reads dictionary from the inputed file and returns it as a map.
* @param fileName Addres of the inputed file.
* @return Dictionary - Map with characters as keys and their codes as values.
*/
std::map<char, std::string> ReadDictionary(const std::string& fileName);

/**
* @brief Saves the dictionary to a file.
* @details Saves the map of characters as keys and their codes as the values of the keys into the file,
* whose addres has been given as the parameter.
* @param dictionary Map of characters as keys and their codes as the values.
* @oaram fileName Addres to the file in which the dictionary will be saved.
*/
void SaveDictionary(const std::map<char, std::string>& dictionary, const std::string& fileName);
#endif
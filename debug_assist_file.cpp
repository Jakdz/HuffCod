/** 
*	@file debug_assist_file.cpp
*	@brief File containing the functions outlined in this file's header.
*	@details Contains bodies of functions declared in the debug_assist_file header.
*	@author Jakub Daz
*	@bug No known bugs.
*/

/* -- Includes -- */

/* debug_assist_file header file. */
#include "debug_assist_file.h"

void DetectLeaks()
{
	std::cout << "The following will be memory leaks ";
	system("pause");
	std::cout << std::endl;

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtDumpMemoryLeaks();

	std::cout << std::endl;
	system("pause");
}
void ShowMapCharByString(const std::map<char, std::string>& map)
{
	for (const auto& el : map) {
		std::cout << std::setw(5) << '\"' << el.first << "\" " << '|' << std::setw(5) << el.second << std::endl;
	}
}
void ShowMapCharByInt(const std::map<char, int>& map) {
	for (const auto& el : map) {
		std::cout << std::setw(5) << '\"' << el.first << "\" " << '|' << std::setw(5) << el.second << std::endl;
	}
}
void PrintHuffmanCode(HuffNode* pRoot, std::string code = "")
{
	if (!pRoot)
		return;
	if (!pRoot->isHuffNodeWithoutChar)
	{
		std::cout << pRoot->character << ": " << code << '\n';
	}
	PrintHuffmanCode(pRoot->leftNode, code + '0');
	PrintHuffmanCode(pRoot->rightNode, code + '1');

	return;
}
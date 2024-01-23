/**
*	@file debug_assist_file.h
*	@brief Functions to help with debugging.
*	@details Contains declaration's of functions used in debugging process of the Huffman coding project.
*	@author Jakub Daü
*	@bug No known bugs.
*/

#ifndef debug_assist_file_h
#define debug_assist_file_h

/* -- Includes -- */

/* stdlib header, standard C library. */
#include <stdlib.h>

/* crtdbg header, C-Run Time Debugger. */
#include <crtdbg.h>

/* map library. */
#include <map>

/* string library. */
#include <string>

/* iomanip library. */
#include <iomanip>

/* iostream library.*/
#include <iostream>

/* functions_and_structs header file. */
#include "functions_and_structs.h"

/* @def Defines flag that makes is so the base versions of the heap functions are directly mapped to their debug version in Visual Studio 2022*/
#define _CRTDBG_MAP_ALLOC

/**
* @brief Show map with 'char' as key and 'string' as argument.
* @details Displays on the console map with 'char' as key and 'string' as argument.
* @param map Map to display on console.
*/
void ShowMapCharByString(const std::map<char, std::string>& map);

/**
* @brief Show map with 'char' as key and 'int' as argument.
* @details Displays on the console map with 'char' as key and 'int' as argument.
* @param map Map to display on console.
*/
void ShowMapCharByInt(const std::map<char, int>& map);

/**
* @brief Display's memory leaks.
* @detauks Displays on the console memory leaks.
*/
void DetectLeaks();

/**
* @brief Prints Huffman codes for each character. 
* @details Prints on the console codes for leaf in the Huffman's binary tree.
* @param pRoot HuffNode pointer to the root of the Huffman's binary tree.
* @param code Not to be used when using the function to display the tree, it's in displaying the codes in the recursive function.
*/
void PrintHuffmanCode(HuffNode* pRoot, std::string code);
#endif 
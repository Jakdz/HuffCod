/**
*	@file HuffCod.cpp
*	@brief Main file of the project.
*	@details This file contains the project's 'main()' function.
*	@author Jakub Daz
*	@bug No known bugs.
*/

/* -- Includes -- */

/* iostream library. */
#include <iostream>

/* string library. */
#include <string>

/* vector library. */
#include <vector>

/* map library. */
#include <map>

/* debug_assist_file header file*/
#include "debug_assist_file.h"

/* functions_and_structs header file */
#include "functions_and_structs.h"

/**
* @brief Check number of arguments inputed.
* @details This function checks if the number of arguments inputed is even or if there is more than nine arguments.
* If either is the case it returns false.
* @param numberOfArguments - number of arguments that have been inputed
* @return Returns boolean value of 'true' if the number of inputed arguments is correct. False if it isn't.
*/
bool ControlForNumberOfArguments(const int& numberOfArguments)
{
	if (!(numberOfArguments % 2) || numberOfArguments > 9)
	{
		std::cout << std::endl <<  "Inappropriate number of arguments used. Aborted." << std::endl;
		return false;
	}
	return true;
}

/**
* @brief Make map of arguments and check if correct switches are present.
* @details This function makes a map consisting of inputed arguments and checks if correct switches are present.
* Said map consists of switches of the program as keys and values of keys are equal to arguments relevant to any given switch.
* Checks of this function consist of checking if:
* 1. Map contains all relevant switches for the program to function.
* 2. The switches "-i", "-o" and "-s" have non empty arguments.
* 3. The switch "-t" has either of releveant arguments (either "k" or "d").
* @param numberOfArguments Is used as index to assign values to the map.
* @param arguments Arguments passed through console.
* @return Map of switches assigned relevant arguments for them.
*/
std::map<std::string, std::string> ControlForArguments (const int& numberOfArguments,char** arguments)
{
	std::map<std::string, std::string> mapOfArguments;
	
	for (size_t i = 1; i < numberOfArguments; i += 2)
	{
		mapOfArguments[arguments[i]] = arguments[i + 1];
	}
	if (!mapOfArguments.contains("-t") && !mapOfArguments.contains("-i") && !mapOfArguments.contains("-o") && !mapOfArguments.contains("-s"))
	{
		std::cout << std::endl << "Inappropriate number of switches used. Aborted." << std::endl;
		return {};
	}
	if ((mapOfArguments["-i"] == "") || (mapOfArguments["-o"] == "") || (mapOfArguments["-s"] == ""))
	{
		std::cout << std::endl << "One of the switches is empty. Aborted" << std::endl;
		return {};
	}
	if (!(mapOfArguments["-t"] == "k" || mapOfArguments["-t"] == "d"))
	{
		std::cout << std::endl << "Inappropriate argument for -t used. Aborted." << std::endl;
		return {};
	}
	return mapOfArguments;
}

/**
* @brief Compresses in-file, saves compressed data to out-file and creates a dictionary.
* @details This function does the following: 
* 1.Creates the relevant dictionary of the file passed through "-i" switch
* 2.Saves created dictionary to the file passed through "-s" switch.
* 3.Compresses the inputed file and saves the data to the file passed through "-o" switch.
* @param fileToTakeFrom Address of the inputed file.
* @param fileToSaveTo Address of the file where data is to be saved.
* @param dictionaryFile Address of the file where dictionary is to be saved
*/
void Compress(const std::string& fileToTakeFrom, const std::string& fileToSaveTo, const std::string& dictionaryFile)
{
	std::map<char, int> characterFrequencyMap = CreateMap(fileToTakeFrom);
	std::vector<std::pair<int, char>> vectorToStoreFrequencyOfCharacters = CreateVector(characterFrequencyMap);
	std::vector<std::pair<char, int>> sorterVectorOfCharsByFrequency = SortVectorMinToMax(vectorToStoreFrequencyOfCharacters);

	HuffNode* pRoot = HuffmanCoding(sorterVectorOfCharsByFrequency);
	std::map<char, std::string> tempDictionary;
	MakeDictionary(pRoot, tempDictionary);
	DeleteHuffEntirely(pRoot);
	SaveDictionary(tempDictionary, dictionaryFile);

	CompressToDiffrentFile(fileToTakeFrom, fileToSaveTo, tempDictionary);
}

/**
* @brief Decompresses in-file to the out-file with use of the in-file's dictionary.
* @details This function takes the inputed file's dictionary and uses it to decompress the inputed files data to output file's addres.
* @param fileToTakeFrom Address of the inputed file.
* @param fileToSaveTo Address of the file where data is to be saved.
* @param dictionaryFile Address of the file where dictionary is located
*/
void Decompress(const std::string& fileToTakeFrom, const std::string& fileToSaveTo, const std::string& dictionaryFile)
{
	std::map<char, std::string> tempDictionary = ReadDictionary(dictionaryFile);
	DecompressToDiffrentFile(fileToTakeFrom, fileToSaveTo, tempDictionary);
}

/**
* @brief Main function of the project, receives both number of arguments and arguments from console.
* @details This function receives arguments from console,
* checks with usage of functions if the correct number of arguments were inputed and if there were relevant switches used.
* It lastly checks whether the file should be compressed of decompressed and calls the appropriate function.
* @param argc Count of arguments.
* @param arg Arguments from console.
* @return Returns 0 if the number of arguments is incorrect, -1 if all switches aren't presents or have arguments, 1 otherwise.
*/
int main(int argc, char** arg)
{
	if (!ControlForNumberOfArguments(argc))
		return 0;
	std::map<std::string, std::string> args = ControlForArguments(argc, arg);
	if (args.empty())
		return -1;
	
	std::string inFile = args["-i"];
	std::string outFile = args["-o"];
	std::string slownikFile = args["-s"];
	if (args["-t"] == "k")
	{
		Compress(inFile, outFile, slownikFile);
		return 1;
	}
	else if (args["-t"] == "d")
	{
		Decompress(inFile, outFile, slownikFile);
		return 1;
	}
}
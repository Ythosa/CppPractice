#include "stdafx.h"
#include "Translator.h"
#include "input_output_utils.h"

void AskForTranslation(CTranslator & translator, const std::string & word)
{
	std::cout << "  There are no translation in this dictionary" << std::endl;
	std::cout << "  Do you want to give it? ";
	std::string agree;
	std::string translation;
	std::cin >> agree;
	if (agree == AGREE_STATMENT)
	{
		std::cout << "Input translation: ";
		std::cin >> translation;
		translator.AddTranslation(word, translation);
	}
}

bool CheckArgumentCount(int argumentCount, std::string programName)
{
	if (argumentCount != 3)
	{
		std::cout << "Invalid argument count" << std::endl;
		std::cout << programName << " <input dictionary> <output dictionary>" << std::endl;
	}
	return argumentCount != 3;
}

bool OpenFile(std::ifstream & input, std::string fileName)
{
	input.open(fileName);
	if (!input.is_open())
	{
		std::cout << "Invalid file name " << fileName << std::endl;
	}
	return input.is_open();
}

bool OpenFile(std::ofstream & output, std::string fileName)
{
	output.open(fileName);
	if (!output.is_open())
	{
		std::cout << "Invalid file name " << fileName << std::endl;
	}
	return output.is_open();
}

void DumpTranslator(const CTranslator & translator, std::ofstream & output)
{
	if (translator.IsModified())
	{
		std::string line;
		std::cout << "Save new dictionary?" << std::endl;
		std::cin >> line;
		if (line == AGREE_STATMENT)
		{
			translator.DumpDictionary(output);
		}
	}
}
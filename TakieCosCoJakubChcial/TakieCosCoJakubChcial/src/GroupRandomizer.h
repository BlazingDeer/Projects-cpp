#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class GroupRandomizer
{
private:
	std::ifstream m_inputFile;
	std::ofstream m_outputFile;
	std::vector<std::string> m_names;
	size_t m_groupSize;


public:
	GroupRandomizer(std::string inputFilename, std::string outputFilename, size_t groupsize);
	void scramble();
	void writedown();


};



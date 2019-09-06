#include "GroupRandomizer.h"


GroupRandomizer::GroupRandomizer(std::string filename, std::string outputFilename, size_t groupsize) :
	m_inputFile(filename),
	m_outputFile(outputFilename, std::ofstream::out | std::ofstream::trunc),
	m_groupSize(groupsize)
{
	if (m_inputFile)
	{
		std::string tempname;
		while (std::getline(m_inputFile, tempname))
		{
			m_names.push_back(tempname);
		}

		scramble();
		writedown();
	}
	else
	{
		std::cout << "\n\nHUJOWA NAZWA PLIKU!"<<std::endl;
		std::cin.get();
		exit(0);
	}


}

void GroupRandomizer::scramble()
{

	const auto begiter = m_names.begin();
	size_t vsize = m_names.size();
	srand(time(NULL));
	if (vsize >= 2)
	{
		for (int i = 0; i < m_names.size(); i++)
		{
			size_t firstElement = rand() % vsize;
			size_t secondElement = rand() % vsize;

			std::iter_swap(begiter + firstElement, begiter + secondElement);

		}
	}
	else
	{
		std::cout << "\n\nKURWA ZA MALO NAZWISK DO LOSOWANIA!" << std::endl;
	}
}

void GroupRandomizer::writedown()
{
	for (int i = 0, k = 0; i < m_names.size(); i++)
	{
		if ((i % m_groupSize) == 0)
		{
			k++;
			std::cout << "\n\nGrupa " << k << ":" << std::endl;
			m_outputFile << "\n\nGrupa " <<k << ":\n";
		}

		std::cout << m_names[i] << "\n";
		m_outputFile << m_names[i] << "\n";

	}
	
}

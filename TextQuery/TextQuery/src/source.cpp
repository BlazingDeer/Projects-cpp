#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <sstream>

#include "Query.h"
#include "OrQuery.h"
#include "AndQuery.h"
#include "NotQuery.h"






std::ostream& print(std::ostream& os, const QueryResult& result)
{
	os << result.m_word << " wystepuje " << result.m_lines->size() << " raz" << (result.m_lines->size() == 1 ? "" : "y") << std::endl;
	for (auto lineNumber : *result.m_lines)
	{
		os << "\t(line " << lineNumber + 1 << ")  " << *(result.m_file->begin() + lineNumber) << std::endl;
	}

	return os;
}


int main()
{
	std::cout << "Wprowadz nazwe pliku do wczytania: ";
	std::string filename;
	std::cin >> filename;
	std::ifstream inputFile(filename);

	TextQuery tq(inputFile);


	while (true)
	{
		std::cout << "Wprowadz wyraz jaki chcesz znalezc albo q zeby wyjsc: ";
		std::string wyraz;
		if (!(std::cin >> wyraz) || wyraz == "q") break;
		print(std::cout, tq.query(wyraz));
	}




	return 0;
}
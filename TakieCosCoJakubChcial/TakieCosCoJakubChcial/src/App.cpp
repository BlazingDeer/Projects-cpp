#include <iostream>
#include "GroupRandomizer.h"
#include <cstdlib>


int main()
{
	std::cout << "Program wczytuje plik z imionami i nazwiskami a nastepnie losuje grupy osob\n\n";
	std::cout << "Podaj nazwe pliku folderze z programem do wczytania: " << std::endl;;
	std::string in, out;
	size_t groupSize = 0;
	std::cin >> in;
	std::cout << "Podaj nazwe pliku do zapisu grup: "<< std::endl;
	std::cin >> out;
	std::cout << "Podaj wielkosc grupy: " << std::endl;
	std::cin >> groupSize;
	GroupRandomizer grupy1(in, out, groupSize);


	std::cin.get();
	std::cin.get();
	return 0;
}
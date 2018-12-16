#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

class GaussElimination
{
private:
	int n;
	std::vector<std::vector<double>> matrix;
public:
	GaussElimination(int c) : matrix(c, std::vector<double>(c)), n(c)
	{
		EnterMatrix();
		ShowMatrix();
	}


	void EnterMatrix()
	{
		int count = 0;
		for (auto &i : matrix)
		{
			std::cout << "\nwprowadz elementy " << count << " wiersza:\n";
			
			for (auto &k : i)
			{
				std::cin >> k;
			}
			++count;
		}
	}

	void ShowMatrix()
	{
		for (auto &i : matrix)
		{
			int count = 0;
			std::cout << "\n| ";
			for (auto &k : i)
			{
				std::cout << std::setw(8) << std::setprecision(4) << k;
			}
			std::cout << "        |";
			++count;
		}
		std::cout << "\n";
	}
};


int main()
{
	int n;
	std::cout << "\nWprowadz stopien macierzy: n= ";
	std::cin >> n;
	GaussElimination matrix(n);



	std::cout << "\n\n";
	system("pause");
	return 0;
}
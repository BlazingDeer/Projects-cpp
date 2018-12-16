#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath>

class GaussElimination
{
private:
	int n;
	double **matrix;
	double  *matrixValues;
	double *BasicGaussWyniki;
public:


	GaussElimination()
	{
		CreateMatrix();
		EnterMatrix();
		ShowMatrix(matrix,matrixValues);
	}



	~GaussElimination()
	{
		
			for (int i = 0; i < n; i++)
			{
				free(matrix[i]);
			}
		free(matrix);
	}


	void CreateMatrix()
	{
		std::cout << "\nWprowadz stopien macierzy: n= ";
		std::cin >> n;
		matrix = (double**)calloc(n, sizeof(double*));
		for (int i = 0; i < n; ++i)
		{
			matrix[i] = (double*)calloc(n, sizeof(double));
		}
		matrixValues = (double *)(calloc(n, sizeof(double)));
		BasicGaussWyniki = (double *)(calloc(n, sizeof(double)));

	}



	void EnterMatrix()
	{
		int count = 0;
		for (int i = 0; i < n; ++i)
		{
			std::cout << "\nwprowadz elementy " << count << " wiersza:\n";
			
			for (int k=0;k<n;k++)
			{
				std::cin >> matrix[i][k];
			}
			++count;
		}

		std::cout << "\nwprowadz macierz wynikow:\n" ;
		for (int i=0;i<n;i++)
		{
			
			std::cin >> matrixValues[i];
			
			
		}

	}

	void ShowMatrix(double** toshow, double* values)
	{
		
		for (int i=0;i<n;i++)
		{
			
			std::cout << "\n| ";
			for (int k=0; k<n; k++)
			{
				std::cout << std::setw(8) << std::setprecision(4) << toshow[i][k];
			}
			std::cout << "        |" << "|"<<std::setw(8) << values[i];
			
		}
		std::cout << "\n";
	}





	void BasicGaussElimination()
	{
		double** BasicMatrix = matrix;
		double* BasicMatrixValues = matrixValues;
		for (int i=0; i<n-1;i++)
		{
			if (BasicMatrix[i][i] == 0)
			{
				std::cout << "\nBlad wartosc po przekatnej rowna 0!";
				break;

			}

			for (int wdol = i+1; wdol < n; wdol++)
			{
				double temp = BasicMatrix[wdol][i] / BasicMatrix[i][i];
				
				for (int wbok = i ; wbok < n; wbok++)
				{
					BasicMatrix[wdol][wbok] -= BasicMatrix[i][wbok] * temp;

					if (abs(BasicMatrix[wdol][wbok]) <= 1e-12) BasicMatrix[wdol][wbok] = 0;
				
				}

				BasicMatrixValues[wdol] -= temp * BasicMatrixValues[i];



			}





		
		}
		std::cout << "\n\nPodstawowy Gauss\n";
		ShowMatrix(BasicMatrix, BasicMatrixValues);

		BasicGaussWyniki[n - 1] = BasicMatrixValues[n - 1] / BasicMatrix[n - 1][n - 1];
		for (int i = n - 2; i >= 0; i--)
		{
			for (int k = n-1; k > i; k--)
			{
				BasicMatrixValues[i] -= BasicMatrix[i][k] * BasicGaussWyniki[k];
				BasicMatrix[k] = 0;
			}
			BasicGaussWyniki[i]= BasicMatrixValues[i] / BasicMatrix[i][i];
		}

		for (int i = 0; i < n; i++)
		{
			std::cout << "\nX" << i << "=" << BasicGaussWyniki[i];
		}
	}
};


int main()
{
	GaussElimination matrix;
	matrix.BasicGaussElimination();




	std::cout << "\n\n";
	system("pause");
	return 0;
}
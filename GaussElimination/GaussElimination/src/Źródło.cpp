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
	double *IntermediateGaussWyniki;
public:


	GaussElimination()
	{
		CreateFirst();
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
		free(matrixValues);
		free(BasicGaussWyniki);
		free(IntermediateGaussWyniki);
	}


	void CreateFirst()
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
		IntermediateGaussWyniki = (double *)(calloc(n, sizeof(double)));
	}

	void FreeMatrix(double **TempMatrix, double *TempMatrixValues)
	{
		for (int i = 0; i < n; i++)
			{
				free(TempMatrix[i]);
			}
		free(TempMatrix);
		free(TempMatrixValues);
	}

	void CreateMatrix(double**& NewMatrix, double*& NewValues)
	{
		NewMatrix = (double**)calloc(n, sizeof(double*));
		for (int i = 0; i < n; ++i)
		{
			NewMatrix[i] = (double*)calloc(n, sizeof(double));
		}
		NewValues = (double *)(calloc(n, sizeof(double)));

	}

	void CopyMatrix(double **NewMatrix, double *NewValues)
	{
		

		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				NewMatrix[i][k] = matrix[i][k];
			}
			NewValues[i] = matrixValues[i];
		}
	}

	void MaxColumnSwap(double **TempMatrix, double *TempMatrixValues, int przekatna)
	{
		double MaxElement= TempMatrix[przekatna][przekatna];
		int MaxElementVerticalIndex=przekatna;

		for (int i = przekatna; i < n; i++)
		{
			if (abs(TempMatrix[i][przekatna]) > MaxElement)
			{
				MaxElement = TempMatrix[i][przekatna];
				MaxElementVerticalIndex = i;
			}
		}

		for (int i = 0; i < n; i++)
		{
			double CopyColumn;
			CopyColumn = TempMatrix[przekatna][i];
			TempMatrix[przekatna][i] = TempMatrix[MaxElementVerticalIndex][i];
			TempMatrix[MaxElementVerticalIndex][i] = CopyColumn;

			CopyColumn = TempMatrixValues[przekatna];
			TempMatrixValues[przekatna] = TempMatrixValues[MaxElementVerticalIndex];
			TempMatrixValues[MaxElementVerticalIndex] = CopyColumn;
		}



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
		std::cout << "\n\nPodstawowy Gauss(Bez Wyboru)\n";
		double** BasicMatrix = nullptr;
		double* BasicMatrixValues = nullptr;
		bool EndV = false;
		CreateMatrix(BasicMatrix, BasicMatrixValues);
		CopyMatrix(BasicMatrix, BasicMatrixValues); 
		for (int i=0; i<n-1;i++)
		{
			if (BasicMatrix[i][i] == 0)
			{
				std::cout << "\nBlad wartosc po przekatnej rowna 0!";
				EndV = true;
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
		if (EndV)
		{
			FreeMatrix(BasicMatrix, BasicMatrixValues);
			return;
		}
		
		ShowMatrix(BasicMatrix, BasicMatrixValues);
		if(BasicMatrix[n - 1][n - 1]) BasicGaussWyniki[n - 1] = BasicMatrixValues[n - 1] / BasicMatrix[n - 1][n - 1];
		else
		{
			std::cout << "\nBlad! Macierz ma nieskonczenie wiele rozwiazan BasicMatrixValues[n - 1] / BasicMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(BasicMatrix, BasicMatrixValues);
			return;
		}
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
		FreeMatrix(BasicMatrix, BasicMatrixValues);
	}

	void IntermediateGauss()
	{
		std::cout << "\n\nGauss z wyborem Maksymalnego elementu w kolumnie";
		double **IntermediateMatrix = nullptr;
		double *IntermediateMatrixValues = nullptr;
		CreateMatrix(IntermediateMatrix, IntermediateMatrixValues);

		bool EndV = false;
		CopyMatrix(IntermediateMatrix, IntermediateMatrixValues);
		for (int i = 0; i < n - 1; i++)
		{
			MaxColumnSwap(IntermediateMatrix, IntermediateMatrixValues,i);
			if (IntermediateMatrix[i][i] == 0)
			{
				std::cout << "\nBlad wartosc po przekatnej rowna 0!";
				EndV = true;
				break;

			}

			for (int wdol = i + 1; wdol < n; wdol++)
			{
				double temp = IntermediateMatrix[wdol][i] / IntermediateMatrix[i][i];

				for (int wbok = i; wbok < n; wbok++)
				{
					IntermediateMatrix[wdol][wbok] -= IntermediateMatrix[i][wbok] * temp;

					if (abs(IntermediateMatrix[wdol][wbok]) <= 1e-12) IntermediateMatrix[wdol][wbok] = 0;

				}

				IntermediateMatrixValues[wdol] -= temp * IntermediateMatrixValues[i];

			}
		}
		if (EndV)
		{
			FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
			return;
		}
		
		ShowMatrix(IntermediateMatrix, IntermediateMatrixValues);
		if (IntermediateMatrix[n - 1][n - 1]) BasicGaussWyniki[n - 1] = IntermediateMatrixValues[n - 1] / IntermediateMatrix[n - 1][n - 1];
		else
		{
			std::cout << "\nBlad! Macierz ma nieskonczenie wiele rozwiazan BasicMatrixValues[n - 1] / BasicMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
			return;
		}
		for (int i = n - 2; i >= 0; i--)
		{
			for (int k = n - 1; k > i; k--)
			{
				IntermediateMatrixValues[i] -= IntermediateMatrix[i][k] * BasicGaussWyniki[k];
				IntermediateMatrix[k] = 0;
			}
			IntermediateGaussWyniki[i] = IntermediateMatrixValues[i] / IntermediateMatrix[i][i];
		}

		for (int i = 0; i < n; i++)
		{
			std::cout << "\nX" << i << "=" << BasicGaussWyniki[i];
		}
		FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
	}
	
};


int main()
{
	GaussElimination matrix;
	matrix.BasicGaussElimination();
	matrix.IntermediateGauss();




	std::cout << "\n\n";
	system("pause");
	return 0;
}
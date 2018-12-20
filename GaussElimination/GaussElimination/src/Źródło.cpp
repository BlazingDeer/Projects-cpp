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
	double *AdvancedGaussWyniki;
public:

	//ZESTAWY TESTOWE
	//Oznaczone
	std::vector<std::vector<double>> zt1{ {0,1,2,3}, {1 ,0 ,1 ,2}, {1,2,3,4}, {0,1, 3, 2} };
	std::vector<double> zt1wyniki{ 8,4,10,7 };

	std::vector<std::vector<double>> zt2{ {2, 4 ,2 ,0}, {1, 0, -1, 1}, {0,1,3,-1},{2,1,2,1} };
	std::vector<double> zt2wyniki{ 4,2,0,6 };

	std::vector<std::vector<double>> zt3{ {6,-2,2,4},{12,-8,6,10},{3,-13,9,3},{-6,4,1,-18} };
	std::vector<double> zt3wyniki{ 12,34,27,-38 };

	std::vector<std::vector<double>> zt4{ {1,1,0,1,-3},{2,0,-1,0,-2},{1,-1,-2,1,-2},{2,0,1,0,1},{-3,-1,1,2,2} };
	std::vector<double> zt4wyniki{ 1,1,1,-1,1 };
	//Nieoznaczone
	std::vector<std::vector<double>> zt5{ {1,3,2},{2,-1,1},{3,2,3} };
	std::vector<double> zt5wyniki{ 0,1,1 };
	
	std::vector<std::vector<double>> zt6{ {3,-1,2},{1,2,-1},{4,1,1} };
	std::vector<double> zt6wyniki{ 1,2,3 };
	//Sprzeczne
	std::vector<std::vector<double>> zt7{ {1,2,3,1},{1,1,1,1},{2,-4,-1,2},{3,6,10,3} };
	std::vector<double> zt7wyniki{ 1,0,2,2 };

	std::vector<std::vector<double>> zt8{ {2,4,0,-6}, {1,-5,3,-1}, {3,2,-1,2}, {6,1,2,-5} };
	std::vector<double> zt8wyniki{ 1,-3,9,22 };




	GaussElimination(int wybor)
	{
		switch (wybor)
		{
		case 1:
			n = 0;
			CreateFirst();
			EnterMatrix();
			ShowMatrix(matrix, matrixValues);
			break;
		case 2:
			Choose();
			break;
		default:
			std::cout << "\nBlad!\n";
			system("pause");
			exit(0);
			

		}
	}

	GaussElimination()
	{
		n = 0;
		CreateFirst();
		EnterMatrix();
		ShowMatrix(matrix, matrixValues);

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
		free(AdvancedGaussWyniki);
	}

	void Choose()
	{
		system("cls");
		std::cout << "\n\nWybierz zestaw:\n";
		std::cout << "OZNACZONE\n";
		std::cout << "Zestaw 1\n";
		VectorShowMatrix(zt1, zt1wyniki);
		
		std::cout << "\n\nZestaw 2\n";

		VectorShowMatrix(zt2, zt2wyniki);


		std::cout << "\n\nZestaw 3\n";
		VectorShowMatrix(zt3, zt3wyniki);
		std::cout << "\n\nZestaw 4\n";
		VectorShowMatrix(zt4, zt4wyniki);
		std::cout << "\nNIEOZNACZONE\n";
		std::cout << "\n\nZestaw 5\n";
		VectorShowMatrix(zt5, zt5wyniki);
		std::cout << "\n\nZestaw 6\n";
		VectorShowMatrix(zt6, zt6wyniki);
		std::cout << "\nSPRZECZNE\n";
		std::cout << "\n\nZestaw 7\n";
		VectorShowMatrix(zt7, zt7wyniki);
		std::cout << "\n\nZestaw 8\n";
		VectorShowMatrix(zt8, zt8wyniki);
		std::cout << "\nWybor:";
		int i;
		std::cin >> i;
		switch (i)
		{
		case 1:
			n = 4;
			CreateFirst();
			CopySet(zt1, zt1wyniki);
			break;
		case 2:
			n = 4;
			CreateFirst();
			CopySet(zt2, zt2wyniki);
			break;
		case 3:
			n = 4;
			CreateFirst();
			CopySet(zt3, zt3wyniki);
			break;
		case 4:
			n = 5;
			CreateFirst();
			CopySet(zt4, zt4wyniki);
			break;
		case 5:
			n = 3;
			CreateFirst();
			CopySet(zt5, zt5wyniki);
			break;
		case 6:
			n = 3;
			CreateFirst();
			CopySet(zt6, zt6wyniki);
			break;
		case 7:
			n = 4;
			CreateFirst();
			CopySet(zt7, zt7wyniki);
			break;
		case 8:
			n = 4;
			CreateFirst();
			CopySet(zt8, zt8wyniki);
			break;
		default:
			std::cout << "Blad! Wybrano zly zestaw";
			system("pause");
			exit(0);
		}
	}

	void CopySet(std::vector<std::vector<double>> Set, std::vector<double> SetValues)
	{
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				matrix[i][k] = Set[i][k];
			}
			matrixValues[i] = SetValues[i];
		}

	}


	void CreateFirst()
	{

		if (n == 0)
		{
			std::cout << "\nWprowadz stopien macierzy: n= ";
			std::cin >> n;
		}
		matrix = (double**)calloc(n, sizeof(double*));
		for (int i = 0; i < n; ++i)
		{
			matrix[i] = (double*)calloc(n, sizeof(double));
		}
		matrixValues = (double *)(calloc(n, sizeof(double)));
		BasicGaussWyniki = (double *)(calloc(n, sizeof(double)));
		IntermediateGaussWyniki = (double *)(calloc(n, sizeof(double)));
		AdvancedGaussWyniki = (double *)(calloc(n, sizeof(double)));
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

	void CopyMatrix(double**& NewMatrix, double*& NewValues)
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

	void MaxColumnSwap(double**& TempMatrix, double*& TempMatrixValues, int przekatna)
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
			double CopyLine;
			CopyLine = TempMatrix[przekatna][i];
			TempMatrix[przekatna][i] = TempMatrix[MaxElementVerticalIndex][i];
			TempMatrix[MaxElementVerticalIndex][i] = CopyLine;

		}

		double CopyValue;
		CopyValue = TempMatrixValues[przekatna];
		TempMatrixValues[przekatna] = TempMatrixValues[MaxElementVerticalIndex];
		TempMatrixValues[MaxElementVerticalIndex] = CopyValue;



	}

	void MaxMatrixSwap(double**& TempMatrix, double*& TempMatrixValues, int*& XOrder, int przekatna)
	{
		double MaxElement = TempMatrix[przekatna][przekatna];
		int MaxElementVerticalIndex = przekatna;
		int MaxElementHorizontalIndex = przekatna;

		for (int i = przekatna; i < n; i++)
		{
			for (int k = przekatna; k < n; k++)
			{
				if (abs(TempMatrix[i][k]) > MaxElement)
				{
					MaxElement = TempMatrix[i][k];
					MaxElementVerticalIndex = i;
					MaxElementHorizontalIndex = k;
				}
			}
			
		}

		for (int i = 0; i < n; i++) //Zamiana Wierszy
		{
			double CopyLine;
			CopyLine = TempMatrix[przekatna][i];
			TempMatrix[przekatna][i] = TempMatrix[MaxElementVerticalIndex][i];
			TempMatrix[MaxElementVerticalIndex][i] = CopyLine;
		}
		double CopyValue;
		CopyValue = TempMatrixValues[przekatna];
		TempMatrixValues[przekatna] = TempMatrixValues[MaxElementVerticalIndex];
		TempMatrixValues[MaxElementVerticalIndex] = CopyValue;

		for (int i = 0; i < n; i++) //Zamiana Kolumn
		{
			double CopyColumn;
			CopyColumn = TempMatrix[i][przekatna];
			TempMatrix[i][przekatna] = TempMatrix[i][MaxElementHorizontalIndex];
			TempMatrix[i][MaxElementHorizontalIndex] = CopyColumn;

		}

		int temp;
		temp = XOrder[przekatna];
		XOrder[przekatna] = XOrder[MaxElementHorizontalIndex];
		XOrder[MaxElementHorizontalIndex] = temp;


	}



	void EnterMatrix()
	{
		std::cout << "\n\nUWAGA! Najpierw wprowadzamy wiersze macierzy ze zmiennymi(X) a na koniec oddzielnie macierz Y(wyrazow wolnych)\nPrzyklad: X1 + X2 + X3 = Y\n";
		int count = 0;
		for (int i = 0; i < n; ++i)
		{
			std::cout << "\nwprowadz elementy(X) " << count << " wiersza:\n";
			
			for (int k=0;k<n;k++)
			{
				std::cin >> matrix[i][k];
			}
			++count;
		}

		std::cout << "\nwprowadz macierz Y(wyrazow wolnych):\n" ;
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

	void VectorShowMatrix(std::vector<std::vector<double>> toshow, std::vector<double> values)
	{

		for (int i = 0; i < values.size(); i++)
		{

			std::cout << "\n| ";
			for (int k = 0; k < values.size(); k++)
			{
				std::cout << std::setw(8) << std::setprecision(4) << toshow[i][k];
			}
			std::cout << "        |" << "|" << std::setw(8) << values[i];

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
		

		if (BasicMatrix[n - 1][n - 1])
		{
			BasicGaussWyniki[n - 1] = BasicMatrixValues[n - 1] / BasicMatrix[n - 1][n - 1];
			if (abs(BasicGaussWyniki[n - 1]) < 1e-12) BasicGaussWyniki[n - 1] = 0;
		}
		else if (BasicMatrixValues[n - 1] == 0)
		{
			std::cout << "\n\nRozwiazan jest nieskonczenie wiele.\n BasicMatrixValues[n - 1]==0 AND BasicMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(BasicMatrix, BasicMatrixValues);
			
			return;
		}
		else if (BasicMatrixValues[n - 1] != 0)
		{
			std::cout << "\n\nUklad sprzeczny!\n BasicMatrixValues[n - 1]!=0  AND BasicMatrix[n - 1][n - 1]==0\n";
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
			if (BasicMatrix[i][i] == 0)
			{
				std::cout << "\nBlad! Rozwiazania sa sprzeczne lub jest ich nieskonczenie wiele.\n";
				FreeMatrix(BasicMatrix, BasicMatrixValues);
				return;
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
		std::cout << "\n\n\nGauss z wyborem Maksymalnego elementu w kolumnie";
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
		if (IntermediateMatrix[n - 1][n - 1])
		{
			IntermediateGaussWyniki[n - 1] = IntermediateMatrixValues[n - 1] / IntermediateMatrix[n - 1][n - 1];
			if (abs(IntermediateGaussWyniki[n - 1]) < 1e-12) IntermediateGaussWyniki[n - 1] = 0;
		}
		else if(IntermediateMatrixValues[n - 1]==0)
		{
			std::cout << "\n\nRozwiazan jest nieskonczenie wiele.\n IntermediateMatrixValues[n - 1]==0  AND  IntermediateMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
			return;
		}
		else if (IntermediateMatrixValues[n - 1] != 0)
		{
			std::cout << "\n\nUklad sprzeczny!\n IntermediateMatrixValues[n - 1]!=0  AND  IntermediateMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
			return;
		}

		for (int i = n - 2; i >= 0; i--)
		{
			for (int k = n - 1; k > i; k--)
			{
				IntermediateMatrixValues[i] -= IntermediateMatrix[i][k] * IntermediateGaussWyniki[k];
				IntermediateMatrix[k] = 0;
			}
			if (IntermediateMatrix[i][i] == 0)
			{
				std::cout << "\nBlad! Rozwiazania sa sprzeczne lub jest ich nieskonczenie wiele.\n";
				FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
				return;
			}
			IntermediateGaussWyniki[i] = IntermediateMatrixValues[i] / IntermediateMatrix[i][i];
		}

		for (int i = 0; i < n; i++)
		{
			std::cout << "\nX" << i << "=" << IntermediateGaussWyniki[i];
		}
		FreeMatrix(IntermediateMatrix, IntermediateMatrixValues);
	}


	void AdvancedGauss()
	{
		std::cout << "\n\n\nGauss z PELNYM wyborem Maksymalnego elementu";
		double **AdvancedMatrix = nullptr;
		double *AdvancedMatrixValues = nullptr;
		int* XOrder = (int*)calloc(n, sizeof(int));

		for (int i = 0; i < n; i++)
		{
			XOrder[i] = i;
		}

		CreateMatrix(AdvancedMatrix, AdvancedMatrixValues);

		bool EndV = false;
		CopyMatrix(AdvancedMatrix, AdvancedMatrixValues);
		for (int i = 0; i < n - 1; i++)
		{
			MaxMatrixSwap(AdvancedMatrix, AdvancedMatrixValues,XOrder, i);
			if (AdvancedMatrix[i][i] == 0)
			{
				std::cout << "\nBlad wartosc po przekatnej rowna 0!";
				EndV = true;
				break;

			}

			for (int wdol = i + 1; wdol < n; wdol++)
			{
				double temp = AdvancedMatrix[wdol][i] / AdvancedMatrix[i][i];

				for (int wbok = i; wbok < n; wbok++)
				{
					AdvancedMatrix[wdol][wbok] -= AdvancedMatrix[i][wbok] * temp;

					if (abs(AdvancedMatrix[wdol][wbok]) <= 1e-12) AdvancedMatrix[wdol][wbok] = 0;

				}

				AdvancedMatrixValues[wdol] -= temp * AdvancedMatrixValues[i];

			}
		}
		if (EndV)
		{
			FreeMatrix(AdvancedMatrix, AdvancedMatrixValues);
			free(XOrder);
			return;
		}

		ShowMatrix(AdvancedMatrix, AdvancedMatrixValues);
		if (AdvancedMatrix[n - 1][n - 1])
		{
			AdvancedGaussWyniki[n - 1] = AdvancedMatrixValues[n - 1] / AdvancedMatrix[n - 1][n - 1];
			if (abs(AdvancedGaussWyniki[n - 1]) < 1e-12) AdvancedGaussWyniki[n - 1] = 0;
		}
		else if(AdvancedMatrixValues[n - 1]==0)
		{
			std::cout << "\n\nRozwiazan jest nieskonczenie wiele.\n AdvancedMatrixValues[n - 1]==0 AND AdvancedMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(AdvancedMatrix, AdvancedMatrixValues);
			free(XOrder);
			return;
		}
		else if (AdvancedMatrixValues[n - 1] != 0)
		{
			std::cout << "\n\nUklad sprzeczny!\n AdvancedMatrixValues[n - 1]!=0  AND AdvancedMatrix[n - 1][n - 1]==0\n";
			FreeMatrix(AdvancedMatrix, AdvancedMatrixValues);
			free(XOrder);
			return;
		}

		
		if (abs(AdvancedGaussWyniki[n - 1]) < 1e-12) AdvancedGaussWyniki[n - 1] = 0;
		for (int i = n - 2; i >= 0; i--)
		{
			for (int k = n - 1; k > i; k--)
			{
				AdvancedMatrixValues[i] -= AdvancedMatrix[i][k] * AdvancedGaussWyniki[k];
				AdvancedMatrix[k] = 0;
			}
			if (AdvancedMatrix[i][i] == 0)
			{
				std::cout << "\nBlad! Rozwiazania sa sprzeczne lub jest ich nieskonczenie wiele.\n";
				FreeMatrix(AdvancedMatrix, AdvancedMatrixValues);
				free(XOrder);
				return;
			}
			AdvancedGaussWyniki[i] = AdvancedMatrixValues[i] / AdvancedMatrix[i][i];
			if (abs(AdvancedGaussWyniki[i]) < 1e-12) AdvancedGaussWyniki[i] = 0;
		}

		std::cout << "\nWYPISUJE WARTOSCI POSZCZEGOLNYCH ZMIENNYCH!\nUWAGA NA ZMIANE KOLEJNOSCI Xn!!\n";
		for (int i = 0; i < n; i++)
		{
			std::cout << "\nX" << XOrder[i] << "=" << AdvancedGaussWyniki[i];
		}
		FreeMatrix(AdvancedMatrix, AdvancedMatrixValues);
		free(XOrder);
	}
	
};


int main()
{
	std::cout << "Program rozwiazuje rownania Metoda Eliminacji Gaussa.\n";
	std::cout << "Wybierz metode wprowadzania macierzy:\n1.Wlasna macierz\n2.Zestaw testowy\nWybor:";
	int wybor;
	std::cin >> wybor;
	if ((wybor != 1) && (wybor != 2))
	{
		std::cout << "Blad! Nie dokonano poprawnego wyboru.\n";
		system("pause");
		exit(0);
	}
	GaussElimination matrix(wybor);
	std::cout << "1.Podstawowy Gauss (bez wyboru)\n2.Gauss z wyborem maksymalnego elementu w kolumnie\n3.Gauss z Pelnym wyborem maksymalnego elementu\n4.Wszystkie\nWybor: ";
	std::cin >> wybor;
	system("cls");
	switch (wybor)
	{
	case 1:
		
		matrix.BasicGaussElimination();
		break;
	case 2:
		matrix.IntermediateGauss();
		break;
	case 3:
		matrix.AdvancedGauss();
		break;
	case 4:
		matrix.BasicGaussElimination();
		matrix.IntermediateGauss();
		matrix.AdvancedGauss();
		break;
	default:
		std::cout << "\nNie dokonano poprawnego wyboru.\n";

	}
	
	std::cout << "\n\n";
	system("pause");
	return 0;
}
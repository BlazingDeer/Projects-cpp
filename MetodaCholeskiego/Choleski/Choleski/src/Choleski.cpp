#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath>




class Choleski
{
private:
	int n;
	double** matrix;
	double* matrixValues;
	double* CholeskiWyniki;

public:


	//Z pdf
	std::vector<std::vector<double>> zt1{ {1,-2,3,1},{-2,5,-8,1},{3,-8,17,-7},{1,1,-7,18} };
	std::vector<double> zt1wyniki{ 1,-1,3,-4};






	Choleski(int wybor)
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

	Choleski()
	{
		n = 0;
		CreateFirst();
		EnterMatrix();
		ShowMatrix(matrix, matrixValues);

	}



	~Choleski()
	{

		for (int i = 0; i < n; i++)
		{
			free(matrix[i]);
		}
		free(matrix);
		free(matrixValues);
		free(CholeskiWyniki);
	}

	void Choose()
	{
		system("cls");
		std::cout << "\n\nWybierz zestaw:\n";
	
		std::cout << "\nPRZYKLAD Z PDF\n";
		std::cout << "\n\nZestaw 1\n";
		VectorShowMatrix(zt1, zt1wyniki);
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
		default:
			std::cout << "Blad! Wybrano zly zestaw";
			system("pause");
			exit(0);
		}
	}

	void CopySet(std::vector<std::vector<double>>& Set, std::vector<double>& SetValues)
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
		CholeskiWyniki = (double *)(calloc(n, sizeof(double)));

	}
	void FreeMatrix(double** TempMatrix)
	{
		for (int i = 0; i < n; i++)
		{
			free(TempMatrix[i]);
		}
		free(TempMatrix);
	}
	void FreeMatrixAndValues(double **TempMatrix, double *TempMatrixValues)
	{
		FreeMatrix(TempMatrix);
		free(TempMatrixValues);
	}

	void CreateMatrix(double**& NewMatrix)
	{
		NewMatrix = (double**)calloc(n, sizeof(double*));
		for (int i = 0; i < n; ++i)
		{
			NewMatrix[i] = (double*)calloc(n, sizeof(double));
		}
	}
	void CreateMatrixAndValues(double**& NewMatrix, double*& NewValues)
	{
		CreateMatrix(NewMatrix);
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

	

	void EnterMatrix()
	{
		std::cout << "\n\nUWAGA! Najpierw wprowadzamy wiersze macierzy ze zmiennymi(X) a na koniec oddzielnie macierz Y(wyrazow wolnych)\nPrzyklad: X1 + X2 + X3 = Y\n";
		int count = 0;
		for (int i = 0; i < n; ++i)
		{
			std::cout << "\nwprowadz elementy(X) " << count << " wiersza:\n";

			for (int k = 0; k < n; k++)
			{
				std::cin >> matrix[i][k];
			}
			++count;
		}

		std::cout << "\nwprowadz macierz Y(wyrazow wolnych):\n";
		for (int i = 0; i < n; i++)
		{

			std::cin >> matrixValues[i];


		}

	}

	void ShowMatrix(double** toshow, double* values)
	{

		for (int i = 0; i < n; i++)
		{

			std::cout << "\n| ";
			for (int k = 0; k < n; k++)
			{
				std::cout << std::setw(8) << std::setprecision(4) << toshow[i][k];
			}
			std::cout << "        |" << "|" << std::setw(8) << values[i];

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




	void MatrixTranspose(double**& ToTranspose)
	{
		double** CopyTranspose = nullptr;
		CreateMatrix(CopyTranspose);
		for(int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				CopyTranspose[i][k] = ToTranspose[i][k];
			}
		}

		for(int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				ToTranspose[i][k] = CopyTranspose[k][i];
			}
		}
		FreeMatrix(CopyTranspose);

	}

	bool MacierzDT(int wymiar, double** AMatrix, double**& LMatrix)
	{
		bool EndV = false;
		
		for (int i = 0; i < wymiar; i++)
		{
			if (AMatrix[i][i] == 0)
			{
				std::cout << "\nBlad wartosc po przekatnej rowna 0!";
				EndV = true;
				break;

			}
			//lii (lss)
			LMatrix[i][i] = AMatrix[i][i];
			for (int k = 0; k <= i - 1; k++)
			{
				LMatrix[i][i] -= LMatrix[i][k] * LMatrix[i][k];
			}

			if (LMatrix[i][i] < 0)
			{
				std::cout << "\nBlad Nie mozna policzyc LMatrix[" << i << "][" << i << "] ! Wartosc pod pierwiastkiem < 0!!\n";
				;
				EndV = true;
				break;

			}
			LMatrix[i][i] = sqrt(LMatrix[i][i]);

			//lki (lis)

			for (int k = i + 1; k < wymiar; k++)
			{
				LMatrix[k][i] = AMatrix[k][i];
				for (int j = 0; j <= i - 1; j++)
				{
					LMatrix[k][i] -= LMatrix[k][j] * LMatrix[i][j];
				}
				LMatrix[k][i] /= LMatrix[i][i];
			}


		}
		
		return EndV;

	}

	bool RozwiazanieDT(int wymiar, double** LMatrix, double* B, double*& LMatrixValues)
	{
		bool EndV = false;


		for (int i = 0; i < wymiar; i++)
		{
			LMatrixValues[i] = B[i];
		}



		if (LMatrix[0][0])
		{
			LMatrixValues[0] = LMatrixValues[0] / LMatrix[0][0];
			if (abs(LMatrixValues[0]) < 1e-12) LMatrixValues[0] = 0;
		}
		else if (LMatrixValues[0] == 0)
		{
			std::cout << "\n\nRozwiazan jest nieskonczenie wiele.\n (Y)LMatrixValues[0]==0 AND LMatrix[0][0]==0\n";
			
			EndV = true;
			return EndV;
		}
		else if (LMatrixValues[0] != 0)
		{
			std::cout << "\n\nUklad sprzeczny!\n (Y)LMatrixValues[0]!=0  AND LMatrix[0][0]==0\n";
			EndV = true;
			return EndV;
		}
		for (int i = 1; i < wymiar; i++)
		{
			for (int k = 0; k < i; k++)
			{
				LMatrixValues[i] -= LMatrix[i][k] * LMatrixValues[k];
			}
			if (LMatrix[i][i] == 0)
			{
				std::cout << "\nBlad! Rozwiazania sa sprzeczne lub jest ich nieskonczenie wiele.\n";
				EndV = true;
				return EndV;
			}
			LMatrixValues[i] = LMatrixValues[i] / LMatrix[i][i];
			if (abs(LMatrixValues[i]) < 1e-12) LMatrixValues[i] = 0;
		}

		for (int i = 0; i < wymiar; i++)
		{
			std::cout << "\nY" << i << "=" << LMatrixValues[i];
		}
		std::cout << "\n\n";


		return EndV;
	}



	bool RozwiazanieGT(int wymiar, double** LMatrix, double* Y, double*& LMatrixValues)
	{
		bool EndV = false;
		if (Y)
		{
			for (int i = 0; i < wymiar; i++)
			{
				LMatrixValues[i] = Y[i];
			}
		}



		if (LMatrix[wymiar - 1][wymiar - 1])
		{
			LMatrixValues[wymiar - 1] = LMatrixValues[wymiar - 1] / LMatrix[wymiar - 1][wymiar - 1];
			if (abs(LMatrixValues[wymiar - 1]) < 1e-12) LMatrixValues[wymiar - 1] = 0;
		}
		else if (LMatrixValues[wymiar - 1] == 0)
		{
			std::cout << "\n\nRozwiazan jest nieskonczenie wiele.\n (X)LMatrixValues[wymiar-1]==0 AND LMatrix[wymiar - 1][wymiar - 1]==0\n";
			EndV = true;
			return EndV;
		}
		else if (LMatrixValues[wymiar - 1] != 0)
		{
			std::cout << "\n\nUklad sprzeczny!\n (X)LMatrixValues[wymiar - 1]!=0  AND LMatrix[wymiar - 1][wymiar - 1]==0\n";
			EndV = true;
			return EndV;
		}
		for (int i = wymiar - 2; i >= 0; i--)
		{
			for (int k = wymiar - 1; k > i; k--)
			{
				LMatrixValues[i] -= LMatrix[i][k] * LMatrixValues[k];
			}
			if (LMatrix[i][i] == 0)
			{
				std::cout << "\nBlad! Rozwiazania sa sprzeczne lub jest ich nieskonczenie wiele.\n";
				EndV = true;
				return EndV;
			}
			LMatrixValues[i] = LMatrixValues[i] / LMatrix[i][i];
			if (abs(LMatrixValues[i]) < 1e-12) LMatrixValues[i] = 0;
		}

		for (int i = 0; i < wymiar; i++)
		{
			std::cout << "\nX" << i << "=" << LMatrixValues[i];
		}


		return EndV;
	}

	void Calc()
	{
		std::cout << "\n\nCholeski)\n";
		double** LMatrix = nullptr;
		double* LMatrixValues = nullptr;
		bool EndV = false;
		CreateMatrixAndValues(LMatrix, LMatrixValues);

		
	

		EndV = MacierzDT(n, matrix, LMatrix);
		if (EndV)
		{
			FreeMatrixAndValues(LMatrix, LMatrixValues);
			return;
		}

		
		EndV=RozwiazanieDT(n, LMatrix, matrixValues, LMatrixValues);
		if (EndV)
		{
			FreeMatrixAndValues(LMatrix, LMatrixValues);
			return;
		}

		MatrixTranspose(LMatrix);


		EndV=RozwiazanieGT(n, LMatrix, nullptr, LMatrixValues);
		if (EndV)
		{
			FreeMatrixAndValues(LMatrix, LMatrixValues);
			return;
		}


		FreeMatrixAndValues(LMatrix, LMatrixValues);

	}
	


};



int main()
{
	std::cout << "Program rozwiazuje rownania przy pomocy rozkladu Choleskiego.\n";
	std::cout << "Wybierz metode wprowadzania macierzy:\n1.Wlasna macierz\n2.Zestaw testowy\nWybor:";
	int wybor;
	std::cin >> wybor;
	if ((wybor != 1) && (wybor != 2))
	{
		std::cout << "Blad! Nie dokonano poprawnego wyboru.\n";
		system("pause");
		exit(0);
	}
	Choleski matrix(wybor);
	matrix.Calc();



	std::cout << "\n\n";
	system("pause");
	return 0;

}

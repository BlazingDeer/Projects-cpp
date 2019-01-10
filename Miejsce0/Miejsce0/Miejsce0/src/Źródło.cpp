#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

#define K_MAX 40

double func(double x)
{
	return x * x - 15;
}

double derfunc(double x)
{
	return 2 * x;
}

double bisekcja( int &kroki, double E, double a=3, double b=4)
{

	double fa = func(a);
	double fb=func(b);
	if (fa*fb > 0 || abs(a-b)<E)
	{
		kroki = -1;
		return (a + b) / 2;
	}

	double delta;
	double fdelta;
	kroki=0;

	do
	{
		if (abs(a - b) < E)
		{
			kroki = -1;
			return delta;
		}
		kroki++;
		delta = (a + b) / 2;
		fdelta = func(delta);
		if (fa > 0)
		{
			if (fdelta > 0)
			{
				fa = fdelta;
				a = delta;
			}
			else
			{
				fb = fdelta;
				b = delta;
			}
		}
		else
		{
			if (fdelta < 0)
			{
				fa = fdelta;
				a = delta;
			}
			else
			{
				fb = fdelta;
				b = delta;
			}
		}

		

	} while (abs(fdelta) > E);

	return delta;
}

double newton(int &kroki, double E, double x = 4)
{
	kroki = 0;
	while (abs(func(x)) > E && kroki < K_MAX)
	{
		kroki++;
		x = x - (func(x) / derfunc(x));
	}

	if (abs(func(x)) <= E) return x;
	else
	{
		kroki = -1;
		return x;
	}
}

int main()
{
	std::cout << "Obliczanie rownan nieliniowych\nPodaj epsilon:";
	double epsilon;
	int kroki;
	std::cin >> epsilon;
	if (epsilon <= 0)
	{
		std::cout << "\nEpsilon nie moze byc mniejszy lub rowny 0!\n";
		system("pause");
		exit(1);
			
	}
	std::cout << "\nMetoda Bisekcji\n";
	double wynik=bisekcja(kroki,epsilon);
	if (kroki!=-1)
	{
		std::cout << "sqrt(15)=" << wynik << "\nliczba krokow = " << kroki;
	}
	else std::cout << "\n abs(a - b) < epsilon , wynik = " << wynik;
	

	std::cout << "\n\nMetoda Newtona\n";
	wynik = newton(kroki, epsilon);
	if (kroki != -1)
	{
		std::cout << "sqrt(15)=" << wynik << "\nliczba krokow = " << kroki;
	}
	else std::cout << "\nkroki = K_MAX! ";





	





	std::cout << "\n\n";
	system("pause");
	return 0;
}
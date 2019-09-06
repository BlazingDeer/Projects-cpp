#include <iostream>



class Base
{
public:
	virtual std::string func()
	{
		return "BASE";
	}

	int overf()
	{
		return 0;
	}

	int overf(int)
	{
		return 1;
	}
	
	virtual ~Base()
	{
		std::cout << "\nBase Destructor"<< std::endl;
	}
};


class Derived : public Base
{
public:
	virtual std::string func() override
	{
		return "DERIVED";
	}

	using Base::overf;

	int overf(int)
	{
		return 2;
	}

	virtual ~Derived()
	{
		std::cout << "\nDerived Destructor" << std::endl;
	}
};

int main()
{
	Base *pb;
	Derived d;
	pb = &d;

	std::cout <<"\n\n"<< pb->func()<< std::endl<< std::endl;

	std::cout << d.overf() << std::endl;




	return 0;
}
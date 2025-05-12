#include <iostream>

void Increment( int &x)
{
	++x;
}

int& GetRef(int &x)
{
	return x;
}

int main()
{
	int i =8;
	int &ip = i; //	int &ip = i;

	ip = 9;

	double d =  3.14;
	double dd =  4.5;

	double &ref_d = d;

	ref_d = 1.23;
	ref_d = dd;

	std::cout << "d="<< d << std::endl;
	std::cout <<"ref_d="<< ref_d << std::endl;
	std::cout <<"&ref_d="<< &ref_d << std::endl;
	std::cout <<"&d    ="<< &d << std::endl;
	std::cout <<"&dd    ="<< &dd << std::endl;



	Increment(i);
	std::cout << "Increment(i)="<< i << std::endl;

	Increment(ip);

	std::cout << "Increment(i)="<< i << std::endl;

	std::cout <<"sizeof(ip)="<< sizeof(ip) << std::endl;

	
	std::cout << "GetRef(i) = "<< GetRef(i) << std::endl;

	GetRef(i) = 20;
	std::cout << "GetRef(i) = 20 => i =  "<< i << std::endl;
	//std::cout <<"&ip="<<(&ip + 1) - &ip<< std::endl;


	/*
	std::cout << "d="<< d << std::endl;
	std::cout <<"ref_d="<< ref_d << std::endl;
	std::cout <<"&ref_d="<< &ref_d << std::endl;
	std::cout <<"&d    ="<< &d << std::endl;


	std::cout << "i="<< i << std::endl;
	std::cout <<"ip="<< ip << std::endl;
	std::cout <<"&ip="<< &ip << std::endl;
	std::cout <<"&i ="<< &i << std::endl;
	*/

	return 0;
}

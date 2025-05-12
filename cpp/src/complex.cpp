#include <iostream> // std::ostream, std::istream
#include <math.h> //std::sqrt
#include <cassert> //assert

#include "complex.hpp"
//#include "utils.hpp" //BAD_MEM

namespace nlrd
{
//member functions
//ctor
Complex::Complex(double real_, double imag_) 
	: m_real(real_), m_imag(imag_)
{}
//cctor
Complex::Complex(const Complex& other_)
	: m_real(other_.m_real), m_imag(other_.m_imag)  
{}

//assignment operator
Complex& Complex::operator=(const Complex& other_)
{
	if(this != &other_)
	{
		m_real= other_.m_real;
		m_imag= other_.m_imag;
	}

	return *this;
}

//dtor
Complex::~Complex()
{}
//Getters
double Complex::GetReal() const
{
	return m_real;
}

double Complex::GetImag() const
{
	return m_imag;
}
//Setters
void Complex::SetReal(double real_) 
{
	m_real= real_; 	
}

void Complex::SetImag(double imag_) 
{
	m_imag= imag_; 	
}

//Abs
double Complex::Abs() const
{
	return sqrt((m_real*m_real) + (m_imag*m_imag) );
}

// operator+=
Complex& Complex::operator+=(const Complex& other_)
{
	m_real+=other_.m_real;
	m_imag+=other_.m_imag;

	return *this;
}

// operator-=
Complex& Complex::operator-=(const Complex& other_)
{
	m_real+=-other_.m_real;
	m_imag+=-other_.m_imag;

	return *this;
}

// operator*=
Complex& Complex::operator*=(const Complex& other_)
{
	double real= m_real*other_.m_real - m_imag*other_.m_imag;
	double imag= m_real*other_.m_imag + m_imag*other_.m_real;

	m_real = real;
	m_imag = imag;

	return *this;
}

// operator/=
Complex& Complex::operator/=(const Complex& other_)
{
	
	
	const double epsilon = 1e-10;
	double denominator = (other_.GetReal() * other_.GetReal()) + 
						 (other_.GetImag() * other_.GetImag());

	assert(epsilon < denominator);

	double real = (m_real*other_.GetReal()) + (m_imag*other_.GetImag());
	double imag = (m_imag*other_.GetReal()) - (m_real*other_.GetImag());

	m_real= real / denominator;
	m_imag= imag / denominator;

	return *this;
}

//Global functions
//operator+ plus
Complex operator+(const Complex& lhs_, const Complex& rhs_)
{
	Complex ret(lhs_);
	return ret+=rhs_;
}

//operator- minus
Complex operator-(const Complex& lhs_, const Complex& rhs_)
{
	Complex ret(lhs_);
	return ret-=rhs_;
}

//operator* multiplexer
Complex operator*(const Complex& lhs_, const Complex& rhs_)
{
	Complex ret(lhs_);
	return ret*=rhs_;
}

//operator/ divisor
Complex operator/(const Complex& lhs_, const Complex& rhs_)
{
	Complex ret(lhs_);
	return ret/=rhs_;
}

//operator== equaler
bool operator==(const Complex& lhs_, const Complex& rhs_)
{
	return (lhs_.GetReal()==rhs_.GetReal()) && (lhs_.GetImag()==rhs_.GetImag());

}

//operator!= un-equaler
bool operator!=(const Complex& lhs_, const Complex& rhs_)
{
	return !(lhs_== rhs_);
}

//operator<< stdout
std::ostream& operator<<(std::ostream& os_, const Complex& z_)
{
	return os_<<'(' << z_.GetReal()<< ", "<< z_.GetImag()<< ')';
}

//operator>> stdin
std::istream& operator>>(std::istream& is_, Complex& z_)
{
	double real= 0.0;
	double imag= 0.0;
	char ch= 0;

	is_ >> ch;

	if('('==ch)
	{
		char comma= 0;
		char closing= 0;

		is_ >> real >> comma>> imag >> closing;

		if(is_ && ','==comma && ')' == closing)
		{
			z_.SetReal(real);
			z_.SetImag(imag);
		}
		else
		{
			is_.setstate(std::ios::failbit);
		}

	}
	else
	{
		// probably simple format: real imag
		is_.putback(ch); //return to the stream
		is_ >> real >> imag;


		if(is_) // can be fail
		{
			z_.SetReal(real);
			z_.SetImag(imag);
		}

	}

	return is_;
}

} //namespace nlrd







/*
Complex& Complex::operator*=(const Complex& other_)
{
	double real= m_real*other_.m_real - m_imag*other_.m_imag;
	double imag= m_real*other_.m_imag + m_imag*other_.m_real;

	m_real = real;
	m_imag = imag;

	return *this;
}
*/
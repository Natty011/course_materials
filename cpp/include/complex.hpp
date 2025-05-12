#ifndef NLRD_COMPLEX_HPP // NLRD_COMPLEX_HPP
#define NLRD_COMPLEX_HPP // NLRD_COMPLEX_HPP

#include <iostream> // std::ostream, std::istream

namespace nlrd
{

class Complex
{
public:
    explicit Complex(double real_ = 0.0, double imag_ = 0.0); //ctor
    Complex(const Complex& other_); //cctor
    Complex& operator=(const Complex& other_); //assignment operator
    ~Complex(); //dtor

    Complex& operator+=(const Complex& other_);
    Complex& operator-=(const Complex& other_);
    Complex& operator*=(const Complex& other_);
    Complex& operator/=(const Complex& other_);
    
    double GetReal() const;
    double GetImag() const;
    void SetReal(double real_);
    void SetImag(double imag_);

    double Abs() const;
    
private:
    double m_real;
    double m_imag;

}; // class Complex

Complex operator+(const Complex& lhs_, const Complex& rhs_);
Complex operator-(const Complex& lhs_, const Complex& rhs_);
Complex operator*(const Complex& lhs_, const Complex& rhs_);
Complex operator/(const Complex& lhs_, const Complex& rhs_);

bool operator==(const Complex& lhs_, const Complex& rhs_);
bool operator!=(const Complex& lhs_, const Complex& rhs_);

std::ostream& operator<<(std::ostream& os_, const Complex& z_);
std::istream& operator>>(std::istream& is_, Complex& z_);

}// namespace nlrd
#endif // NLRD_COMPLEX_HPP

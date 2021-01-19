/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Omer Hefetz                				  *
******************************************************************************/
#include <iostream>     // <<
#include "complex_number.hpp"

namespace ilrd
{
// -----------------------------Ctors & Dtor-----------------------------------
Complex::Complex(double real, double img) : m_real(real), m_img(img)
{
    //empty
}
Complex::~Complex()
{
    //empty
}
Complex::Complex(const Complex& other) : m_real(other.m_real), m_img(other.m_img)
{
    //empty
}
Complex& Complex::operator=(const Complex &num)
{
    m_real = num.m_real;
    m_img = num.m_img;

    return (*this);
}
// ----------------------------------------------------------------------------
// ---------------------------Global Operators---------------------------------
bool operator==(const Complex &num1, const Complex &num2)
{
    return (num1.GetReal() == num2.GetReal()
            && num1.GetImaginary() == num2.GetImaginary());
}

bool operator!=(const Complex &num1, const Complex &num2)
{
    return !(num1 == num2);
}

std::ostream& operator<<(std::ostream& out, const Complex& num)
{
    double real = num.GetReal();
    double img  = num.GetImaginary();
    return (out << real << ((img >= 0) ? " + ": "" ) << img << 'i' << std::endl);
}

std::istream& operator>>(std::istream& in, Complex& num)
{
    double input;

    std::cout << "real: ";
    in >> input;
    num.SetReal(input);

    std::cout << "imaginary: ";
    in >> input;
    num.SetImaginary(input);

    return (in);
}
// ----------------------------------------------------------------------------
}  //namespace ilrd

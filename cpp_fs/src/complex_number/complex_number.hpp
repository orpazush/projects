/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Omer Hefetz                				  *
******************************************************************************/
#ifndef ILRD_RD8788_COMPLEX_HPP
#define ILRD_RD8788_COMPLEX_HPP    

#include <iosfwd>   // ostream

namespace ilrd
{
class Complex
{
public:
    Complex(double m_real = 0, double m_img = 0); // non explicit by intention
    ~Complex();
    Complex(const Complex &other);
    Complex& operator=(const Complex &num);

    inline Complex& operator+=(const Complex &num)
    {
        m_real += num.m_real;
        m_img += num.m_img;

        return (*this);
    }
    // for benchmark check inline Complex& operator+=(const Complex num)
    // {
    //     m_real += num.m_real;
    //     m_img += num.m_img;
    //     return (*this);
    // }
    inline Complex& operator-=(const Complex &num)
    {
        m_real -= num.m_real;
        m_img -= num.m_img;

        return (*this);
    }
    inline Complex& operator*=(const Complex &num)
    {
        double tmpReal = m_real;
        
        m_real = ((tmpReal * num.m_real) - (m_img * num.m_img));
        m_img = ((tmpReal * num.m_img) + (num.m_real * m_img));
        
        return (*this);
    }
    inline Complex& operator/=(const Complex &num)
    {
        double tmpReal = m_real;
    
        double rNumerator = (tmpReal * num.m_real) + (m_img * num.m_img);
        double iNumerator = (num.m_real * m_img) - (tmpReal * num.m_img);
        double denominator = (num.m_real * num.m_real) + (num.m_img * num.m_img);
    
        m_real = (rNumerator / denominator);
        m_img = (iNumerator / denominator);
        
        return (*this);
    }

    inline void SetReal(double real)
    {
        m_real = real;
    }
    inline void SetImaginary(double imaginary)
    {
        m_img = imaginary;
    }
    inline double GetReal() const
    {
        return m_real;
    } 
    inline double GetImaginary() const
    {
        return m_img;
    }  

private:
    double m_real;
    double m_img;
};

inline const Complex operator+(const Complex &num1, const Complex &num2)
{
    Complex result(num1);

    return (result += num2);
}
inline const Complex operator-(const Complex &num1, const Complex &num2)
{
    Complex result(num1);
    
    return (result -= num2);
}
inline const Complex operator*(const Complex &num1, const Complex &num2)
{
    Complex result(num1);
    
    return (result *= num2);
}
inline const Complex operator/(const Complex &num1, const Complex &num2)
{
    Complex result(num1);
    
    return (result /= num2);
}

bool operator==(const Complex &num1, const Complex &num2);
bool operator!=(const Complex &num1, const Complex &num2);

std::ostream &operator<<(std::ostream &out, const Complex &num);
std::istream &operator>>(std::istream &in, Complex &num);

} // namespace ilrd

#endif // ILRD_RD8788_COMPLEX_HPP
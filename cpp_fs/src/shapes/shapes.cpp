/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Alex            						         *
 * 					Last update : 9.8.20									 *
 ****************************************************************************/
#include <iostream> //cout

#include "shapes.hpp"

namespace ilrd
{
Shape::Shape() : m_offset(0)
{
    //empty
}

Shape::~Shape()
{
    //empty
}

void Shape::Move()
{
    ++m_offset;
}

void Shape::PrintOffset() const
{
    for (size_t i = 0; i < m_offset; ++i)
    {
        std::cout << " ";
    }
}

void Line::Draw() const
{
    PrintOffset();
    std::cout << "I'm a Line" << std::endl;
}

void Circle::Draw() const
{
    PrintOffset();
    std::cout << "I'm a Circle" << std::endl;
}

void Rectangle::Draw() const
{
    PrintOffset();
    std::cout << "I'm a Rectangle" << std::endl;
}

void Square::Draw() const
{
    PrintOffset();
    std::cout << "I'm a Square" << std::endl;
}
} // namespace ilrd

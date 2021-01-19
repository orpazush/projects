/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Alex            						         *
 * 					Last update : 9.8.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_SHAPES_HPP
#define ILRD_RD8788_SHAPES_HPP

#include <cstddef>

namespace ilrd
{
class Shape
{
public:    
    explicit Shape();
    virtual ~Shape();
    virtual void Draw() const = 0; 
    void Move(); 
protected:
    void PrintOffset() const;
private:
    size_t m_offset;
};
class Line : public Shape
{
public:
    virtual void Draw() const;
};
class Circle : public Shape
{
public:
    virtual void Draw() const;
};
class Rectangle : public Shape
{
public:
    virtual void Draw() const;
};
class Square : public Shape
{
public:
    virtual void Draw() const;
};
} // namespace ilrd

#endif //ILRD_RD8788_SHAPE_HPP

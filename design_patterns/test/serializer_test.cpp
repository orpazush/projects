/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 11.10.20									 *
 ****************************************************************************/

#include <iostream>
#include "serializer.hpp"

using namespace ilrd;
using namespace project;
using namespace std;

class Shape
{
public:
//    Shape();
//    ~Shape();
    virtual void Print() =0;
    virtual void Serialize(std::ostream& out) const =0;
//    static Shape *Deserialize(std::istream& in);
};

class Circle : public Shape
{
public:
    Circle(size_t radius);
//    ~Circle();
    void Serialize(std::ostream& out) const;
    void Print();
    static Shape *Deserialize(std::istream& in);
private:
    size_t m_radius;
};

Circle::Circle(size_t radius) : m_radius(radius)
{
    cout << "ctor Circle\n";
}

void Circle::Serialize(std::ostream& out) const
{
    out << m_radius;
}

Shape *Circle::Deserialize(std::istream &in)
{
    size_t radius = 0;
    in >> radius;

    return (new Circle(radius));
}

void Circle::Print()
{
    cout << m_radius << endl;
}

class Square : public Shape
{
public:
    Square(size_t width, size_t length);
//    ~Square();
    void Serialize(std::ostream& out) const;
    void Print();
    static Shape *Deserialize(std::istream& in);
private:
    size_t m_width;
    size_t m_length;
};

Square::Square(size_t width, size_t length) : m_width(width), m_length(length)
{
    cout << "ctor Square\n";
}

void Square::Serialize(std::ostream &out) const
{
    out << m_width << " ";
    out << m_length;
}

Shape *Square::Deserialize(std::istream &in)
{
    size_t width = 0;
    size_t length = 0;

    in >> width;
    in >> length;

    return (new Square(width, length));
}

void Square::Print()
{
    cout << m_width << endl;
    cout << m_length << endl;
}

int main()
{
    Serializer<Shape> seria;
    seria.Add<Circle>();
    seria.Add<Square>();

    Circle circ(5);
    Square sque(8, 4);

    std::stringbuf buffer;
    std::ostream out(&buffer);
    std::istream in(&buffer);

    seria.Serialize(out, circ);
    seria.Serialize(out, sque);

    boost::shared_ptr<Shape> p_circ = seria.Deserialize(in);
    boost::shared_ptr<Shape> p_sque = seria.Deserialize(in);

    cout << typeid(circ).name() << endl;
    cout << typeid(Square).name() << endl;

    p_circ->Print();
    p_sque->Print();

    return 0;
}
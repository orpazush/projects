/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Alex            						         *
 * 					Last update : 9.8.20									 *
 ****************************************************************************/
#include <iostream>     //cout
#include <list>         //list
#include <iterator>     //iterator

#include "shapes.hpp"

using namespace ilrd;
using namespace std;

void Drawlist(list<Shape *> shapeList);

int main()
{
    list<Shape *> shapeList;
    Line line;
    Circle circle;
    Rectangle rectangle;
    Square square;

    for (size_t i = 0; i < 3; ++i)
    {
        shapeList.push_back(&line);
        shapeList.push_back(&circle);
        shapeList.push_back(&rectangle);
        shapeList.push_back(&square);
    }
    
    line.Move();
    circle.Move();
    circle.Move();
    Drawlist(shapeList);

    return (0);
}

void Drawlist(list<Shape *> shapeList)
{
    list<Shape *>::iterator i;
    for (i = shapeList.begin(); i != shapeList.end(); ++i)
    {
        Shape *shape = *i;
        shape->Draw();
    }
}

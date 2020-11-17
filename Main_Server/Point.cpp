#include "Point.h"

Point::Point()
    :dotX(0), dotY(0)
{}

Point::Point(double dotX, double dotY)
    :dotX(dotX), dotY(dotY)
{}

double Point::GetX()
{
    return dotX;
}

double Point::GetY()
{
    return dotY;
}

void Point::SetX(double dotX)
{
    this->dotX=dotX;
}

void Point::SetY(double dotY)
{
    this->dotY=dotY;
}

void Point::ShowXY()
{
    cout<<"dotX: "<<dotX<<" dotY: "<<dotY<<endl;
}
#pragma once

#include "Common.h"

class Point
{
private:
    double dotX;
    double dotY;
public:
    Point();
    Point(double,double);
    double GetX();
    double GetY();
    void SetX(double dotX);
    void SetY(double dotY);
    void ShowXY();
};
#pragma once
#include "Shape.h"
#include <vector>

using namespace std;

class Menu
{
public:
    static MyCircle* addCircle(int c, int a = 200, int b = 200, int r = 50);
    static MyRect* addRect(int c, int a = 300, int b = 300, int w = 100, int h = 100);
    static Aggregation* addAggregation(const vector<Shape*>& shapes, int c);
    static MyStar* addStar(int c, int a = 400, int b = 400, int r = 50); 
    static void selectNext(int len, int& n);
    static void selectPrev(int& n);
};
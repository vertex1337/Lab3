#include "Menu.h"

MyCircle* Menu::addCircle(int c, int a, int b, int r)
{
    return new MyCircle(a, b, r, c);
}

MyRect* Menu::addRect(int c, int a, int b, int w, int h)
{
    return new MyRect(a, b, w, h, c);
}

Aggregation* Menu::addAggregation(const vector<Shape*>& shapes, int c)
{
    return  new Aggregation(shapes, c);
}

MyStar* Menu::addStar(int c, int a, int b, int r)
{
    return new MyStar(a, b, r, c); 
}

void Menu::selectNext(int len, int& n)
{
    n = n < len - 1 ? ++n : n;
}

void Menu::selectPrev(int& n)
{
    n = n > 0 ? --n : n;
}
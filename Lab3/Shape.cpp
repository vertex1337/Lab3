#include "Shape.h"

Grfx::Graphics cg;

Shape::Shape(int c) : x(0), y(0), color(c) {}

Shape::Shape(int a, int b, int c) : x(a), y(b), color(c) {}

bool Shape::colide(vector<Shape*> shapes)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (this == shapes[i])
        {
            continue;
        }
        if (Aggregation* agg = dynamic_cast<Aggregation*>(this))
        {
            for (int j = 0; j < agg->aggShapes.size(); j++)
            {
                if (agg->colide(shapes))
                {
                    this->setColor(agg->aggShapes[j]->getColor());
                    return true;
                }
            }
        }
        if (MyCircle* other = dynamic_cast<MyCircle*>(shapes[i]))
        {
            if (colidesWithCircle(other))
            {
                this->setColor(other->getColor());
                return true;
            }
        }
        if (MyRect* other = dynamic_cast<MyRect*>(shapes[i]))
        {
            if (colidesWithRect(other))
            {
                this->setColor(other->getColor());
                return true;
            }
        }
        if (Aggregation* other = dynamic_cast<Aggregation*>(shapes[i]))
        {
            if (this->colide(other->aggShapes)) {
                this->setColor(other->getColor());
            }
        }
    }
}

void Shape::show() { draw(color); }
void Shape::hide() { draw(BGCOLOR); }
void Shape::move(int dx, int dy, vector<Shape*> shapes, bool isTale) {
    if (!isTale) hide();
    x += dx;
    y += dy;
    show();
    colide(shapes);
}

void Shape::setColor(int c)
{
    color = c;
    cg.setcolor(c);
}

int Shape::getX()
{
    return this->x;
}

int Shape::getY()
{
    return this->y;
}

int Shape::getColor()
{
    return this->color;
}


MyCircle::MyCircle(int a, int b, int r, int c) : Shape(a, b, c), radius(r) { show(); }

Shape* MyCircle::Clone() const
{
    return new MyCircle(*this);
}

void MyCircle::draw(int c) {
    cg.setcolor(c);
    cg.circle(x, y, radius);
}

int MyCircle::getR()
{
    return this->radius;
}

bool MyCircle::colidesWithCircle(Shape* other)
{
    return ShapesHelper::areCollide(this, dynamic_cast<MyCircle*>(other));
}

bool MyCircle::colidesWithRect(Shape* other)
{
    return ShapesHelper::areCollide(this, dynamic_cast<MyRect*>(other));
}

void MyCircle::reduce()
{
    if (radius > 5)
    {
        radius -= 5;
    }
}

void MyCircle::increase()
{
    if (radius < 100)
    {
        radius += 5;
    }
}


MyRect::MyRect(int a, int b, int w, int h, int c) : Shape(a, b, c), width(w), height(h) { show(); }

Shape* MyRect::Clone() const
{
    return new MyRect(*this);
}

void MyRect::draw(int c)
{
    cg.setcolor(c);
    cg.rectangle(x, y, width, height);
}


bool MyRect::colidesWithCircle(Shape* other)
{
    return ShapesHelper::areCollide(dynamic_cast<MyCircle*>(other), this);
}

bool MyRect::colidesWithRect(Shape* other)
{
    return ShapesHelper::areCollide(this, dynamic_cast<MyRect*>(other));
}

int MyRect::getWidth()
{
    return this->width;
}

int MyRect::getHeight()
{
    return this->height;
}

void MyRect::reduce()
{
    if (width > 5 || height > 5)
    {
        width -= 5;
        height -= 5;
    }

}

void MyRect::increase()
{
    if (width < 200 || height < 200)
    {
        width += 5;
        height += 5;
    }
}

MyStar::MyStar(int a, int b, int r, int c) : Shape(a, b, c), radius(r) { show(); }

Shape* MyStar::Clone() const {
    return new MyStar(*this);
}

void MyStar::draw(int c) {
    cg.setcolor(c);

    int x1 = x - radius;
    int y1 = y + radius;
    int x2 = x + radius;
    int y2 = y + radius;
    int x3 = x;
    int y3 = y - radius;

    cg.line(x1, y1, x2, y2);
    cg.line(x2, y2, x3, y3);
    cg.line(x3, y3, x1, y1);
}

bool MyStar::colidesWithCircle(Shape* other) {
    return ShapesHelper::areCollide(this, dynamic_cast<MyCircle*>(other));
}

bool MyStar::colidesWithRect(Shape* other) {
    return ShapesHelper::areCollide(this, dynamic_cast<MyRect*>(other));
}

void MyStar::reduce() {
    if (radius > 5) {
        radius -= 5;
    }
}

void MyStar::increase() {
    if (radius < 100) {
        radius += 5;
    }
}

Aggregation::Aggregation(const vector<Shape*>& otherShapes, int c) : Shape(c)
{
    for (int i = 0; i < otherShapes.size(); i++)
    {
        aggShapes.push_back(otherShapes[i]->Clone());
    }
    show();
}

Shape* Aggregation::Clone() const
{
    return new Aggregation(*this);
}

void Aggregation::setColor(int c)
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->setColor(c);
    }
}

void Aggregation::show()
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->show();
    }
}

void Aggregation::draw(int c)
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->draw(c);
    }
}

void Aggregation::hide()
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->hide();
    }
}

void Aggregation::move(int dx, int dy, vector<Shape*> shapes, bool isTail)
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->move(dx, dy, shapes, isTail);
    }
}

bool Aggregation::colidesWithCircle(Shape* other)
{
    return false;
}

bool Aggregation::colidesWithRect(Shape* other)
{
    return false;
}

void Aggregation::reduce()
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->reduce();
    }
}

void Aggregation::increase()
{
    for (int i = 0; i < aggShapes.size(); i++)
    {
        aggShapes[i]->increase();
    }
}


bool ShapesHelper::areCollide(MyCircle* circle1, MyCircle* circle2) {
    int distanceSquared = (circle1->getX() - circle2->getX()) * (circle1->getX() - circle2->getX()) +
        (circle1->getY() - circle2->getY()) * (circle1->getY() - circle2->getY());
    int radiusSumSquared = (circle1->getR() + circle2->getR()) * (circle1->getR() + circle2->getR());
    return distanceSquared <= radiusSumSquared;
}

bool ShapesHelper::areCollide(MyCircle* circle, MyRect* rect) {
    int closestX = max(rect->getX(), min(circle->getX(), rect->getX() + rect->getWidth()));
    int closestY = max(rect->getY(), min(circle->getY(), rect->getY() + rect->getHeight()));
    int distanceSquared = (circle->getX() - closestX) * (circle->getX() - closestX) +
        (circle->getY() - closestY) * (circle->getY() - closestY);
    return distanceSquared <= circle->getR() * circle->getR();
}

bool ShapesHelper::areCollide(MyRect* rect1, MyRect* rect2) {
    return !(rect1->getX() + rect1->getWidth() <= rect2->getX() ||
        rect1->getX() >= rect2->getX() + rect2->getWidth() ||
        rect1->getY() + rect1->getHeight() <= rect2->getY() ||
        rect1->getY() >= rect2->getY() + rect2->getHeight());
}

bool ShapesHelper::areCollide(MyStar* star, MyCircle* circle) {
    return false;
}

bool ShapesHelper::areCollide(MyStar* star, MyRect* rect) {
    return false;
}

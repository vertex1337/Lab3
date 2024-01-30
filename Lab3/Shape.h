#pragma once
#include "graphics.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

static class ShapesHelper;

class Shape {
private:
    const int BGCOLOR = 0;
protected:
    int x, y, color;

public:
    Shape(int c);
    Shape(int a, int b, int c);
    virtual Shape* Clone() const = 0;
    virtual void draw(int c) = 0;
    virtual bool colidesWithCircle(Shape* other) = 0;
    virtual bool colidesWithRect(Shape* other) = 0;
    virtual void reduce() = 0;
    virtual void increase() = 0;
    bool colide(vector<Shape*> shapes);
    virtual void show();
    virtual void hide();
    virtual void move(int dx, int dy, vector<Shape*> shapes, bool isTail = 0);
    virtual void setColor(int c);
    int getX();
    int getY();
    int getColor();
};

class MyCircle : public Shape {
protected:
    int radius;
public:
    MyCircle(int a, int b, int r, int c);
    Shape* Clone() const;
    void draw(int c);
    int getR();
    bool colidesWithCircle(Shape* other);
    bool colidesWithRect(Shape* other);
    void reduce();
    void increase();
};


class MyRect : public Shape {
protected:
    int width, height;
public:
    MyRect(int a, int b, int w, int h, int c);
    Shape* Clone() const;
    void draw(int c);
    bool colidesWithCircle(Shape* other);
    bool colidesWithRect(Shape* other);
    int getWidth();
    int getHeight();
    void reduce();
    void increase();
};

class MyStar : public Shape {
protected:
    int radius;
public:
    MyStar(int a, int b, int r, int c);
    Shape* Clone() const override;
    void draw(int c) override;
    bool colidesWithCircle(Shape* other) override;
    bool colidesWithRect(Shape* other) override;
    void reduce() override;
    void increase() override;
};


class Aggregation : public Shape {
public:
    vector<Shape*> aggShapes;
    Aggregation(const vector<Shape*>& otherShapes, int c);
    Shape* Clone() const;
    void setColor(int c);
protected:
    void show();
    void draw(int c);
    void hide();
    void move(int dx, int dy, vector<Shape*> shapes, bool isTail);
    bool colidesWithCircle(Shape* other);
    bool colidesWithRect(Shape* other);
    void reduce();
    void increase();
};

static class ShapesHelper {
public:
    static bool areCollide(MyCircle* circle1, MyCircle* circle2);
    static bool areCollide(MyCircle* circle, MyRect* rect);
    static bool areCollide(MyRect* rect1, MyRect* rect2);
    static bool areCollide(MyStar* star, MyCircle* circle);
    static bool areCollide(MyStar* star, MyRect* rect);
};

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include "Shape.h"
#include "Menu.h"

using namespace std;

vector<Shape*> shapes;
vector<Shape*> s;
vector<Shape*> newAgg;
int selected_index = 0;
bool isTale = false;

void printInstructions() {
    system("CLS");
    cout << "Добро пожаловать в программу управления фигурами!" << endl;
    cout << "Нажмите:" << endl;
    cout << "1 - создать круг" << endl;
    cout << "2 - создать квадрат" << endl;
    cout << "3 - создать треугольник" << endl;
    cout << "w,a,s,d - переместить выбранный объект" << endl;
    cout << "p - выбрать предыдущий объект" << endl;
    cout << "n - выбрать следующий объект" << endl;
    cout << "- - уменьшить размер объекта" << endl;
    cout << "+ - увеличить размер объекта" << endl;
    cout << "[ - добавить объект в агрегацию" << endl;
    cout << "] - создать агрегацию" << endl;
    cout << "z - установить цвет объекта на 1" << endl;
    cout << "x - установить цвет объекта на 2" << endl;
    cout << "i - вывести инструкции" << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    printInstructions();

    char input;
    while (true)
    {
        input = _getch();

        switch (input)
        {
        case 'i':
            printInstructions();
            break;
        case '1':
            shapes.push_back(Menu::addCircle(rand() % 5 + 1));
            selected_index = shapes.size() - 1;
            break;
        case '2':
            shapes.push_back(Menu::addRect(rand() % 5 + 1));
            selected_index = shapes.size() - 1;
            break;
        case '3':
            shapes.push_back(Menu::addStar(rand() % 5 + 1));
            selected_index = shapes.size() - 1;
            break;
        case 'd':
            shapes[selected_index]->move(2, 0, shapes);
            break;
        case 'a':
            shapes[selected_index]->move(-2, 0, shapes);
            break;
        case 'w':
            shapes[selected_index]->move(0, -2, shapes);
            break;
        case 's':
            shapes[selected_index]->move(0, 2, shapes);
            break;
        case 'p':
            Menu::selectPrev(selected_index);
            break;
        case 'n':
            Menu::selectNext(shapes.size(), selected_index);
            break;
        case '-':
            shapes[selected_index]->reduce();
            break;
        case '+':
            shapes[selected_index]->increase();
            break;
        case '[':
            s.push_back(shapes[selected_index]);
            break;
        case ']':
            if (s.size() > 0)
            {
                shapes.push_back(Menu::addAggregation(s, s[0]->getColor()));
                s.clear();
                selected_index = shapes.size() - 1;
            }
            break;
        case 'z':
            if (selected_index < shapes.size()) {
                shapes[selected_index]->setColor(1); 
            }
            break;
        case 'x':
            if (selected_index < shapes.size()) {
                shapes[selected_index]->setColor(2); 
            }
            break;
        default:
            break;
        }

        // Показать все объекты на экране
        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->show();
        }

        // Задержка для обновления экрана
        Sleep(1000 / 60);
    }

    return 0;
}

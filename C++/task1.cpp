#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
    // Вывод заголовка таблицы
    cout << "+----------+----------+" << endl;
    cout << "|         x|         y|" << endl;
    cout << "+----------+----------+" << endl;

    // Определение переменных и контейнера для хранения пар (x, y)
    double toch = 10000.0; // Точность округления до 4 знаков после запятой
    double y;              // Переменная для хранения значения функции
    double delta = 0.5;    // Шаг изменения x

    double R = 2.0;
    double r = 1.0;

    double centerX; // Координата x центра полуокружности
    double centerY; // Координата y центра полуокружности

    vector<tuple<double, double>> cont; // Вектор кортежей для хранения пар (x, y)
    tuple<double, double> tek;          // Текущий кортеж для добавления в вектор

    // Цикл для вычисления значений y для различных диапазонов x
    for (double x = -9; x <= 5; x += delta)
    {
        x = round(x * toch) / toch; // Округление x до 4 знаков после запятой
        if (x <= -5)
        {
            y = 2; // Вычисление y для x в диапазоне [-9, -5]
        }
        else if (x > -5 && x < -1)
        {

            centerX = -3.0;
            centerY = 2.0;
            y = centerY - sqrt(R * R - (x - centerX) * (x - centerX));
        }
        else if (x > -1 && x < 1)
        {
            y = -cosh(2 * x) + 2;
        }
        else if (x > 1 && x <= 2)
        {
            y = 0;
        }
        else if (x > 2 && x <= 4)
        {

            centerX = 3.0;
            centerY = 0.0;
            y = centerY + sqrt(r * r - (x - centerX) * (x - centerX));
        }
        else if (x > 4)
        {
            y = 0;
        }
        y = round(y * toch) / toch; // Округление y до 4 знаков после запятой
        tek = make_tuple(x, y);     // Создание кортежа с текущими значениями x и y
        cont.push_back(tek);        // Добавление кортежа в вектор
    }

    // Вывод таблицы с результатами
    for (int i = 0; i < cont.size(); i++)
    {
        cout << "|" << setw(10) << get<0>(cont[i]) << "|" << setw(10) << get<1>(cont[i]) << "|" << endl;
        cout << "+----------+----------+" << endl;
    }
}
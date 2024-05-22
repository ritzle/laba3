#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iomanip>
// #include <Windows.h>

using namespace std;

double T;                   // Переменная для хранения начальной температуры кофе
double Ts;                  // Переменная для хранения температуры окружающей среды
double r;                   // Переменная для хранения коэффициента остывания
int time_limit;             // Переменная для хранения итогового времени
vector<double> apox_vector; // Вектор для хранения коэффициентов аппроксимирующей прямой

// Функция для вычисления коэффициента корреляции Пирсона
double korrel(const vector<double> &temperatures, double mean_y, int t)
{
    double sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
    double mean_x = (time_limit - 1) / 2.0;
    for (int i = 0; i <= t; i++)
    {
        sum_xy += (i - mean_x) * (temperatures[i] - mean_y);
        sum_x2 += (i - mean_x) * (i - mean_x);
        sum_y2 += (temperatures[i] - mean_y) * (temperatures[i] - mean_y);
    }
    return sum_xy / sqrt(sum_x2 * sum_y2);
}

// Функция для вычисления коэффициентов аппроксимирующей прямой методом наименьших квадратов
pair<double, double> aprox(const vector<double> &x_vector, const vector<double> &y_vector)
{
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    int n = x_vector.size();

    for (int i = 0; i < n; i++)
    {
        sum_x += x_vector[i];
        sum_y += y_vector[i];
        sum_xy += x_vector[i] * y_vector[i];
        sum_x2 += x_vector[i] * x_vector[i];
    }

    double a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double b = (sum_y - a * sum_x) / n;

    return make_pair(a, b);
}

// Функция для моделирования остывания кофе и вычисления коэффициентов корреляции
vector<pair<double, double>> coffee(double T, double Ts, double r, int time_limit)
{
    vector<double> temperatures;
    vector<double> times;
    vector<pair<double, double>> temp_corr;

    for (int t = 0; t <= time_limit; t++)
    {
        double temperature = Ts + (T - Ts) * exp(-r * t);
        temperatures.push_back(temperature);
        times.push_back(t);
    }

    pair<double, double> aprox_coeffs = aprox(times, temperatures);
    double a = aprox_coeffs.first;
    double b = aprox_coeffs.second;

    apox_vector = {a, b};

    double mean_y = accumulate(temperatures.begin(), temperatures.end(), 0.0) / temperatures.size();
    for (int t = 0; t <= time_limit; t++)
    {
        double corr = korrel(temperatures, mean_y, t);
        temp_corr.push_back(make_pair(temperatures[t], corr));
    }

    return temp_corr;
}

int main()
{
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    cout << "Введите начальную температуру кофе: ";
    cin >> T;
    cout << "Введите температуру окружающей среды: ";
    cin >> Ts;
    cout << "Введите коэффициент остывания: ";
    cin >> r;
    cout << "Введите итоговое время: ";
    cin >> time_limit;

    // Вызов функции coffee для моделирования остывания кофе
    vector<pair<double, double>> results = coffee(T, Ts, r, time_limit);

    cout << "Коэффициенты аппроксимирующей прямой а - " << apox_vector[0] << ", b - " << apox_vector[1] << endl;
    cout << "+------+" << "------------+" << "---------------+" << endl;
    cout << "| Время|" << " Температура|" << " Коэф.кореляции|" << endl;
    cout << "+------+" << "------------+" << "---------------+" << endl;

    int t = 0;

    // Цикл для вывода результатов моделирования остывания кофе
    for (const auto &result : results)
    {

        cout << "|" << setw(6) << t << "|" << setw(12) << result.first << "|" << setw(15) << result.second << "|" << endl;
        t++;
        cout << "+------+" << "------------+" << "---------------+" << endl;
    }

    return 0;
}
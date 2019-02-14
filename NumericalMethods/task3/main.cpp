#include <iostream>
#include <math.h>
#include <iomanip>

double f(double x, double y) {
return pow(x, 2) - y + 2 - pow(M_E, x*y);
}

double g(double x, double y) {
return pow(x + 0.5, 2) + pow(y, 2) - 1.5;
}

double f_x(double x, double y) {
return 2 * x - y * pow(M_E, x*y);
}

double f_y(double x, double y) {
return -x * pow(M_E, x*y) - 1;
}

double g_x(double x, double y) {
return 2 * (x + 0.5);
}

double g_y(double x, double y) {
return 2 * y;
}

double f_x_numeric(double x, double y, double h) {
return (f(x + h, y) - f(x, y)) / h;
}

double f_y_numeric(double x, double y, double h) {
return (f(x, y + h) - f(x, y)) / h;
}

double g_x_numeric(double x, double y, double h) {
return (g(x + h, y) - g(x, y)) / h;
}

double g_y_numeric(double x, double y, double h) {
return (g(x, y + h) - g(x, y)) / h;
}

void Analytic(double x, double y) {

int k = 0;
double middle_x;
double middle_y;
double delta;
const double eps = 0.00001;

do {

middle_x = x;
middle_y = y;

delta = (f_x(x, y) * g_y(x, y) - g_x(x, y) * f_y(x, y));

x = middle_x - (g_y(x, y) * f(x, y) - f_y(x, y) * g(x, y)) / delta;
y = middle_y - (f_x(x, y) * g(x, y) - g_x(x, y) * f(x, y)) / delta;

k++;

} while (fabs(middle_x - x) >= eps && fabs(middle_y - y) >= eps);

std::cout << "Количество иттераций:" << k << std::endl <<
            "x=" << std::setprecision(6) << x << std::endl <<
            "y=" << std::setprecision(6) << y << std::endl;

}

void Numeric(double x, double y) {

int k = 0
double middle_x;
double middle_y;
const double eps = 0.00001;
double h = 0.001;

do {

middle_x = x;
middle_y = y;
double delta = (f_x_numeric(x, y, h) * g_y_numeric(x, y, h) - g_x_numeric(x, y, h) * f_y_numeric(x, y, h));
x = middle_x - (g_y_numeric(x, y, h) * f(x, y) - f_y_numeric(x, y, h) * g(x, y)) / delta;
y = middle_y - (f_x_numeric(x, y, h) * g(x, y) - g_x_numeric(x, y, h) * f(x, y)) / delta;

k++;

} while (fabs(middle_x - x) >= eps && fabs(middle_y - y) >= eps);

std::cout << "Количество иттераций:" << k << std::endl <<
            "x=" << std::setprecision(6) << x << std::endl <<
            "y=" << std::setprecision(6) << y << std::endl;

}

int main() {

std::cout << "Частные производные находятся аналитически:" << std::endl;
Analytic(-0.1, 1);
Analytic(0.5, 0.7);
std::cout << "Частные производные находятся численно:" << std::endl;
Numeric(-0.1, 1);
Numeric(0.5, 0.7);

return 0;

}
#include <iostream>
#include <cmath>
#include <iomanip>

double Equation(double dot)
{
    return pow(dot,5)-2*dot-1;
}
double Equation_derivative(double dot)
{
    return 5*pow(dot,4)-2;
}

double Equation_second_derivative(double dot)
{
    return 20*pow(dot,3);
}


void Newton(double left_border , double right_border)
{
    int k=0;
    double eps = 0.00001;
    double x, middle_value;

    if (Equation(left_border) * Equation_second_derivative(left_border) > 0)
        middle_value = left_border;
    else middle_value = right_border;

    do{
        x = middle_value;
        middle_value = x - Equation(x) / Equation_derivative(x);
        k++;

    } while (fabs(x - middle_value) > eps && fabs(Equation(middle_value))>eps);

    std::cout << "Метод Ньютона на отрезке [" << left_border << "," << right_border << "]:" << std::endl <<
    "Число итераций:" << k << std::endl <<
    "Корень равен :" << std::setprecision(5) << middle_value << std::endl;
}

void  Relax(double left_border, double right_border)

{

    int k=0;
    double x, t=0.0, tau_optimal=0.0;
    double eps = 0.00001;

    t = (left_border + right_border) / 2;

    if (Equation_derivative(left_border) > 0 && Equation_derivative(right_border) > 0)
    {
        tau_optimal = -2 / fabs(Equation_derivative(left_border) + Equation_derivative(right_border));
    }
    else if (Equation_derivative(left_border) < 0 && Equation_derivative(right_border) < 0)
    {
        tau_optimal = 2 / fabs(Equation_derivative(left_border) + Equation_derivative(right_border));
    }

    do{
        x = t;
        t = x + tau_optimal * Equation(x);
        k++;

    } while ((fabs(x - t) > eps) && (fabs(Equation(t)) > eps));

    std::cout << "Метод релаксации на отрезке [" << left_border << "," << right_border << "]:" << std::endl <<
              "Число итераций:" << k << std::endl <<
              "Корень равен :" << std::setprecision(5) << t << std::endl;
}

int main()
{
    Newton(-1.5,-0.8);
    Newton(-0.6,-0.5);
    Newton(1.0,2.0);
    Relax(-1.5,-0.8);
    Relax(-0.6,-0.5);
    Relax(1.0,2.0);

    return 0;
}

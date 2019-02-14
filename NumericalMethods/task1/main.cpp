#include <iostream>
#include<cmath>
#include<ctime>
#include <iomanip>


int main() {

    unsigned int iteration_number = 0;
    double summ = 0;
    int k = 1;
    double eps = 1e-15;
    double x , result;
    std::cout << "Введите x:";
    std::cin >> x;
    std::cout << std::endl;

    result = 1/tanh(x)-1/x;

    double element;

    do
    {
        element = 0;
        element=1/pow(2,k)*tanh(x/pow(2,k));
        summ+=element;
        std::cout << std::setprecision(15) << summ << std::endl;
        iteration_number++;
        k++;
    }while(fabs(summ-(summ-element))>eps);

    std::cout << "cthx-1/x = " << std::setprecision(15) << result << std::endl;
    std::cout << "Количество итераций:" << iteration_number << std::endl;
    std::cout << "Сумма = " << std::setprecision(15) << summ << std:: endl;
    return 0;
}
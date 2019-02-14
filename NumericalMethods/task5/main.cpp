#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x) {
return log(cos(x));
}

void simpsonMethod(double a, double b, double eps) {
unsigned step_count = 1;
double current = 0;
double previous;

do {

double h;
double sum = 0;
double sum2 = 0;
double sum4 = 0;

previous = current;
step_count *= 2;

h = (b - a) / (2 * step_count);

for (int i = 1; i <= 2 * step_count - 1; i += 2){
sum4 += f(a + h * i);
sum2 += f(a + h * (i + 1));

}

sum = f(a) + 4 * sum4 + 2 * sum2 - f(b);
current = (h / 3)*sum;

} while (fabs(previous - current) > eps);

std::cout << "Метод Симпсона" << std::endl;
std::cout << "Ответ:" << std::setprecision(4) << current << std::endl;
std::cout << "Количество разбиений:" << step_count << std::endl;

}

void trapeziumMethod(double a, double b, double eps) {

unsigned step_count = 1;
double current = 0;
double previous;

do {

double h;
step_count *= 2;
previous = current;
current = 0;

h = (b - a) / (1.0 * step_count);
for (int i = 1; i < step_count; ++i) {
current += f(a + i * h);
}

current += (f(a) + f(b)) / 2;
current *= h;

} while (fabs(previous - current) > eps);

std::cout << "Метод Трапеций" << std::endl;
std::cout << "Ответ:" << std::setprecision(4) << current << std::endl;
std::cout << "Количество разбиений:" << step_count << std::endl;

}

int main() {

double eps = 0.00005;

std::cout << "Точность:" << eps << std::endl;
trapeziumMethod(0, M_PI / 4, eps);
simpsonMethod(0, M_PI / 4, eps);

return 0;

}
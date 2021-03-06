#include"pch.h"
#include <iostream>

#include <array>

#include <iomanip>

std::array<double, 4> multiplication(std::array<std::array<double, 4>, 4> first, std::array<double, 4> second) {

	std::array<double, 4> result = { 0,0,0,0 };

	for (int i = 0; i < 4; i++) {

		double elem = 0;

		for (int j = 0; j < 4; j++) {

			elem += first[i][j] * second[j];

		}

		result[i] = elem;

	}

	return result;

}

double scalar(std::array<double, 4> first, std::array<double, 4> second) {

	double result = 0;

	for (int i = 0; i < 4; i++) {

		result += first[i] * second[i];

	}

	return result;

}

std::array<double, 4> minus(std::array<double, 4> first, std::array<double, 4> second) {

	std::array<double, 4> result = { 0,0,0,0 };

	for (int i = 0; i < 4; i++) {

		result[i] = first[i] - second[i];

	}

	return result;

}

void Fastest_Decent(std::array<std::array<double, 4>, 4> A, std::array<double, 4> f) {

	std::array<double, 4> x_0 = { 0,0,0,0 };
	std::array<std::array<double, 4>, 4> A_;
	for (int i = 0; i < 4; i++)

	{
		x_0[i] = f[i] / A[i][i];
	}

	auto x_n = x_0;

	auto r_n = multiplication(A, x_0);

	r_n = minus(r_n, f);

	std::array<double, 4> Ar;

	std::array<double, 4> AAr;

	std::array<std::array<double, 4>, 4> transposed_A;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			transposed_A[i][j] = A[j][i];
		}
	}

	auto previous = x_0;
	double mu;
	double eps = 1e-7;

	double counter = 0;
	double left;

	do {

		left = 0;

		Ar = multiplication(transposed_A, r_n);

		AAr = multiplication(A, Ar);

		mu = scalar(r_n, AAr) / scalar(AAr, AAr);

		previous = x_n;

		for (int i = 0; i < 4; ++i) {

			Ar[i] = mu * Ar[i];

		}

		x_n = minus(x_n, Ar);

		r_n = minus(multiplication(A, x_n), f);

		counter++;

		std::array<double, 4> res = { 0,0,0,0 };

		for (int j = 0; j < 4; j++) {

			res[j] = fabs(previous[j] - x_n[j]);

		}

		for (int k = 0; k < 4; k++) {

			if (res[k] > left)

				left = res[k];

		}
	} while (left > eps);

	for (int i = 0; i < 4; i++) {

		std::cout << "[" << std::setprecision(7) << x_n[i] << "]" << std::endl;

	}

	std::cout << "Шаг:" << counter << std::endl;

}

void Gauss(std::array<std::array<double, 4>, 4> A, std::array<double, 4> f) {

	std::array<double, 4> x_0;

	double max;

	int index, k = 0;

	double eps = 1e-5;

	while (k < 4)

	{

		max = abs(A[k][k]);

		index = k;

		for (int i = k + 1; i < 4; i++)

		{

			if (abs(A[i][k]) > max)

			{

				max = abs(A[i][k]);

				index = i;

			}

		}

		if (max < eps)

		{

			std::cout << "Решение получить невозможно из-за нулевого столбца ";

			std::cout << index << " матрицы A" << std::endl;

			exit(-1);

		}

		for (int j = 0; j < 4; j++)

		{

			double temp = A[k][j];

			A[k][j] = A[index][j];

			A[index][j] = temp;

		}

		double temp = f[k];

		f[k] = f[index];

		f[index] = temp;

		for (int i = k; i < 4; i++)

		{

			double temp = A[i][k];

			if (abs(temp) < eps) continue;

			for (int j = 0; j < 4; j++)

				A[i][j] = A[i][j] / temp;

			f[i] = f[i] / temp;

			if (i == k) continue;

			for (int j = 0; j < 4; j++)

				A[i][j] = A[i][j] - A[k][j];

			f[i] = f[i] - f[k];

		}

		k++;

	}

	for (k = 4 - 1; k >= 0; k--)

	{

		x_0[k] = f[k];

		for (int i = 0; i < k; i++)

			f[i] = f[i] - A[i][k] * x_0[k];

	}

	for (int i = 0; i < 4; i++) {

		std::cout << "[" << std::setprecision(7) << x_0[i] << "]" << std::endl;

	}

}

int main() {

	setlocale(LC_ALL, "Russian");
	std::array<std::array<double, 4>, 4> A = { 7.4,2.2,-3.1,-0.7,1.6,4.8,-8.5,4.5, 4.7,7.0,-6.0,6.6 ,5.9,2.7,4.9,-6.3 };
	std::array<double, 4> f = { 2,4,6,8 };

	std::cout << "Метод наискорейшего спуска:" << std::endl;

	Fastest_Decent(A, f);

	std::cout << "Метод Гаусса:" << std::endl;

	Gauss(A, f);
	system("pause");
	return 0;

}

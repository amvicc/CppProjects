#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
#include<ostream>
#include"fraction.h"

using namespace std;

template<typename T,int SIZE>
class Matrix
{
private:

	int size = SIZE;

public:

	T _matrix[SIZE][SIZE];

	Matrix();

	Matrix(T number);

	T determinant() {

		T t;
		T det(1);
		Matrix<T, SIZE> res = *this;

		for (int j = 0; j < size - 1; j++) {

			for (int i = j + 1; i < size; i++) {

				if (res._matrix[i][j] == NumberConstraint<T>::Zero) continue;
				if (res._matrix[j][j] == NumberConstraint<T>::Zero) {

					for (int l = 0; l < size; l++)
						res._matrix[j][l] = res._matrix[j][l] + res._matrix[i][l];
				}

				t = -(res._matrix[i][j] / res._matrix[j][j]);

				for (int l = 0; l < size; l++)
					res._matrix[i][l] = res._matrix[i][l] + (t*res._matrix[j][l]);
			}
		}

		for (int i = 0; i < size; i++)
			det *= res._matrix[i][i];

		return det;

	}

	Matrix<T, SIZE> transpose() {

		Matrix<T, SIZE> res;

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				res._matrix[i][j] = _matrix[j][i];

		return res;

	}

	std::string ToString() const {

		std::stringstream stream;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				stream << '[';
				stream << _matrix[i][j];
				stream << ']';
			}
			if(i!=size-1)stream << "||";
		}

		return stream.str();

	}

	Matrix<T, SIZE - 1> AlgMatrix(int a, int b) {

		Matrix<T, SIZE - 1> res;
		int x(0), y(0);

		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				if (i == a || j == b) continue;
				res._matrix[x][y++] = _matrix[i][j];
				if (y == size - 1)
				{
					y = 0;
					x++;
				}
			}
		}
		return res;
	}

	Matrix<T, SIZE> reverse() {

		Matrix<T, SIZE> res;

		T det = determinant();

		if (det == NumberConstraint<T>::Zero)
			throw runtime_error("No reverce matirx");
		else
		{
			for (int i = 0; i < size; i++) {

				for (int j = 0; j < size; j++) {

					Matrix<T, SIZE - 1> tmp(this->AlgMatrix(i, j));
					if (std::pow(-1, (i + j + 2)) < 0)
						res._matrix[i][j] = -tmp.determinant();
					else res._matrix[i][j] = tmp.determinant();
				}
			}
			res = res.transpose();
			res *= 1.0 / det;
			return res;
		}

	}

	Matrix<T, SIZE>& operator=(const Matrix<T, SIZE>& right) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				_matrix[i][j] = right._matrix[i][j];

		return *this;
	}

	Matrix<T, SIZE>& operator+=(Matrix<T, SIZE>& right) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				_matrix[i][j] += right._matrix[i][j];

		return *this;
	}

	Matrix<T, SIZE> operator+(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = *this;
		return res += right;
	}

	Matrix<T, SIZE>& operator*=(T number) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				_matrix[i][j] += number;

		return *this;
	}

	friend Matrix<T, SIZE> operator*(Matrix<T, SIZE>& left, T number) {

		Matrix<T, SIZE> res = left;
		return res *= number;
	}

	friend Matrix<T, SIZE> operator*(T number, Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = right;
		return res *= number;
	}

	Matrix<T, SIZE>& operator*=(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				res._matrix[i][j] = 0;


		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				for (int k = 0; k < size; k++)
					res._matrix[i][j] += _matrix[i][k] * right._matrix[k][j];

		return *this = res;

	}

	Matrix<T, SIZE> operator*(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = *this;
		return res *= right;
	}

	Matrix<T, SIZE>& operator/=(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = right;
		res = res.reverse();
		return *this *= res;

	}

	Matrix<T, SIZE> operator/(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = *this;
		return res /= right;

	}

	Matrix<T, SIZE> operator-() {

		Matrix<T, SIZE> res;

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				res._matrix[i][j] = -_matrix[i][j];

		return res;

	}

	Matrix<T, SIZE>& operator-=(Matrix<T, SIZE>& right) {

		return *this += -right;
	}

	bool operator>(Matrix<T, SIZE>& right) { return true; }

	Matrix<T, SIZE> operator-(Matrix<T, SIZE>& right) {

		Matrix<T, SIZE> res = *this;
		return res += -right;
	}

	bool operator==(Matrix<T, SIZE> right) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				if (_matrix[i][j] != right._matrix[i][j])return false;
			}
		return true;
	}

	bool operator!=(Matrix<T, SIZE> right) {
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (_matrix[i][j] != right._matrix[i][j])return true;
			}
		return false;
	}

	template<class Stream>
	friend Stream& operator >> (Stream&stream, Matrix<T, SIZE>&ob)
	{
		ob = Matrix<T, SIZE>();
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				stream >> ob._matrix[i][j];

		return stream;
	}

	template<class Stream>
	friend Stream& operator << (Stream&stream, Matrix<T, SIZE>&ob) {
 
		stream << ob.ToString();
		return stream;
	}

	~Matrix();
};

template<typename T, int SIZE>
inline Matrix<T, SIZE>::Matrix()
{

}

template<typename T, int SIZE>
inline Matrix<T, SIZE>::Matrix(T number)
{
	T res(0);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (i == j) 
			{
				_matrix[i][j] = number;
			}
			else _matrix[i][j] = res;
		}
}

template<typename T, int SIZE>
inline Matrix<T, SIZE>::~Matrix()
{
}

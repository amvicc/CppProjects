// Lab2.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "Matrix.h"
#include"fraction.h"
#include"polynom.h"

using namespace std;
int main()
{
	polynom<Matrix<Fraction<int>, 2>> poly1,poly2,poly3;
	Matrix<Fraction<int>, 2> Mat;

	cin >> poly1>> poly2;

	//cout << poly1 - poly1;

	//cout << poly1 - poly2;

	cout << poly1.superPosition(poly2) << endl;

	/*cout << poly1 / poly2 << endl;
	cout << poly1 % poly2 << endl;
	cout << poly1 + poly2 << endl;
	cout << poly1 - poly2 << endl;
	cout << poly1 * poly2 << endl;

	cout << poly1.superPosition(poly2) << endl;

	cin >> Mat;
	
	cout << poly1.valueinPoint(Mat);*/

	system("pause");
    return 0;
}


#pragma once
#include<iostream>
#include<string>
#include<map>
#include<sstream>
#include<ostream>

using namespace std;

template<typename T>
class polynom
{
private:
	std::map<int, T> _polynom;
public:

	size_t size;

	explicit polynom(int _size = 0) :size(_size) {};
	polynom(const polynom<T> & ob);

	void setMonom(int pow, T coef);
	void simplify();

	T valueinPoint(T point);
	polynom<T> differential();
	polynom<T> superPosition(const polynom<T> & ob) const;

	string ToString();

	polynom<T> operator -() const;

	polynom<T>& operator+=(const polynom<T> & right);
	polynom<T>& operator-=(const polynom<T> & right);
	polynom<T>& operator*=(const polynom<T> & right);
	polynom<T>& operator/=(const polynom<T> & right);
	polynom<T>& operator%=(const polynom<T> & right);

	polynom<T> operator+(const polynom<T> & right);
	polynom<T> operator-(const polynom<T> & right);
	polynom<T> operator*(const polynom<T> & right);
	polynom<T> operator/(const polynom<T> & right);
	polynom<T> operator%(const polynom<T> & right);

	polynom<T> RaiseDegree(int degree) const;

	template<class Stream>
	friend Stream& operator << (Stream &stream, polynom<T> &ob)
	{
		return stream << ob.ToString();
	}

	template<class Stream>
	friend Stream& operator >> (Stream&stream, polynom<T> &ob)
	{
		T tmp;
		int pow;

		size_t obSize;

		if (ob.size == 0) 
		{
			cout << "Enter number of Monoms";
			cin >> obSize; getchar();
			ob.size = obSize;
		}

		for (int i = 0; i < ob.size; i++)
		{
			cout << "Enter koef: ";
			stream >> tmp;
			cout << "Enter degree: ";
			stream >> pow; getchar();
			ob.setMonom(pow, tmp);
		}

		return stream;
	}


	~polynom();
};

template<typename T>
inline polynom<T>::polynom(const polynom<T>& ob)
{
	size = ob.size;
	for (auto it : ob._polynom)
		_polynom[it.first] = it.second;
}

template<typename T>
inline void polynom<T>::setMonom(int pow, T coef)
{
	if (_polynom.count(pow)) _polynom[pow] += coef;
	else _polynom[pow] = coef;
}

template<typename T>
inline void polynom<T>::simplify()
{
	for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
		if (it->second == T(0))
		{
			_polynom.erase(it);
			simplify();
			break;
		}

	if (_polynom.size() == 0) _polynom[0] = T(0);
}

template<typename T>
inline T polynom<T>::valueinPoint(T point)
{
	T res(0);

	for (auto it : _polynom)
	{	
		T tmp(1);
		for (int i = 0; i < abs(it.first); i++) tmp *= point;
		res += (it.second*tmp);
	}

	return res;
}

template<typename T>
inline polynom<T> polynom<T>::differential()
{
	polynom<T> res(size);

	for (const auto& it : _polynom)
		if (it.first != 0)
		{
			res._polynom[it.first - 1] = (it.second * it.first);
		}

	return res;
}

template<typename T>
inline polynom<T> polynom<T>::superPosition(const polynom<T>& ob) const
{
	polynom<T> result(ob.size),tmp(ob.size),mon(ob.size);
	for (auto & it : this->_polynom)
	{
		tmp._polynom.clear();
		mon._polynom.clear();
		mon.setMonom(0,it.second);

		if (it.first > 0) 
		{
			tmp = ob;
			for (unsigned i = 1; i < it.first; i++)tmp *= ob;
			mon *= tmp;
			result += mon;
		}
		else
		{
			result += mon;
		}
	}
	return result;
}

template<typename T>
inline string polynom<T>::ToString()
{
	stringstream stream;

	simplify();

	stream << '<';

	if (_polynom.size() > 0)
		for (auto it = _polynom.rbegin(); it != _polynom.rend(); ++it)
		{
			if (it == _polynom.rbegin())
			{
				if (it->second != T(1))stream << (T)it->second;
				if (it->first == 1)
				{
					if (it->first) stream << "x";
				}
				else
				{
					if (it->first) stream << "x^" << it->first;
				}
			}
			else
			{
				if ((T)it->second > T(0)) stream << '+';

				if (it->second != T(1))stream << (T)it->second;
				if (it->first == 1)
				{
					if (it->first) stream << "x";
				}
				else
				{
					if (it->first) stream << "x^" << it->first;
				}

			}
		}

	stream << '>';
	return stream.str();
}

template<typename T>
inline polynom<T> polynom<T>::operator-() const
{
	polynom<T> res = *this;
	for (auto it = res._polynom.begin(); it != res._polynom.end(); ++it)
		it->second = -it->second;

	return res;
}

template<typename T>
inline polynom<T>& polynom<T>::operator+=(const polynom<T>& right)
{
	for (auto it = right._polynom.begin(); it != right._polynom.end(); ++it)
	{
		if (_polynom.count(it->first)) _polynom[it->first] += (T)it->second;
		else _polynom[it->first] = it->second;
	}

	return *this;
}

template<typename T>
inline polynom<T>& polynom<T>::operator-=(const polynom<T>& right)
{
	return *this += -right;
}

template<typename T>
inline polynom<T>& polynom<T>::operator*=(const polynom<T>& right)
{
	polynom<T> res(size);

	for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
	{
		for (auto _it = right._polynom.begin(); _it != right._polynom.end(); ++_it)
		{
			if (res._polynom.count((it->first + _it->first))) res._polynom[it->first + _it->first] += ((T)it->second * (T)_it->second);
			else res._polynom[(it->first + _it->first)] = (T)it->second * (T)_it->second;
		}
	}

	return *this = res;
}

template<typename T>
inline polynom<T>& polynom<T>::operator/=(const polynom<T>& right)
{
	polynom<T> remainder(*this), result(size);

	pair<int, T> max_mon_this = (remainder._polynom.empty() ? pair<int, T>(0, T(0)) : *(remainder._polynom.rbegin()));
	pair<int, T> max_mon_obj = (right._polynom.empty() ? pair<int, T>(0, T(0)) : *(right._polynom.rbegin()));
	T zero(0);

	while (max_mon_this.first >= max_mon_obj.first) {

		if (max_mon_obj.second == zero) {
			throw std::runtime_error("division by zero");
		}

		max_mon_this.first -= max_mon_obj.first;
		max_mon_this.second /= max_mon_obj.second;

		if (max_mon_this.second == zero) {
			break;
		}

		result.setMonom(max_mon_this.first, max_mon_this.second);

		polynom<T> tmp_polynom(size);
		tmp_polynom.setMonom(max_mon_this.first, max_mon_this.second);

		tmp_polynom *= right;
		remainder -= tmp_polynom;

		remainder.simplify();
		max_mon_this = (remainder._polynom.empty() ? pair<int, T>(0, T(0)) : *(remainder._polynom.rbegin()));
	}

	return *this = result;
}

template<typename T>
inline polynom<T>& polynom<T>::operator%=(const polynom<T>& right)
{
	polynom<T> res = right;

	return *this = *this - *this / res*res;
}

template<typename T>
inline polynom<T> polynom<T>::operator+(const polynom<T>& right)
{
	polynom<T> res = *this;
	return res += right;
}

template<typename T>
inline polynom<T> polynom<T>::operator-(const polynom<T>& right)
{
	polynom<T> res = *this;
	return res -= right;
}

template<typename T>
inline polynom<T> polynom<T>::operator*(const polynom<T>& right)
{
	polynom<T> res = *this;
	return res *= right;
}

template<typename T>
inline polynom<T> polynom<T>::operator/(const polynom<T>& right)
{
	polynom<T> res = *this;
	return res /= right;
}

template<typename T>
inline polynom<T> polynom<T>::operator%(const polynom<T>& right)
{
	polynom<T> res = *this;
	return res %= right;
}

template<typename T>
inline polynom<T> polynom<T>::RaiseDegree(int degree) const
{
	polynom<T> result(*this);

	if (degree > 1) 
	{
		for (size_t i = 1; i < degree; i++) {
			result *= *this;
		}
	}
	else if (degree == 1) 
	{
		return result;
	}
	else if (degree == 0) 
	{
		result._polynom.clear();
		result._polynom[0] = T(1);
	}

	return result;
}

template<typename T>
inline polynom<T>::~polynom()
{
}

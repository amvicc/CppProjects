#ifndef FRAC
#define FRAC

#include <cmath> 
#include <sstream>
#include <iostream>
#include <string>

template<class T>
class Fraction
{
	T numerator;
	T denominator;
public: 
	using CRef = const Fraction&;
	using Ref = Fraction&;

	explicit Fraction() : numerator(NumberConstraint<T>::One), denominator(NumberConstraint<T>::One) {};
	constexpr Fraction(T num) :numerator(num), denominator(NumberConstraint<T>::One) {  };
	Fraction(T num, T dem) : numerator(num)
	{
		if (dem == NumberConstraint<T>::Zero) {
			throw std::runtime_error("Denumerator equals to 0");
		}
		
		denominator = dem;
		simplify(); 
	}; 

	Fraction(std::string);

	Fraction(CRef);

	Fraction& operator=(CRef);
	Fraction<T>& operator=(T);

	Ref operator+=(CRef);
	Fraction operator+(CRef);

	Ref operator-=(CRef);
	Fraction operator-(CRef);

	Ref operator/=(CRef);
	Fraction operator/(CRef);

	Ref operator*=(CRef);
	Ref operator*=(T);
	Fraction operator*(CRef);
	Fraction operator*(T);

	T Compare(CRef) const;

	Fraction operator -() const {
		return Fraction(-numerator, denominator);
	}


	friend T& operator*=(T& k, const Fraction&ob)
	{
		return k *= (ob.numerator / ob.denominator);
	}

	friend Fraction operator/(T k, const Fraction&ob)
	{
		Fraction<T> res(ob.denominator*k, ob.numerator);
		return res;
	}

	std::string ToString() const;
private:
	void simplify();

	static T Lcm(T left, T right) {
		return left * (right / Gcd(left, right));
	}

	static T Gcd(T left, T right) {
		return left ? Gcd(fmod(right, left), left) : right;
	}

	inline T Multiply(T number) const {
		return (number / denominator) * numerator;
	}
};

template<class T>
inline Fraction<T>::Fraction(std::string strIn)
{
	std::string buf;
	bool flag = true;

	for each (char c in strIn)
	{
		if (c == '/')
		{
			numerator = atof(buf.c_str());
			buf.clear();
			flag = false;
		}
		else buf += c;
	}

	if (flag)
	{
		denominator = NumberConstraint<T>::One;
		numerator = atof(buf.c_str());
	}
	else denominator = atof(buf.c_str());
}

template<class T>
inline Fraction<T>::Fraction(CRef ob)
{
	numerator = ob.numerator;
	denominator = ob.denominator;
}

template<class T>
inline Fraction<T>& Fraction<T>::operator=(CRef ob)
{
	numerator = ob.numerator;
	denominator = ob.denominator;
	return *this;
}

template<class T>
inline Fraction<T> & Fraction<T>::operator=(T num)
{
	numerator = num;
	denominator = 1;

	return *this;
}

template<class T>
inline Fraction<T> &Fraction<T>::operator+=(CRef ob)
{
	T multiplier = Lcm(denominator, ob.denominator);

	numerator = Multiply(multiplier) + ob.Multiply(multiplier);
	denominator = multiplier;
	simplify();

	return *this;
}

template<class T>
inline Fraction<T> Fraction<T>::operator+(CRef ob)
{
	Fraction<T> res(numerator, denominator);
	return res += ob;
}

template<class T>
inline Fraction<T>& Fraction<T>::operator-=(CRef ob)
{
	return (*this) += -ob;
}

template<class T>
inline Fraction<T> Fraction<T>::operator-(CRef ob)
{
	Fraction<T> res(numerator, denominator);
	return res -= ob;
}

template<class T>
inline Fraction<T>& Fraction<T>::operator/=(CRef ob)
{
	numerator *= ob.denominator;
	denominator *= ob.numerator;
	if (denominator == NumberConstraint<T>::Zero) throw std::runtime_error("Denumerator equals to 0");

	simplify();
	return *this;
}

template<class T>
inline Fraction<T> Fraction<T>::operator/(CRef ob)
{
	Fraction<T> res(numerator, denominator);
	return res /= ob;
}

template<class T>
inline Fraction<T>& Fraction<T>::operator*=(CRef ob)
{
	numerator *= ob.numerator;
	denominator *= ob.denominator;
	simplify();
	return *this;
}

template<class T>
inline Fraction<T>& Fraction<T>::operator*=(T k)
{
	numerator *= k;
	simplify();
	return *this;
}

template<class T>
inline Fraction<T> Fraction<T>::operator*(CRef ob)
{
	Fraction<T> res(numerator, denominator);
	return res *= ob;
}

template<class T>
inline Fraction<T> Fraction<T>::operator*(T k)
{
	Fraction<T> res(numerator, denominator);
	res.numerator *= k;
	return res;
}

template<class T>
inline T Fraction<T>::Compare(CRef ob) const
{
	if (denominator == ob.denominator) {
		return numerator - ob.numerator;
	}

	auto number = Lcm(denominator, ob.denominator);
	return this->Multiply(number) - ob.Multiply(number);
}

template<class T>
inline std::string Fraction<T>::ToString() const
{
	std::stringstream stream;
	stream << numerator;
	if (denominator != NumberConstraint<T>::One)
	stream << "/" << denominator;

	return stream.str();
}

template<class T>
inline void Fraction<T>::simplify()
{
	auto d = Gcd(::abs(numerator), denominator);

	numerator /= d;
	denominator /= d;

	if (numerator < 0 && denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
}

template<class T>
std::ostream & operator << (std::ostream & stream, const Fraction<T> & ob)
{
	return stream << ob.ToString();
}

template <typename T>
bool operator==(const Fraction<T> & left, const Fraction<T> & right) {
	return left.Compare(right) == NumberConstraint<T>::Zero;
}

template <typename T>
bool operator!=(const Fraction<T> & left, const Fraction<T> & right) {
	return !(left == right);
}

template <typename T>
bool operator>(const Fraction<T> & left, const Fraction<T> & right) {
	return left.Compare(right) > NumberConstraint<T>::Zero;
}

template <typename T>
bool operator<(const Fraction<T> & left, const Fraction<T> & right) {
	return left.Compare(right) < NumberConstraint<T>::Zero;
}

template <typename T>
bool operator>=(const Fraction<T> & left, const Fraction<T> & right) {
	return !(left < right);
}

template <typename T>
bool operator<=(const Fraction<T> & left, const Fraction<T> & right) {
	return !(left > right);
}

template<class  T>
struct NumberConstraint
{};

template<>
struct NumberConstraint<double>
{
	static constexpr double One = 1.0;
	static constexpr double Zero = 0.0;
};

template<>
struct NumberConstraint<float>
{
	static constexpr float One = 1.0;
	static constexpr float Zero = 0.0;
};

template<>
struct NumberConstraint<int>
{
	static constexpr int One = 1;
	static constexpr int Zero = 0;
};

template<>
struct NumberConstraint<long>
{
	static constexpr long One = 1;
	static constexpr long Zero = 0;
};

template<>
struct NumberConstraint<unsigned char>
{
	static constexpr unsigned char One = 1;
	static constexpr unsigned char Zero = 0;
};

template<typename T>
struct NumberConstraint<Fraction<T>>
{
	static const constexpr Fraction<T> One = Fraction<T>(NumberConstraint<T>::One);
	static const constexpr Fraction<T> Zero = Fraction<T>(NumberConstraint<T>::Zero);
};

template<typename Stream, class T>
Stream& operator >> (Stream&stream, Fraction<T> &ob)
{
	std::string strIn, buf;
	std::getline(stream, strIn);

	ob = Fraction<T>(strIn);

	return stream;
}

template<typename Stream, class T>
Stream& operator << (Stream&stream, Fraction<T> &ob)
{
	return stream << ob.ToString();
}

#endif
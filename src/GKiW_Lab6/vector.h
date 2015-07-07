#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

/*
VECTOR.H

scalar_t
CVector


Copyright (c) 2000 Bas Kuenen.
baskuenen.cfxweb.net
*/

typedef float scalar_t;  // skalar


// klasa CVector
// specjalne podziêkowania dla Basa Kuenena za koncepcje wykorzystania operatorów

class CVector
{
public:
	scalar_t x;
	scalar_t y;
	scalar_t z;    // sk³adowe x,y,z 

public:
	// konstruktor
	CVector(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b), z(c) {}
	CVector(const CVector &vec) : x(vec.x), y(vec.y), z(vec.z) {}

	// podstawienie wektora
	const CVector &operator=(const CVector &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	// równoœæ wektorów
	const bool operator==(const CVector &vec) const
	{
		return ((x == vec.x) && (y == vec.y) && (z == vec.z));
	}

	// nierównoœæ wektorów
	const bool operator!=(const CVector &vec) const
	{
		return !(*this == vec);
	}

	// dodawanie wektorów
	const CVector operator+(const CVector &vec) const
	{
		return CVector(x + vec.x, y + vec.y, z + vec.z);
	}

	// dodawanie wektorów
	const CVector operator+() const
	{
		return CVector(*this);
	}

	// dodawanie wektorów
	const CVector& operator+=(const CVector& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	// odejmowanie wektorów
	const CVector operator-(const CVector& vec) const
	{
		return CVector(x - vec.x, y - vec.y, z - vec.z);
	}

	// odejmowanie wektorów
	const CVector operator-() const
	{
		return CVector(-x, -y, -z);
	}

	// odejmowanie wektorów
	const CVector &operator-=(const CVector& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	// mno¿enie wektora przez skalar
	const CVector &operator*=(const scalar_t &s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	// dzielenie wektora przez skalar
	const CVector &operator/=(const scalar_t &s)
	{
		const float recip = 1 / s; // dla efektywnoœci

		x *= recip;
		y *= recip;
		z *= recip;

		return *this;
	}

	// mno¿enie wektora przez skalar
	const CVector operator*(const scalar_t &s) const
	{
		return CVector(x*s, y*s, z*s);
	}

	// mno¿enie wektora przez skalar
	friend inline const CVector operator*(const scalar_t &s, const CVector &vec)
	{
		return vec*s;
	}

	/*   friend inline const CVector operator*(const CVector &vec, const scalar_t &s)
	{
	return CVector(vec.x*s, vec.y*s, vec.z*s);
	}

	*/   // dzielenie wektora przez skalar
	const CVector operator/(scalar_t s) const
	{
		s = 1 / s;

		return CVector(s*x, s*y, s*z);
	}

	// iloczyn wektorowy
	const CVector CrossProduct(const CVector &vec) const
	{
		return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// iloczyn wektorowy
	const CVector operator^(const CVector &vec) const
	{
		return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// iloczyn skalarny
	const scalar_t DotProduct(const CVector &vec) const
	{
		return x*vec.x + y*vec.x + z*vec.z;
	}

	// iloczyn skalarny
	const scalar_t operator%(const CVector &vec) const
	{
		return x*vec.x + y*vec.x + z*vec.z;
	}


	// d³ugoœæ wektora
	const scalar_t Length() const
	{
		return (scalar_t)sqrt((double)(x*x + y*y + z*z));
	}

	// wektor jednostkowy
	const CVector UnitVector() const
	{
		return (*this) / Length();
	}

	// normalizacja wektora
	void Normalize()
	{
		(*this) /= Length();
	}

	// operator modu³u (d³ugoœci) wektora
	const scalar_t operator!() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	// zmienia d³ugoœæ wektora
	const CVector operator | (const scalar_t length) const
	{
		return *this * (length / !(*this));
	}

	// zmienia d³ugoœæ wektora
	const CVector& operator |= (const float length)
	{
		return *this = *this | length;
	}

	// zwraca k¹t, który tworz¹ wektory
	const float inline Angle(const CVector& normal) const
	{
		return acosf(*this % normal);
	}

	// tworzy odbicie wektora wzglêdem powierzchni zdefiniowanej przez normaln¹
	const CVector inline Reflection(const CVector& normal) const
	{
		const CVector vec(*this | 1);     // normalizuje wektor
		return (vec - normal * 2.0 * (vec % normal)) * !*this;
	}

};

#endif
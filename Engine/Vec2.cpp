#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float in_x, float in_y)
	:
	x(in_x),
    y(in_y)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2( x + rhs.x , y + rhs.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator+(const float rhs)
{
	return Vec2( x + rhs , y + rhs );
}

Vec2& Vec2::operator-=(const Vec2 & rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator-(const float rhs )
{
	return Vec2( x - rhs , y - rhs );
}

Vec2 Vec2::operator*(const float rhs) const
{
	return Vec2( x * rhs, y * rhs);
}

Vec2 & Vec2::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator/(const float rhs) const
{
	return Vec2( x / rhs , y / rhs);
}

Vec2 & Vec2::operator/=(const float rhs)
{
	return *this = *this / rhs;
}

float Vec2::Getlenghtsq() const
{
	return x*x + y*y;
}

float Vec2::Getlength() const
{
	return std::sqrt( Getlenghtsq() );
}

Vec2 Vec2::Getnormalized() const
{
	const float length = Getlength();
	if (length != 0.0f)
	{
		return *this * (1.0f / length );
	}
	else
	{
		return *this;
	}
}

Vec2 & Vec2::Normalized()
{
	return *this = Getnormalized();
}

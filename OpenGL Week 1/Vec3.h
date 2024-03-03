#pragma once

class Vec3
{
public:
	Vec3()
	{

	}
	Vec3(float x, float y, float z) : x(x), y(y), z(z)
	{

	}
	~Vec3()
	{

	}

	Vec3 operator +=(const Vec3& vec)
	{
		*this = Vec3(x + vec.x, y + vec.y, z + vec.z);
		return *this;
	}
	Vec3 operator *(float num) const
	{
		return Vec3(x * num, y * num, z * num);
	}
	Vec3 operator +(const Vec3& vec) const
	{
		return Vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vec3 operator -(const Vec3& vec) const
	{
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}



public:
	float x = 0, y = 0, z = 0;
};

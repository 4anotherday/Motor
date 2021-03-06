#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <tuple>
#include <cmath>

#define PI 3.14159265 

class Vector3 {
public:

	Vector3();
	Vector3(const Vector3& v);
	Vector3(double x, double y, double z);
	Vector3(const std::tuple<float, float, float>& tuple);

	~Vector3();
		
	/// <summary>
	/// Returns the x component of the vector3
	/// </summary>
	inline double getX() const { return _x; }

	/// <summary>
	/// Sets a new x component to the vector3
	/// </summary>
	/// <param name="x">New x component</param>
	inline void setX(double x) { _x = x; }

	/// <summary>
	/// Returns the y component of the vector3
	/// </summary>
	inline double getY() const { return _y; }

	/// <summary>
	/// Sets a new y component to the vector3
	/// </summary>
	/// <param name="x">New y component</param>
	inline void setY(double y) { _y = y; }

	/// <summary>
	/// Returns the z component of the vector3
	/// </summary>
	inline double getZ() const { return _z; }

	/// <summary>
	/// Sets a new z component to the vector3
	/// </summary>
	/// <param name="x">New z component</param>
	inline void setZ(double z) { _z = z; }

	/// <summary>
	/// Sets a new vector3
	/// </summary>
	/// <param name="v">New vector</param>
	inline void set(const Vector3& v) { _x = v._x; _y = v._y; _z = v._z; }

	/// <summary>
	/// Sets a new x, y and z component
	/// </summary>
	/// <param name="x">New x component</param>
	/// <param name="y">New y component</param>
	/// <param name="z">New z component</param>
	inline void set(double x, double y, double z) { _x = x; _y = y; _z = z; }
		
	/// <summary>
	/// Returns the magnitude(length) of the vector3
	/// </summary>
	inline double magnitude() const { return sqrt(_x * _x + _y * _y + _z * _z); }

	/// <summary>
	/// Returns a vector3 with a magnitude of 1  
	/// </summary>
	Vector3 normalize() const;

	/// <summary>
	/// Returns a tuple
	/// </summary>
	/// <returns></returns>
	inline std::tuple<float, float, float> toTuple() const { return { _x, _y, _z }; }

	/// <summary>
	/// Returns the inverse vector
	/// </summary>
	/// <returns></returns>
	inline Vector3 inverse() const { return Vector3(1 / _x, 1 / _y, 1 / _z); }
	
	/// Returns a radian angle between this vector and other
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float angleRadiansBetweenVector(const Vector3& other) const { return std::acos((_x * other._x + _y * other._y + _z * other._z) / (magnitude() * other.magnitude())); }

	/// <summary>
	/// Returns a degree angle between this vector and other
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float angleDegreesBetweenVector(const Vector3& other) const { return std::acos((_x * other._x + _y * other._y + _z * other._z) / (magnitude() * other.magnitude())) * 180 / PI; }

	/// <summary>
	/// Allows subtraction of vectors
	/// </summary>
	/// <param name="v">Vector to be subtracted</param>
	inline Vector3 operator-(const Vector3& v) const { return Vector3(_x - v._x, _y - v._y, _z - v._z); }

	/// <summary>
	/// Allows addition of vectors
	/// </summary>
	/// <param name="v">Vector to be added</param>
	inline Vector3 operator+(const Vector3& v) const { return Vector3(_x + v._x, _y + v._y, _z + v._z); }

	/// <summary>
	/// Allows to multiply vectors
	/// </summary>
	/// <param name="d">Number to be multiplied</param>
	inline Vector3 operator*(double d) const { return Vector3(_x * d, _y * d, _z * d); }

	/// <summary>
	/// Dot multiplication
	/// </summary>
	/// <param name="other">other vector</param>
	inline Vector3 operator*(const Vector3& other) const { return Vector3(_x * other._x, _y * other._y, _z * other._z); }

	/// <summary>
	/// Allows to divide vectors
	/// </summary>
	/// <param name="d">Number to be divided</param>
	inline Vector3 operator/(double d) const { return Vector3(_x / d, _y / d, _z / d); }

	/// <summary>
	/// Returns if two vectors are equal
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline bool operator==(const Vector3& other) const { return _x == other._x && _y == other._y && _z == other._z; }

	/// <summary>
	/// Returns if two vectors are equal
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline bool operator!=(const Vector3& other) const { return _x != other._x || _y != other._y || _z != other._z; }

private:	
	
	double _x, _y, _z;
};
#endif // !VECTOR3_H
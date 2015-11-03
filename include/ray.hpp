#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#if !(defined(tray) || defined(ray))
template <typename T> struct tray
{

	inline tray() : origin(0), direction(0), length((T)FLT_MAX) {}
	inline tray(const glm::tvec3<T>& v, const glm::tvec3<T>& forward) : origin(v), direction(forward), length((T)FLT_MAX) {}
	inline tray(const glm::tvec3<T>& v, const glm::tvec3<T>& forward, const T length) : origin(v), direction(forward), length(length) {}
	inline tray(const tray<T>& r) : origin(r.origin), direction(r.direction), length(r.length) {}
	inline ~tray() {}

	inline void operator=(const tray<T>& r)
	{
		this->origin = r.origin;
		this->direction = r.direction;
	}
	inline void operator+=(const tray<T>& r)
	{
		this->origin += r.origin;
		this->direction += r.direction;
	}
	inline void operator+=(const glm::tvec3<T>& v)
	{
		this->origin += v;
	}
	inline void operator-=(const tray<T>& r)
	{
		this->origin -= r.origin;
		this->direction -= r.direction;
	}
	inline void operator-=(const glm::tvec3<T>& v)
	{
		this->origin -= v;
	}
	inline void operator*=(const tray<T>& r)
	{
		this->origin *= r.origin;
		this->direction *= r.direction;
	}
	inline void operator*=(const glm::tvec3<T>& v)
	{
		this->origin *= v;
	}
	inline void operator/=(const tray<T>& r)
	{
		this->origin /= r.origin;
		this->direction /= r.direction;
	}
	inline void operator/=(const glm::tvec3<T>& v)
	{
		this->origin /= v;
	}
	inline bool operator==(const tray<T>& r)
	{
		return this->origin == r.origin && this->direction == r.direction;
	}
	inline bool operator!=(const tray<T>& r)
	{
		return this->origin != r.origin && this->direction != r.direction;
	}

	glm::tvec3<T> origin;
	glm::tvec3<T> direction;
	T length;

};

template <typename T> inline tray<T> operator+(const tray<T>& r1, const tray<T>& r2)
{
	return tray<T>(r1.origin + r2.origin, normalize(r1.direction + r2.direction), max(r1.length, r2.length));
}
template <typename T> inline tray<T> operator+(const tray<T>& r, const glm::tvec3<T>& v)
{
	return tray<T>(r.origin + v, r.direction, r.length);
}
template <typename T> inline tray<T> operator+(const glm::tvec3<T>& v, const tray<T>& r)
{
	return tray<T>(v + r.origin, r.direction, r.length);
}
template <typename T> inline tray<T> operator-(const tray<T>& r1, const tray<T>& r2)
{
	return tray<T>(r1.origin - r2.origin, normalize(r1.direction - r2.direction), min(r1.length, r2.length));
}
template <typename T> inline tray<T> operator-(const tray<T>& r, const glm::tvec3<T>& v)
{
	return tray<T>(r.origin - v, r.direction, r.length);
}
template <typename T> inline tray<T> operator-(const glm::tvec3<T>& v, const tray<T>& r)
{
	return tray<T>(v - r.origin, r.direction, r.length);
}

typedef tray<float> ray;
#endif

#endif
#ifndef GMATH_H
#define GMATH_H

#pragma message("ERROR: Do not use")

#include <math.h>
#include <float.h>
#include <string.h>

#include <fuzzy.hpp>
#include <ray.hpp>
#include <box.hpp>

namespace gmath
{

#if !defined(clamp)
template <typename T> inline T clamp(T x, T min = (T)0, T max = (T)1)
{
	if (x < min)
	{
		return min;
	}

	if (x > max)
	{
		return max;
	}

	return x;
}
#endif

#if !defined(module)
template <typename T> inline T module(T x, T denominator)
{
	while (x > denominator)
	{
		x -= denominator;
	}

	while (x < (T)0)
	{
		x += denominator;
	}

	return x;
}
#endif

#if !defined(sign)
template <typename T> inline T sign(T x) { return x > 0 ? (T)1 : (T)0; }
#endif

#if !defined(abs)
template <typename T> inline T abs(T x)
{
	if (x == (T)0)
	{
		return (T)0;
	}

	return (x * x) / x;
}
#endif

#if !defined(PI)
#define PI 3.14159265358979323846f
#endif

#if !defined(radians)
template <typename T> inline T radians(T angle) { return angle * ((T)PI / (T)180); }
#endif

#if !defined(degrees)
template <typename T> inline T degrees(T angle) { return angle * ((T)180 / (T)PI); }
#endif

#if !(defined(tvec2) || defined(tvec3) || defined(tvec4) || defined(vec2) || defined(vec3) || defined(vec4) || defined(ivec2) || defined(ivec3) || defined(ivec4))
template <typename T> struct tvec2;
template <typename T> struct tvec3;
template <typename T> struct tvec4;

template <typename T> struct tvec2
{

	inline tvec2() : x((T)0), y((T)0) {}
	inline tvec2(const T x) : x(x), y(x) {}
	inline tvec2(const T x, const T y) : x(x), y(y) {}
	inline tvec2(const tvec2<T>& v) : x(v.x), y(v.y) {}
	inline tvec2(const tvec3<T>& v) : x(v.x), y(v.y) {}
	inline tvec2(const tvec4<T>& v) : x(v.x), y(v.y) {}
	inline ~tvec2() {}

	template <typename U> inline tvec2(const tvec2<U>& v) : x((T)v.x), y((T)v.y) {}
	template <typename U> inline tvec2(const tvec3<U>& v) : x((T)v.x), y((T)v.y) {}
	template <typename U> inline tvec2(const tvec4<U>& v) : x((T)v.x), y((T)v.y) {}

	inline const int length() const
	{
		return 2;
	}

	inline void operator=(const tvec2<T>& v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	inline operator T*() const
	{
		return (T*)this;
	}
	inline tvec2<T> operator+() const
	{
		return tvec2<T>(+this->x, +this->y);
	}
	inline tvec2<T> operator-() const
	{
		return tvec2<T>(-this->x, -this->y);
	}
	inline void operator+=(const tvec2<T>& v)
	{
		this->x += v.x;
		this->y += v.y;
	}
	inline void operator+=(const T& x)
	{
		this->x += x;
		this->y += x;
	}
	inline void operator-=(const tvec2<T>& v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}
	inline void operator-=(const T& x)
	{
		this->x -= x;
		this->y -= x;
	}
	inline void operator*=(const tvec2<T>& v)
	{
		this->x *= v.x;
		this->y *= v.y;
	}
	inline void operator*=(const T& x)
	{
		this->x *= x;
		this->y *= x;
	}
	inline void operator/=(const tvec2<T>& v)
	{
#if 0
		this->x = v.x != (T)0 ? this->x / v.x : (T)0;
		this->y = v.y != (T)0 ? this->y / v.y : (T)0;
#else
		this->x /= v.x;
		this->y /= v.y;
#endif
	}
	inline void operator/=(const T& x)
	{
#if 0
		this->x = x != (T)0 ? this->x / x : (T)0;
		this->y = y != (T)0 ? this->y / x : (T)0;
#else
		this->x /= x;
		this->y /= x;
#endif
	}
	inline void operator%=(const tvec2<T>& v)
	{
		return tvec2<T>(module(this->x, v.x), module(this->y, v.y));
	}
	inline void operator%=(const T& x)
	{
		return tvec2<T>(module(this->x, x), module(this->y, x));
	}
	inline bool operator==(const tvec2<T>& v) const
	{
		return (this->x == v.x) && (this->y == v.y);
	}
	inline bool operator!=(const tvec2<T>& v) const
	{
		return (this->x != v.x) && (this->y != v.y);
	}
	inline bool operator>(const tvec2<T>& v) const
	{
		return (this->x > v.x) && (this->y > v.y);
	}
	inline bool operator<(const tvec2<T>& v) const
	{
		return (this->x < v.x) && (this->y < v.y);
	}
	inline bool operator>=(const tvec2<T>& v) const
	{
		return (this->x >= v.x) && (this->y >= v.y);
	}
	inline bool operator<=(const tvec2<T>& v) const
	{
		return (this->x <= v.x) && (this->y <= v.y);
	}
	inline tvec2<T> operator&&(const tvec2<T>& v) const
	{
		return tvec2<T>(min(this->x, v.x), min(this->y, v.y));
	}
	inline tvec2<T> operator||(const tvec2<T>& v) const
	{
		return tvec2<T>(max(this->x, v.x), max(this->y, v.y));
	}
	inline T& operator[](const int index)
	{
		return ((T*)this)[index % this->length()];
	}

	union
	{
		T x, u, s, r;
	};

	union
	{
		T y, v, t, g;
	};

};

template <typename T> struct tvec3
{

	inline tvec3() : x((T)0), y((T)0), z((T)0) {}
	inline tvec3(const T x) : x(x), y(x), z(x) {}
	inline tvec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}
	inline tvec3(const tvec2<T>& v, const T z) : x(v.x), y(v.y), z(z) {}
	inline tvec3(const T x, const tvec2<T>& v) : x(x), y(v.x), z(v.y) {}
	inline tvec3(const tvec3<T>& v) : x(v.x), y(v.y), z(v.z) {}
	inline tvec3(const tvec4<T>& v) : x(v.x), y(v.y), z(v.z) {}
	inline ~tvec3() {}

	template <typename U> inline tvec3(const tvec3<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z) {}
	template <typename U> inline tvec3(const tvec4<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z) {}

	inline const int length() const
	{
		return 3;
	}

	inline void operator=(const tvec3<T>& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	inline operator T*() const
	{
		return (T*)this;
	}
	inline tvec3<T> operator+() const
	{
		return tvec3<T>(+this->x, +this->y, +this->z);
	}
	inline tvec3<T> operator-() const
	{
		return tvec3<T>(-this->x, -this->y, -this->z);
	}
	inline void operator+=(const tvec3<T>& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}
	inline void operator+=(const T x)
	{
		this->x += x;
		this->y += x;
		this->z += x;
	}
	inline void operator-=(const tvec3<T>& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}
	inline void operator-=(const T x)
	{
		this->x -= x;
		this->y -= x;
		this->z -= x;
	}
	inline void operator*=(const tvec3<T>& v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
	}
	inline void operator*=(const T x)
	{
		this->x *= x;
		this->y *= x;
		this->z *= x;
	}
	inline void operator/=(const tvec3<T>& v)
	{
#if 1
		this->x = v.x != (T)0 ? this->x / v.x : (T)0;
		this->y = v.y != (T)0 ? this->y / v.y : (T)0;
		this->z = v.z != (T)0 ? this->z / v.z : (T)0;
#else
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
#endif
	}
	inline void operator/=(const T x)
	{
#if 0
		this->x = x != (T)0 ? this->x / x : (T)0;
		this->y = x != (T)0 ? this->y / x : (T)0;
		this->z = x != (T)0 ? this->z / x : (T)0;
#else
		this->x /= x;
		this->y /= x;
		this->z /= x;
#endif
	}
	inline void operator%=(const tvec3<T>& v)
	{
		return tvec3<T>(module(this->x, v.x), module(this->y, v.y), module(this->z, v.z));
	}
	inline void operator%=(const T& x)
	{
		return tvec3<T>(module(this->x, x), module(this->y, x), module(this->z, x));
	}
	inline bool operator==(const tvec3<T>& v) const
	{
		return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
	}
	inline bool operator!=(const tvec3<T>& v) const
	{
		return (this->x != v.x) && (this->y != v.y) && (this->z != v.z);
	}
	inline bool operator>(const tvec3<T>& v) const
	{
		return (this->x > v.x) && (this->y > v.y) && (this->z > v.z);
	}
	inline bool operator<(const tvec3<T>& v) const
	{
		return (this->x < v.x) && (this->y < v.y) && (this->z < v.z);
	}
	inline bool operator>=(const tvec3<T>& v) const
	{
		return (this->x >= v.x) && (this->y >= v.y) && (this->z >= v.z);
	}
	inline bool operator<=(const tvec3<T>& v) const
	{
		return (this->x <= v.x) && (this->y <= v.y) && (this->z <= v.z);
	}
	inline tvec3<T> operator&&(const tvec3<T>& v) const
	{
		return tvec3<T>(min(this->x, v.x), min(this->y, v.y), min(this->z, v.z));
	}
	inline tvec3<T> operator||(const tvec3<T>& v) const
	{
		return tvec3<T>(max(this->x, v.x), max(this->y, v.y), max(this->z, v.z));
	}
	inline T& operator[](const int index)
	{
		return ((T*)this)[index % this->length()];
	}

	union
	{
		T x, u, s, r;
	};

	union
	{
		T y, v, t, g;
	};

	union
	{
		T z, p, b;
	};

};

template <typename T> struct tvec4
{

	inline tvec4() : x((T)0), y((T)0), z((T)0), w((T)0) {}
	inline tvec4(const T x) : x(x), y(x), z(x), w(x) {}
	inline tvec4(const T x, const T y, const T z, const T w) : x(x), y(y), z(z), w(w) {}
	inline tvec4(const tvec2<T>& v, const T z, const T w) : x(v.x), y(v.y), z(z), w(w) {}
	inline tvec4(const T x, const tvec2<T>& v, const T w) : x(x), y(v.x), z(v.y), w(w) {}
	inline tvec4(const T x, const T y, const tvec2<T>& v) : x(x), y(y), z(v.x), w(v.y) {}
	inline tvec4(const tvec2<T>& v0, const tvec2<T>& v1) : x(v0.x), y(v0.y), z(v1.x), w(v1.y) {}
	inline tvec4(const tvec3<T>& v, const T w) : x(v.x), y(v.y), z(v.z), w(w) {}
	inline tvec4(const T x, const tvec3<T>& v) : x(x), y(v.x), z(v.y), w(v.z) {}
	inline tvec4(const tvec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	inline ~tvec4() {}

	template <typename U> inline tvec4(const tvec4<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z), w((T)v.w) {}

	inline const int length() const
	{
		return 4;
	}

	inline void operator=(const tvec4<T>& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;
	}
	inline operator T*() const
	{
		return (T*)this;
	}
	inline tvec4<T> operator+() const
	{
		return tvec4<T>(+this->x, +this->y, +this->z, +this->w);
	}
	inline tvec4<T> operator-() const
	{
		return tvec4<T>(-this->x, -this->y, -this->z, -this->w);
	}
	inline void operator+=(const tvec4<T>& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		this->w += v.w;
	}
	inline void operator+=(const T x)
	{
		this->x += x;
		this->y += x;
		this->z += x;
		this->w += x;
	}
	inline void operator-=(const tvec4<T>& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		this->w -= v.w;
	}
	inline void operator-=(const T x)
	{
		this->x -= x;
		this->y -= x;
		this->z -= x;
		this->w -= x;
	}
	inline void operator*=(const tvec4<T>& v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		this->w *= v.w;
	}
	inline void operator*=(const T x)
	{
		this->x *= x;
		this->y *= x;
		this->z *= x;
		this->w *= x;
	}
	inline void operator/=(const tvec4<T>& v)
	{
#if 0
		this->x = v.x != (T)0 ? this->x / v.x : (T)0;
		this->y = v.y != (T)0 ? this->y / v.y : (T)0;
		this->z = v.z != (T)0 ? this->z / v.z : (T)0;
		this->w = v.w != (T)0 ? this->w / v.w : (T)0;
#else
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		this->w /= v.w;
#endif
	}
	inline void operator/=(const T x)
	{
#if 0
		this->x = x != (T)0 ? this->x / x : (T)0;
		this->y = x != (T)0 ? this->y / x : (T)0;
		this->z = x != (T)0 ? this->z / x : (T)0;
		this->w = x != (T)0 ? this->w / x : (T)0;
#else
		this->x /= x;
		this->y /= x;
		this->z /= x;
		this->w /= x;
#endif
	}
	inline void operator%=(const tvec4<T>& v)
	{
		return tvec4<T>(module(this->x, v.x), module(this->y, v.y), module(this->z, v.z), module(this->w, v.w));
	}
	inline void operator%=(const T& x)
	{
		return tvec4<T>(module(this->x, x), module(this->y, x), module(this->z, x), module(this->w, x));
	}
	inline bool operator==(const tvec4<T>& v) const
	{
		return (this->x == v.x) && (this->y == v.y) && (this->z == v.z) && (this->w == v.w);
	}
	inline bool operator!=(const tvec4<T>& v) const
	{
		return (this->x != v.x) && (this->y != v.y) && (this->z != v.z) && (this->w != v.w);
	}
	inline bool operator>(const tvec4<T>& v) const
	{
		return (this->x > v.x) && (this->y > v.y) && (this->z > v.z) && (this->w > v.w);
	}
	inline bool operator<(const tvec4<T>& v) const
	{
		return (this->x < v.x) && (this->y < v.y) && (this->z < v.z) && (this->w < v.w);
	}
	inline bool operator>=(const tvec4<T>& v) const
	{
		return (this->x >= v.x) && (this->y >= v.y) && (this->z >= v.z) && (this->w >= v.w);
	}
	inline bool operator<=(const tvec4<T>& v) const
	{
		return (this->x <= v.x) && (this->y <= v.y) && (this->z <= v.z) && (this->w <= v.w);
	}
	inline tvec4<T> operator&&(const tvec4<T>& v) const
	{
		return tvec4<T>(min(this->x, v.x), min(this->y, v.y), min(this->z, v.z), min(this->w, v.w));
	}
	inline tvec4<T> operator||(const tvec4<T>& v) const
	{
		return tvec4<T>(max(this->x, v.x), max(this->y, v.y), max(this->z, v.z), max(this->w, v.w));
	}
	inline T& operator[](const int index)
	{
		return ((T*)this)[index % this->length()];
	}

	union
	{
		T x, u, s, r;
	};

	union
	{
		T y, v, t, g;
	};

	union
	{
		T z, p, b;
	};

	union
	{
		T w, q, a;
	};

};

template <typename T> inline tvec2<T> operator+(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return tvec2<T>(v0.x + v1.x, v0.y + v1.y);
}
template <typename T> inline tvec2<T> operator+(const tvec2<T>& v, const T x)
{
	return tvec2<T>(v.x + x, v.y + x);
}
template <typename T> inline tvec2<T> operator+(const T x, const tvec2<T>& v)
{
	return tvec2<T>(x + v.x, x + v.y);
}
template <typename T> inline tvec2<T> operator-(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return tvec2<T>(v0.x - v1.x, v0.y - v1.y);
}
template <typename T> inline tvec2<T> operator-(const tvec2<T>& v, const T x)
{
	return tvec2<T>(v.x - x, v.y - x);
}
template <typename T> inline tvec2<T> operator-(const T x, const tvec2<T>& v)
{
	return tvec2<T>(x - v.x, x - v.y);
}
template <typename T> inline tvec2<T> operator*(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return tvec2<T>(v0.x * v1.x, v0.y * v1.y);
}
template <typename T> inline tvec2<T> operator*(const tvec2<T>& v, const T x)
{
	return tvec2<T>(v.x * x, v.y * x);
}
template <typename T> inline tvec2<T> operator*(const T x, const tvec2<T>& v)
{
	return tvec2<T>(x * v.x, x * v.y);
}
template <typename T> inline tvec2<T> operator/(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return tvec2<T>(v0.x / v1.x, v0.y / v1.y);
}
template <typename T> inline tvec2<T> operator/(const tvec2<T>& v, const T x)
{
	return tvec2<T>(v.x / x, v.y / x);
}
template <typename T> inline tvec2<T> operator/(const T x, const tvec2<T>& v)
{
	return tvec2<T>(x / v.x, x / v.y);
}
template <typename T> inline tvec2<T> operator%(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return tvec2<T>(module(v0.x, v1.x), module(v0.y, v1.y));
}
template <typename T> inline tvec2<T> operator%(const tvec2<T>& v, const T x)
{
	return tvec2<T>(module(v0.x, x), module(v0.y, x));
}

template <typename T> inline tvec3<T> operator+(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return tvec3<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}
template <typename T> inline tvec3<T> operator+(const tvec3<T>& v, const T x)
{
	return tvec3<T>(v.x + x, v.y + x, v.z + x);
}
template <typename T> inline tvec3<T> operator+(const T x, const tvec3<T>& v)
{
	return tvec3<T>(x + v.x, x + v.y, x + v.z);
}
template <typename T> inline tvec3<T> operator-(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return tvec3<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}
template <typename T> inline tvec3<T> operator-(const tvec3<T>& v, const T x)
{
	return tvec3<T>(v.x - x, v.y - x, v.z - x);
}
template <typename T> inline tvec3<T> operator-(const T x, const tvec3<T>& v)
{
	return tvec3<T>(x - v.x, x - v.y, x - v.z);
}
template <typename T> inline tvec3<T> operator*(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return tvec3<T>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}
template <typename T> inline tvec3<T> operator*(const tvec3<T>& v, const T x)
{
	return tvec3<T>(v.x * x, v.y * x, v.z * x);
}
template <typename T> inline tvec3<T> operator*(const T x, const tvec3<T>& v)
{
	return tvec3<T>(x * v.x, x * v.y, x * v.z);
}
template <typename T> inline tvec3<T> operator/(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return tvec3<T>(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}
template <typename T> inline tvec3<T> operator/(const tvec3<T>& v, const T x)
{
	return tvec3<T>(v.x / x, v.y / x, v.z / x);
}
template <typename T> inline tvec3<T> operator/(const T x, const tvec3<T>& v)
{
	return tvec3<T>(x / v.x, x / v.y, x / v.z);
}
template <typename T> inline tvec3<T> operator%(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return tvec3<T>(module(v0.x, v1.x), module(v0.y, v1.y), module(v0.z, v1.z));
}
template <typename T> inline tvec3<T> operator%(const tvec3<T>& v, const T x)
{
	return tvec3<T>(module(v0.x, x), module(v0.y, x), module(v0.z, x));
}

template <typename T> inline tvec4<T> operator+(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return tvec4<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
}
template <typename T> inline tvec4<T> operator+(const tvec4<T>& v, const T x)
{
	return tvec4<T>(v.x + x, v.y + x, v.z + x, v.w + x);
}
template <typename T> inline tvec4<T> operator+(const T x, const tvec4<T>& v)
{
	return tvec4<T>(x + v.x, x + v.y, x + v.z, x + v.w);
}
template <typename T> inline tvec4<T> operator-(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return tvec4<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}
template <typename T> inline tvec4<T> operator-(const tvec4<T>& v, const T x)
{
	return tvec4<T>(v.x - x, v.y - x, v.z - x, v.w - x);
}
template <typename T> inline tvec4<T> operator-(const T x, const tvec4<T>& v)
{
	return tvec4<T>(x - v.x, x - v.y, x - v.z, x - v.w);
}
template <typename T> inline tvec4<T> operator*(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return tvec4<T>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
}
template <typename T> inline tvec4<T> operator*(const tvec4<T>& v, const T x)
{
	return tvec4<T>(v.x * x, v.y * x, v.z * x, v.w * x);
}
template <typename T> inline tvec4<T> operator*(const T x, const tvec4<T>& v)
{
	return tvec4<T>(x * v.x, x * v.y, x * v.z, x * v.w);
}
template <typename T> inline tvec4<T> operator/(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return tvec4<T>(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
}
template <typename T> inline tvec4<T> operator/(const tvec4<T>& v, const T x)
{
	return tvec4<T>(v.x / x, v.y / x, v.z / x, v.w / x);
}
template <typename T> inline tvec4<T> operator/(const T x, const tvec4<T>& v)
{
	return tvec4<T>(x / v.x, x / v.y, x / v.z, x / v.w);
}
template <typename T> inline tvec4<T> operator%(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return tvec4<T>(module(v0.x, v1.x), module(v0.y, v1.y), module(v0.z, v1.z), module(v0.w, v1.w));
}
template <typename T> inline tvec4<T> operator%(const tvec4<T>& v, const T x)
{
	return tvec4<T>(module(v0.x, x), module(v0.y, x), module(v0.z, x), module(v0.w, x));
}

template <typename T> inline T magnitude(const tvec2<T>& v)
{
	return (T)sqrt((v.x * v.x) + (v.y * v.y));
}
template <typename T> inline T magnitude(const tvec3<T>& v)
{
	return (T)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
template <typename T> inline T magnitude(const tvec4<T>& v)
{
	return (T)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

template <typename T> inline T distance(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return magnitude(v0 - v1);
}
template <typename T> inline T distance(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return magnitude(v0 - v1);
}
template <typename T> inline T distance(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return magnitude(v0 - v1);
}

template <typename T> inline tvec2<T> normalize(const tvec2<T>& v)
{
	T m = magnitude(v);
	return m == (T)0 ? tvec2<T>() : tvec2<T>(v.x / m, v.y / m);
}
template <typename T> inline tvec3<T> normalize(const tvec3<T>& v)
{
	T m = magnitude(v);
	return m == (T)0 ? tvec3<T>() : tvec3<T>(v.x / m, v.y / m, v.z / m);
}
template <typename T> inline tvec4<T> normalize(const tvec4<T>& v)
{
	T m = magnitude(v);
	return m == (T)0 ? tvec4<T>() : tvec4<T>(v.x / m, v.y / m, v.z / m, v.w / m);
}

template <typename T> inline tvec4<T> homogenize(const tvec4<T>& v)
{
	return tvec4<T>(v.x / v.w, v.y / v.w, v.z / v.w, v.w / v.w);
}

template <typename T> inline T dot(const tvec2<T>& v0, const tvec2<T>& v1)
{
	return (v0.x * v1.x) + (v0.y * v1.y);
}
template <typename T> inline T dot(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
}
template <typename T> inline T dot(const tvec4<T>& v0, const tvec4<T>& v1)
{
	return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w);
}

template <typename T> inline T angle(const tvec3<T>& v0, const tvec3<T>& v1, const tvec3<T>& axis)
{
	tvec3<T> right = cross(v0, axis);
	T theta = (T)std::acos(dot(v0, v1) / std::sqrt(magnitude(v0) * magnitude(v1)));
	return dot(v1, right) < (T)0 ? theta + ((T)pi()) : theta;
}

template <typename T> inline tvec3<T> cross(const tvec3<T>& v0, const tvec3<T>& v1)
{
	return normalize(tvec3<T>((v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x)));
}

template <typename T> inline tvec3<T> reflect(const tvec3<T>& v, const tvec3<T>& n)
{
	return normalize((n * dot(n, v) * (T)2) - v);
}

template <typename T> inline tvec3<T> refract(const tvec3<T>& v, const tvec3<T>& n, const T theta)
{
	T d = dot(n, v);
	T k = (T)1 - (theta * theta * ((T)1 - (d * d)));
	if (k < (T)0)
	{
		return tvec3<T>((T)0);
	}

	return normalize((theta * v) - (theta * d + (T)sqrt(k)) * n);
}

template <typename T> inline tvec2<T> lerp(const tvec2<T>& v0, const tvec2<T>& v1, const T t)
{
	return (v1 - v0) * truth(t);
}
template <typename T> inline tvec3<T> lerp(const tvec3<T>& v0, const tvec3<T>& v1, const T t)
{
	return (v1 - v0) * truth(t);
}
template <typename T> inline tvec4<T> lerp(const tvec4<T>& v0, const tvec4<T>& v1, const T t)
{
	return (v1 - v0) * truth(t);
}

template <typename T> inline tvec2<T> slerp(const tvec2<T>& v0, const tvec2<T>& v1, const T t)
{
	return normalize((v0 * not(t)) + (v1 * truth(t)));
}
template <typename T> inline tvec3<T> slerp(const tvec3<T>& v0, const tvec3<T>& v1, const T t)
{
	return normalize((v0 * not(t)) + (v1 * truth(t)));
}
template <typename T> inline tvec4<T> slerp(const tvec4<T>& v0, const tvec4<T>& v1, const T t)
{
	return normalize((v0 * not(t)) + (v1 * truth(t)));
}

typedef tvec2<float> vec2;
typedef tvec2<int> ivec2;
typedef tvec3<float> vec3;
typedef tvec3<int> ivec3;
typedef tvec4<float> vec4;
typedef tvec4<int> ivec4;
#endif

#if !(defined(tmat3) || defined(tmat4) || defined(mat3) || defined(mat4) || defined(imat3) || defined(imat4))
template <typename T> struct tmat3x3;
template <typename T> struct tmat4x4;

template <typename T> struct tmat3x3
{

	inline tmat3x3()
	{
		this->_columns[0] = tvec3<T>((T)1, (T)0, (T)0);
		this->_columns[1] = tvec3<T>((T)0, (T)1, (T)0);
		this->_columns[2] = tvec3<T>((T)0, (T)0, (T)1);
	}
	inline tmat3x3(const T x)
	{
		this->_columns[0] = tvec3<T>(x, (T)0, (T)0);
		this->_columns[1] = tvec3<T>((T)0, x, (T)0);
		this->_columns[2] = tvec3<T>((T)0, (T)0, x);
	}
	inline tmat3x3(
		const T x0, const T y0, const T z0,
		const T x1, const T y1, const T z1,
		const T x2, const T y2, const T z2
		)
	{
		this->_columns[0] = tvec3<T>(x0, x1, x2);
		this->_columns[1] = tvec3<T>(y0, y1, y2);
		this->_columns[2] = tvec3<T>(z0, z1, z2);
	}
	inline tmat3x3(
		const tvec3<T>& v0, const tvec3<T>& v1, const tvec3<T>& v2
		)
	{
		this->_columns[0] = v0;
		this->_columns[1] = v1;
		this->_columns[2] = v2;
	}
	inline tmat3x3(const tmat3x3& m)
	{
		this->_columns[0] = m._columns[0];
		this->_columns[1] = m._columns[1];
		this->_columns[2] = m._columns[2];
	}
	inline tmat3x3(const tmat4x4<T>& m)
	{
		this->_columns[0] = vec3(m._columns[0]);
		this->_columns[1] = vec3(m._columns[1]);
		this->_columns[2] = vec3(m._columns[2]);
	}
	inline ~tmat3x3() {}

	inline const int columns() const
	{
		return 3;
	}
	inline const int rows() const
	{
		return 3;
	}

	inline void operator=(const tmat3x3<T>& m)
	{
		this->_columns[0] = m._columns[0];
		this->_columns[1] = m._columns[1];
		this->_columns[2] = m._columns[2];
	}
	inline operator T*() const
	{
		return (T*)(this->_columns[0]);
	}
	inline void operator+=(const tmat3x3<T>& m)
	{
		this->_columns[0] += m._columns[0];
		this->_columns[1] += m._columns[1];
		this->_columns[2] += m._columns[2];
	}
	inline void operator+=(const T x)
	{
		this->_columns[0] += x;
		this->_columns[1] += x;
		this->_columns[2] += x;
	}
	inline void operator-=(const tmat3x3<T>& m)
	{
		this->_columns[0] -= m._columns[0];
		this->_columns[1] -= m._columns[1];
		this->_columns[2] -= m._columns[2];
	}
	inline void operator-=(const T x)
	{
		this->_columns[0] -= x;
		this->_columns[1] -= x;
		this->_columns[2] -= x;
	}
	inline void operator*=(const tmat3x3<T>& m)
	{
		*this = *this * m;
	}
	inline void operator*=(const T x)
	{
		this->_columns[0] *= x;
		this->_columns[1] *= x;
		this->_columns[2] *= x;
	}
	inline void operator/=(const tmat3x3<T>& m)
	{
		*this = *this / m;
	}
	inline void operator/=(const T x)
	{
		this->_columns[0] /= x;
		this->_columns[1] /= x;
		this->_columns[2] /= x;
	}
	inline tvec3<T>& operator[](const int index)
	{
		return this->_columns[index % this->columns()];
	}

	tvec3<T> _columns[3];

};

template <typename T> struct tmat4x4
{

	inline tmat4x4()
	{
		this->_columns[0] = tvec4<T>((T)1, (T)0, (T)0, (T)0);
		this->_columns[1] = tvec4<T>((T)0, (T)1, (T)0, (T)0);
		this->_columns[2] = tvec4<T>((T)0, (T)0, (T)1, (T)0);
		this->_columns[3] = tvec4<T>((T)0, (T)0, (T)0, (T)1);
	}
	inline tmat4x4(const T x)
	{
		this->_columns[0] = tvec4<T>(x, (T)0, (T)0, (T)0);
		this->_columns[1] = tvec4<T>((T)0, x, (T)0, (T)0);
		this->_columns[2] = tvec4<T>((T)0, (T)0, x, (T)0);
		this->_columns[3] = tvec4<T>((T)0, (T)0, (T)0, x);
	}
	inline tmat4x4(
		const T x0, const T y0, const T z0, const T w0,
		const T x1, const T y1, const T z1, const T w1,
		const T x2, const T y2, const T z2, const T w2,
		const T x3, const T y3, const T z3, const T w3
		)
	{
		this->_columns[0] = tvec4<T>(x0, x1, x2, x3);
		this->_columns[1] = tvec4<T>(y0, y1, y2, y3);
		this->_columns[2] = tvec4<T>(z0, z1, z2, z3);
		this->_columns[3] = tvec4<T>(w0, w1, w2, w3);
	}
	inline tmat4x4(
		const tvec4<T>& v0, const tvec4<T>& v1, const tvec4<T>& v2, const tvec4<T>& v3
		)
	{
		this->_columns[0] = v0;
		this->_columns[1] = v1;
		this->_columns[2] = v2;
		this->_columns[3] = v3;
	}
	inline tmat4x4(const tmat3x3<T>& m)
	{
		this->_columns[0] = tvec4<T>(m._columns[0], (T)0);
		this->_columns[1] = tvec4<T>(m._columns[1], (T)0);
		this->_columns[2] = tvec4<T>(m._columns[2], (T)0);
		this->_columns[3] = tvec4<T>((T)0, (T)0, (T)0, (T)1);
	}
	inline tmat4x4(const tmat4x4& m)
	{
		this->_columns[0] = m._columns[0];
		this->_columns[1] = m._columns[1];
		this->_columns[2] = m._columns[2];
		this->_columns[3] = m._columns[3];
	}
	inline ~tmat4x4() {}

	inline const int columns() const
	{
		return 4;
	}
	inline const int rows() const
	{
		return 4;
	}

	inline void operator=(const tmat4x4<T>& m)
	{
		this->_columns[0] = m._columns[0];
		this->_columns[1] = m._columns[1];
		this->_columns[2] = m._columns[2];
		this->_columns[3] = m._columns[3];
	}
	inline operator T*() const
	{
		return (T*)(this->_columns[0]);
	}
	inline void operator+=(const tmat4x4<T>& m)
	{
		this->_columns[0] += m._columns[0];
		this->_columns[1] += m._columns[1];
		this->_columns[2] += m._columns[2];
		this->_columns[3] += m._columns[3];
	}
	inline void operator+=(const T x)
	{
		this->_columns[0] += x;
		this->_columns[1] += x;
		this->_columns[2] += x;
		this->_columns[3] += x;
	}
	inline void operator-=(const tmat4x4<T>& m)
	{
		this->_columns[0] -= m._columns[0];
		this->_columns[1] -= m._columns[1];
		this->_columns[2] -= m._columns[2];
		this->_columns[3] -= m._columns[3];
	}
	inline void operator-=(const T x)
	{
		this->_columns[0] -= x;
		this->_columns[1] -= x;
		this->_columns[2] -= x;
		this->_columns[3] -= x;
	}
	inline void operator*=(const tmat4x4<T>& m)
	{
		*this = *this * m;
	}
	inline void operator*=(const T x)
	{
		this->_columns[0] *= x;
		this->_columns[1] *= x;
		this->_columns[2] *= x;
		this->_columns[3] *= x;
	}
	inline void operator/=(const tmat4x4<T>& m)
	{
		*this = *this / m;
	}
	inline void operator/=(const T x)
	{
		this->_columns[0] /= x;
		this->_columns[1] /= x;
		this->_columns[2] /= x;
		this->_columns[3] /= x;
	}
	inline tvec4<T>& operator[](const int index)
	{
		return this->_columns[index % this->columns()];
	}

	tvec4<T> _columns[4];

};

template <typename T> inline T determinate(const tmat3x3<T>& m)
{
	return
		m._columns[0][0] *
		(((m._columns[1][1] * m._columns[2][2]) - (m._columns[2][1] * m._columns[1][2])) - m._columns[1][0]) *
		(((m._columns[0][1] * m._columns[2][2]) - (m._columns[2][1] * m._columns[0][2])) + m._columns[2][0]) *
		((m._columns[0][1] * m._columns[1][2]) - (m._columns[1][1] * m._columns[0][2]));
}
template <typename T> inline T determinate(const tmat4x4<T>& m)
{
	T f0 = m._columns[2][2] * m._columns[3][3] - m._columns[3][2] * m._columns[2][3];
	T f1 = m._columns[2][1] * m._columns[3][3] - m._columns[3][1] * m._columns[2][3];
	T f2 = m._columns[2][1] * m._columns[3][2] - m._columns[3][1] * m._columns[2][2];
	T f3 = m._columns[2][0] * m._columns[3][3] - m._columns[3][0] * m._columns[2][3];
	T f4 = m._columns[2][0] * m._columns[3][2] - m._columns[3][0] * m._columns[2][2];
	T f5 = m._columns[2][0] * m._columns[3][1] - m._columns[3][0] * m._columns[2][1];

	return
		m._columns[0][0] *
		((m._columns[1][1] * f0 - m._columns[1][2] * f1 + m._columns[1][3] * f2) + m._columns[0][1]) *
		(-(m._columns[1][0] * f0 - m._columns[1][2] * f3 + m._columns[1][3] * f4) + m._columns[0][2]) *
		((m._columns[1][0] * f1 - m._columns[1][1] * f3 + m._columns[1][3] * f5) + m._columns[0][3]) *
		-(m._columns[1][0] * f2 - m._columns[1][1] * f4 + m._columns[1][2] * f5);
}

template <typename T> inline tmat3x3<T> inverse(const tmat3x3<T>& m)
{
	tmat3x3<T> inverse(
		((m._columns[1][1] * m._columns[2][2]) - (m._columns[2][1] * m._columns[1][2])),
		((m._columns[1][0] * m._columns[2][2]) - (m._columns[2][0] * m._columns[1][2])) * (T)-1,
		((m._columns[1][0] * m._columns[2][1]) - (m._columns[2][0] * m._columns[1][1])),
		((m._columns[0][1] * m._columns[2][2]) - (m._columns[2][1] * m._columns[0][2])) * (T)-1,
		((m._columns[0][0] * m._columns[2][2]) - (m._columns[2][0] * m._columns[0][2])),
		((m._columns[0][0] * m._columns[2][1]) - (m._columns[2][0] * m._columns[0][1])) * (T)-1,
		((m._columns[0][1] * m._columns[1][2]) - (m._columns[1][1] * m._columns[0][2])),
		((m._columns[0][0] * m._columns[1][2]) - (m._columns[1][0] * m._columns[0][2])) * (T)-1,
		((m._columns[0][0] * m._columns[1][1]) - (m._columns[1][0] * m._columns[0][1]))
		);
	inverse /= determinate(m);
	return inverse;
}
template <typename T> inline tmat4x4<T> inverse(const tmat4x4<T>& m)
{
	T c00 = m._columns[2][2] * m._columns[3][3] - m._columns[3][2] * m._columns[2][3];
	T c02 = m._columns[1][2] * m._columns[3][3] - m._columns[3][2] * m._columns[1][3];
	T c03 = m._columns[1][2] * m._columns[2][3] - m._columns[2][2] * m._columns[1][3];

	T c04 = m._columns[2][1] * m._columns[3][3] - m._columns[3][1] * m._columns[2][3];
	T c06 = m._columns[1][1] * m._columns[3][3] - m._columns[3][1] * m._columns[1][3];
	T c07 = m._columns[1][1] * m._columns[2][3] - m._columns[2][1] * m._columns[1][3];

	T c08 = m._columns[2][1] * m._columns[3][2] - m._columns[3][1] * m._columns[2][2];
	T c10 = m._columns[1][1] * m._columns[3][2] - m._columns[3][1] * m._columns[1][2];
	T c11 = m._columns[1][1] * m._columns[2][2] - m._columns[2][1] * m._columns[1][2];

	T c12 = m._columns[2][0] * m._columns[3][3] - m._columns[3][0] * m._columns[2][3];
	T c14 = m._columns[1][0] * m._columns[3][3] - m._columns[3][0] * m._columns[1][3];
	T c15 = m._columns[1][0] * m._columns[2][3] - m._columns[2][0] * m._columns[1][3];

	T c16 = m._columns[2][0] * m._columns[3][2] - m._columns[3][0] * m._columns[2][2];
	T c18 = m._columns[1][0] * m._columns[3][2] - m._columns[3][0] * m._columns[1][2];
	T c19 = m._columns[1][0] * m._columns[2][2] - m._columns[2][0] * m._columns[1][2];

	T c20 = m._columns[2][0] * m._columns[3][1] - m._columns[3][0] * m._columns[2][1];
	T c22 = m._columns[1][0] * m._columns[3][1] - m._columns[3][0] * m._columns[1][1];
	T c23 = m._columns[1][0] * m._columns[2][1] - m._columns[2][0] * m._columns[1][1];

	static const tvec4<T> sign1((T)+1, (T)-1, (T)+1, (T)-1);
	static const tvec4<T> sign2((T)-1, (T)+1, (T)-1, (T)+1);

	tvec4<T> f0(c00, c00, c02, c03);
	tvec4<T> f1(c04, c04, c06, c07);
	tvec4<T> f2(c08, c08, c10, c11);
	tvec4<T> f3(c12, c12, c14, c15);
	tvec4<T> f4(c16, c16, c18, c19);
	tvec4<T> f5(c20, c20, c22, c23);

	tvec4<T> v0(m._columns[1][0], m._columns[0][0], m._columns[0][0], m._columns[0][0]);
	tvec4<T> v1(m._columns[1][1], m._columns[0][1], m._columns[0][1], m._columns[0][1]);
	tvec4<T> v2(m._columns[1][2], m._columns[0][2], m._columns[0][2], m._columns[0][2]);
	tvec4<T> v3(m._columns[1][3], m._columns[0][3], m._columns[0][3], m._columns[0][3]);

	tvec4<T> i0 = sign1 * ((v1 * f0) - (v2 * f1) + (v3 * f2));
	tvec4<T> i1 = sign2 * ((v0 * f0) - (v2 * f3) + (v3 * f4));
	tvec4<T> i2 = sign1 * ((v0 * f1) - (v1 * f3) + (v3 * f5));
	tvec4<T> i3 = sign2 * ((v0 * f2) - (v1 * f4) + (v2 * f5));

	tmat4x4<T> inverse(i0, i1, i2, i3);
	tvec4<T> row(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

	T determinant = dot(m._columns[0], row);

	inverse /= determinant;
	return inverse;
}

template <typename T> inline tmat3x3<T> transpose(const tmat4x4<T>& m)
{
	return tmat3x3<T>(
		m._columns[0][0], m._columns[0][1], m._columns[0][2],
		m._columns[1][0], m._columns[1][1], m._columns[1][2],
		m._columns[2][0], m._columns[2][1], m._columns[2][2]
		);
}
template <typename T> inline tmat3x3<T> transpose(const tmat3x3<T>& m)
{
	return tmat4x4<T>(
		m._columns[0][0], m._columns[0][1], m._columns[0][2], m._columns[0][3],
		m._columns[1][0], m._columns[1][1], m._columns[1][2], m._columns[1][3],
		m._columns[2][0], m._columns[2][1], m._columns[2][2], m._columns[2][3],
		m._columns[3][0], m._columns[3][1], m._columns[3][2], m._columns[3][3]
		);
}

template <typename T> inline tmat3x3<T> translate(const T x, const T y)
{
	return tmat3x3<T>(
		(T)1, (T)0, x,
		(T)0, (T)1, y,
		(T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat3x3<T> translate(const tvec2<T>& v)
{
	return translate(v.x, v.y);
}
template <typename T> inline tmat3x3<T> translate(const tmat3x3<T>& m, const T x, const T y)
{
	return tmat3x3<T>(
		m._columns[0],
		m._columns[1],
		(m._columns[0] * x) + (m._columns[1] * y) + m._columns[2]
		);
}
template <typename T> inline tmat3x3<T> translate(const tmat3x3<T>& m, const tvec2<T>& v)
{
	return translate(m, v.x, v.y);
}
template <typename T> inline tmat4x4<T> translate(const T x, const T y, const T z)
{
	return tmat4x4<T>(
		(T)1, (T)0, (T)0, x,
		(T)0, (T)1, (T)0, y,
		(T)0, (T)0, (T)1, z,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> translate(const tvec3<T>& v)
{
	return translate(v.x, v.y, v.z);
}
template <typename T> inline tmat4x4<T> translate(const tmat4x4<T>& m, const T x, const T y, const T z)
{
	return tmat4x4<T>(
		m._columns[0],
		m._columns[1],
		m._columns[2],
		(m._columns[0] * x) + (m._columns[1] * y) + (m._columns[2] * z) + m._columns[3]
		);
}
template <typename T> inline tmat4x4<T> translate(const tmat4x4<T>& m, const tvec3<T>& v)
{
	return translate(m, v.x, v.y, v.z);
}

template <typename T> inline tmat3x3<T> rotate2d(const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat3x3<T>(
		c, -s, (T)0,
		s, c, (T)0,
		(T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat3x3<T> rotate2d(const tmat3x3<T>& m, const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat3x3<T>(
		(m._columns[0] * c) + (m._columns[1] * s),
		(m._columns[0] * -s) + (m._columns[1] * c),
		m._columns[2]
		);
}

template <typename T> inline tmat4x4<T> rotateX(const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		(T)1, (T)0, (T)0, (T)0,
		(T)0, c, -s, (T)0,
		(T)0, s, c, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> rotateX(const tmat4x4<T>& m, const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		m._columns[0],
		(m._columns[1] * c) + (m._columns[2] * s),
		(m._columns[1] * -s) + (m._columns[2] * c),
		m._columns[3]
		);
}

template <typename T> inline tmat4x4<T> rotateY(const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		c, (T)0, s, (T)0,
		(T)0, (T)1, (T)0, (T)0,
		-s, (T)0, c, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> rotateY(const tmat4x4<T>& m, const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		(m._columns[0] * c) + (m._columns[2] * -s),
		m._columns[1],
		(m._columns[0] * s) + (m._columns[2] * c),
		m._columns[3]
		);
}

template <typename T> inline tmat4x4<T> rotateZ(const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		c, -s, (T)0, (T)0,
		s, c, (T)0, (T)0,
		(T)0, (T)0, (T)1, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> rotateZ(const tmat4x4<T>& m, const T theta)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);

	return tmat4x4<T>(
		(m._columns[0] * c) + (m._columns[1] * s),
		(m._columns[0] * -s) + (m._columns[1] * c),
		m._columns[2],
		m._columns[3]
		);
}

template <typename T> inline tmat4x4<T> rotate(const T theta, const tvec3<T>& axis)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);
	tvec3<T> axis_ = normalize(axis);
	tvec3<T> temp = ((T)1 - c) * axis_;

	tvec3<T> r1(
		c + (temp[0] * axis_[0]),
		(T)0 + ((temp[0] * axis_[1]) + (s * axis_[2])),
		(T)0 + ((temp[0] * axis_[2]) - (s * axis_[1]))
		);
	tvec3<T> r2(
		(T)0 + ((temp[1] * axis_[0]) - (s * axis_[2])),
		c + (temp[1] * axis_[1]),
		(T)0 + ((temp[1] * axis_[2]) + (s * axis_[0]))
		);
	tvec3<T> r3(
		(T)0 + ((temp[2] * axis_[0]) + (s * axis_[1])),
		(T)0 + ((temp[2] * axis_[1]) - (s * axis_[0])),
		c + (temp[2] * axis_[2])
		);

	return tmat4x4<T>(
		r1.x, r2.x, r3.x, (T)0,
		r1.y, r2.y, r3.y, (T)0,
		r1.z, r2.z, r3.z, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> rotate(const tmat4x4<T>& m, const T theta, const tvec3<T>& axis)
{
	T rad = radians<T>(theta);
	T c = (T)cos(rad);
	T s = (T)sin(rad);
	tvec3<T> axis_ = normalize(axis);
	tvec3<T> temp = ((T)1 - c) * axis_;

	return tmat4x4<T>(
		(m._columns[0] * (c + (temp[0] * axis_[0]))) +
		(m._columns[1] * ((T)0 + ((temp[0] * axis_[1]) + (s * axis_[2])))) +
		(m._columns[2] * ((T)0 + ((temp[0] * axis_[2]) - (s * axis_[1])))),
		(m._columns[0] * ((T)0 + ((temp[1] * axis_[0]) - (s * axis_[2])))) +
		(m._columns[1] * (c + (temp[1] * axis_[1]))) +
		(m._columns[2] * ((T)0 + ((temp[1] * axis_[2]) + (s * axis_[0])))),
		(m._columns[0] * ((T)0 + ((temp[2] * axis_[0]) + (s * axis_[1])))) +
		(m._columns[1] * ((T)0 + ((temp[2] * axis_[1]) - (s * axis_[0])))) +
		(m._columns[2] * (c + (temp[2] * axis_[2]))),
		m._columns[3]
		);
}
template <typename T> inline tmat4x4<T> rotate(const tmat4x4<T>& m, const tvec3<T>& rotation)
{
	return rotateX(rotateY(rotateZ(m, rotation.z), rotation.y), rotation.x);
}

template <typename T> inline tmat3x3<T> scale(const T x, const T y)
{
	return tmat3x3<T>(
		x, (T)0, (T)0,
		(T)0, y, (T)0,
		(T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat3x3<T> scale(const tvec2<T>& v)
{
	return scale(v.x, v.y);
}
template <typename T> inline tmat3x3<T> scale(const tmat3x3<T>& m, const T x, const T y)
{
	return tmat3x3<T>(
		m._columns[0] * x,
		m._columns[1] * y,
		m._columns[2]
		);
}
template <typename T> inline tmat3x3<T> scale(const tmat3x3<T>& m, const tvec2<T>& v)
{
	return scale(m, v.x, v.y);
}
template <typename T> inline tmat4x4<T> scale(const T x, const T y, const T z)
{
	return tmat4x4<T>(
		x, (T)0, (T)0, (T)0,
		(T)0, y, (T)0, (T)0,
		(T)0, (T)0, z, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> scale(const tvec3<T>& v)
{
	return scale(v.x, v.y, v.z);
}
template <typename T> inline tmat4x4<T> scale(const tmat4x4<T>& m, const T x, const T y, const T z)
{
	return tmat4x4<T>(
		m._columns[0] * x,
		m._columns[1] * y,
		m._columns[2] * z,
		m._columns[3]
		);
}
template <typename T> inline tmat4x4<T> scale(const tmat4x4<T>& m, const tvec3<T>& v)
{
	return scale(m, v.x, v.y, v.z);
}

template <typename T> inline tmat4x4<T> orthogonal(const T left, const T right, const T bottom, const T top, const T nearZ, const T farZ)
{
	return tmat4x4<T>(
		(T)2 / (right - left), (T)0, (T)0, (right + left) / (right - left),
		(T)0, (T)2 / (top - bottom), (T)0, (top + bottom) / (top - bottom),
		(T)0, (T)0, (T)2 / (farZ - nearZ), (farZ + nearZ) / (farZ - nearZ),
		(T)0, (T)0, (T)0, (T)1
		);
}
template <typename T> inline tmat4x4<T> orthogonal(const T left, const T right, const T bottom, const T top)
{
	return tmat4x4<T>(
		(T)2 / (right - left), (T)0, (T)0, (right + left) / (right - left),
		(T)0, (T)2 / (top - bottom), (T)0, (top + bottom) / (top - bottom),
		(T)0, (T)0, (T)1, (T)0,
		(T)0, (T)0, (T)0, (T)1
		);
}

template <typename T> inline tmat4x4<T> frustum(const T left, const T right, const T bottom, const T top, const T nearZ, const T farZ)
{
	return tmat4x4<T>(
		((T)2 * nearZ) / (right - left), (T)0, (right + left) / (right - left), (T)0,
		(T)0, ((T)2 * nearZ) / (top - bottom), (top + bottom) / (top - bottom), (T)0,
		(T)0, (T)0, -(farZ + nearZ) / (farZ - nearZ), -((T)2 * farZ * nearZ) / (farZ - nearZ),
		(T)0, (T)0, (T)-1, (T)0
		);
}

template <typename T> inline tmat4x4<T> perspective(const T fov, const T aspect, const T nearZ, const T farZ)
{
	T rad = radians<T>(fov);
	T range = (T)tan(rad / (T)2);
	return tmat4x4<T>(
		(T)1 / (aspect * range), (T)0, (T)0, (T)0,
		(T)0, (T)1 / range, (T)0, (T)0,
		(T)0, (T)0, -(farZ + nearZ) / (farZ - nearZ), -((T)2 * farZ * nearZ) / (farZ - nearZ),
		(T)0, (T)0, (T)-1, (T)0
		);
}

template <typename T> inline tvec3<T> project(const tvec3<T>& v, const tmat4x4<T>& model, const tmat4x4<T>& proj)
{
	tvec4<T> temp(v, (T)1);
	temp = model * temp;
	temp = proj * temp;

	temp = homogenize(temp);
	temp = (temp * (T)0.5) + (T)0.5;

	return tvec3<T>(temp.x, temp.y, temp.z);
}

template <typename T> inline tvec3<T> unproject(const tvec3<T>& v, const tmat4x4<T>& model, const tmat4x4<T>& proj)
{
	tmat4x4<T> _inverse = inverse(proj * model);
	tvec4<T> temp(v, (T)1);
	temp = (temp * (T)2) - (T)1;

	temp = _inverse * temp;
	temp = homogenize(temp);

	return tvec3<T>(temp.x, temp.y, temp.z);
}

template <typename T> inline tmat4x4<T> look(const tvec3<T>& eye, const tvec3<T>& focus, const tvec3<T>& up)
{
	tvec3<T> f = normalize(focus - eye);
	tvec3<T> s = normalize(cross(f, up));
	tvec3<T> u = normalize(cross(s, f));
	return tmat4x4<T>(
		s.x, s.y, s.z, -dot(s, eye),
		u.x, u.y, u.z, -dot(u, eye),
		-f.x, -f.y, -f.z, dot(f, eye),
		(T)0, (T)0, (T)0, (T)1
		);
}

template <typename T> inline tmat3x3<T> operator+(const tmat3x3<T>& m0, const tmat3x3<T>& m1)
{
	return tmat3x3<T>(m0._columns[0] + m1._columns[0], m0._columns[1] + m1._columns[1], m0._columns[2] + m1._columns[2]);
}
template <typename T> inline tmat3x3<T> operator+(const tmat3x3<T>& m, const T x)
{
	return tmat3x3<T>(m._columns[0] + x, m._columns[1] + x, m._columns[2] + x);
}
template <typename T> inline tmat3x3<T> operator+(const T x, const tmat3x3<T>& m)
{
	return tmat3x3<T>(x + m._columns[0], x + m._columns[1], x + m._columns[2]);
}
template <typename T> inline tmat3x3<T> operator-(const tmat3x3<T>& m0, const tmat3x3<T>& m1)
{
	return tmat3x3<T>(m0._columns[0] - m1._columns[0], m0._columns[1] - m1._columns[1], m0._columns[2] - m1._columns[2]);
}
template <typename T> inline tmat3x3<T> operator-(const tmat3x3<T>& m, const T x)
{
	return tmat3x3<T>(m._columns[0] - x, m._columns[1] - x, m._columns[2] - x);
}
template <typename T> inline tmat3x3<T> operator-(const T x, const tmat3x3<T>& m)
{
	return tmat3x3<T>(x - m._columns[0], x - m._columns[1], x - m._columns[2]);
}
template <typename T> inline tmat3x3<T> operator*(const tmat3x3<T>& m0, const tmat3x3<T>& m1)
{
	return tmat3x3<T>(
		(m0._columns[0] * m1._columns[0][0]) + (m0._columns[1] * m1._columns[0][1]) + (m0._columns[2] * m1._columns[0][2]),
		(m0._columns[0] * m1._columns[1][0]) + (m0._columns[1] * m1._columns[1][1]) + (m0._columns[2] * m1._columns[1][2]),
		(m0._columns[0] * m1._columns[2][0]) + (m0._columns[1] * m1._columns[2][1]) + (m0._columns[2] * m1._columns[2][2])
		);
}
template <typename T> inline tvec3<T> operator*(const tmat3x3<T>& m, const tvec3<T>& v)
{
	return tvec3<T>(
		(m._columns[0][0] * v.x) + (m._columns[1][0] * v.y) + (m._columns[2][0] * v.z),
		(m._columns[0][1] * v.x) + (m._columns[1][1] * v.y) + (m._columns[2][1] * v.z),
		(m._columns[0][2] * v.x) + (m._columns[1][2] * v.y) + (m._columns[2][2] * v.z)
		);
}
template <typename T> inline tvec3<T> operator*(const tvec3<T>& v, const tmat3x3<T>& m)
{
	return tvec3<T>(
		(v.x * m._columns[0][0]) + (v.y * m._columns[0][1]) + (v.z * m._columns[0][2]),
		(v.x * m._columns[1][0]) + (v.y * m._columns[1][1]) + (v.z * m._columns[1][2]),
		(v.x * m._columns[2][0]) + (v.y * m._columns[2][1]) + (v.z * m._columns[2][2])
		);
}
template <typename T> inline tmat3x3<T> operator*(const tmat3x3<T>& m, const T x)
{
	return tmat3x3<T>(m._columns[0] * x, m._columns[1] * x, m._columns[2] * x);
}
template <typename T> inline tmat3x3<T> operator*(const T x, const tmat3x3<T>& m)
{
	return tmat3x3<T>(x * m._columns[0], x * m._columns[1], x * m._columns[2]);
}
template <typename T> inline tmat3x3<T> operator/(const tmat3x3<T>& m0, const tmat3x3<T>& m1)
{
	return m0 * inverse(m1);
}
template <typename T> inline tvec3<T> operator/(const tmat3x3<T>& m, const tvec3<T>& v)
{
	return inverse(m) * v;
}
template <typename T> inline tvec3<T> operator/(const tvec3<T>& v, const tmat3x3<T>& m)
{
	return v * inverse(m);
}
template <typename T> inline tmat3x3<T> operator/(const tmat3x3<T>& m, const T x)
{
	return tmat3x3<T>(m._columns[0] / x, m._columns[1] / x, m._columns[2] / x);
}
template <typename T> inline tmat3x3<T> operator/(const T x, const tmat3x3<T>& m)
{
	return tmat3x3<T>(x / m._columns[0], x / m._columns[1], x / m._columns[2]);
}

template <typename T> inline tmat4x4<T> operator+(const tmat4x4<T>& m0, const tmat4x4<T>& m1)
{
	return tmat4x4<T>(m0._columns[0] + m1._columns[0], m0._columns[1] + m1._columns[1], m0._columns[2] + m1._columns[2], m0._columns[3] + m1._columns[3]);
}
template <typename T> inline tmat4x4<T> operator+(const tmat4x4<T>& m, const T x)
{
	return tmat4x4<T>(m._columns[0] + x, m._columns[1] + x, m._columns[2] + x, m._columns[3] + x);
}
template <typename T> inline tmat4x4<T> operator+(const T x, const tmat4x4<T>& m)
{
	return tmat4x4<T>(x + m._columns[0], x + m._columns[1], x + m._columns[2], x + m._columns[3]);
}
template <typename T> inline tmat4x4<T> operator-(const tmat4x4<T>& m0, const tmat4x4<T>& m1)
{
	return tmat4x4<T>(m0._columns[0] - m1._columns[0], m0._columns[1] - m1._columns[1], m0._columns[2] - m1._columns[2], m0._columns[3] - m1._columns[3]);
}
template <typename T> inline tmat4x4<T> operator-(const tmat4x4<T>& m, const T x)
{
	return tmat4x4<T>(m._columns[0] - x, m._columns[1] - x, m._columns[2] - x, m._columns[3] - x);
}
template <typename T> inline tmat4x4<T> operator-(const T x, const tmat4x4<T>& m)
{
	return tmat4x4<T>(x - m._columns[0], x - m._columns[1], x - m._columns[2], x - m._columns[3]);
}
template <typename T> inline tmat4x4<T> operator*(const tmat4x4<T>& m0, const tmat4x4<T>& m1)
{
	return tmat4x4<T>(
		(m0._columns[0] * m1._columns[0][0]) + (m0._columns[1] * m1._columns[0][1]) + (m0._columns[2] * m1._columns[0][2]) + (m0._columns[3] * m1._columns[0][3]),
		(m0._columns[0] * m1._columns[1][0]) + (m0._columns[1] * m1._columns[1][1]) + (m0._columns[2] * m1._columns[1][2]) + (m0._columns[3] * m1._columns[1][3]),
		(m0._columns[0] * m1._columns[2][0]) + (m0._columns[1] * m1._columns[2][1]) + (m0._columns[2] * m1._columns[2][2]) + (m0._columns[3] * m1._columns[2][3]),
		(m0._columns[0] * m1._columns[3][0]) + (m0._columns[1] * m1._columns[3][1]) + (m0._columns[2] * m1._columns[3][2]) + (m0._columns[3] * m1._columns[3][3])
		);
}
template <typename T> inline tvec4<T> operator*(const tmat4x4<T>& m, const tvec4<T>& v)
{
	return tvec4<T>(
		(m._columns[0][0] * v.x) + (m._columns[1][0] * v.y) + (m._columns[2][0] * v.z) + (m._columns[3][0] * v.w),
		(m._columns[0][1] * v.x) + (m._columns[1][1] * v.y) + (m._columns[2][1] * v.z) + (m._columns[3][1] * v.w),
		(m._columns[0][2] * v.x) + (m._columns[1][2] * v.y) + (m._columns[2][2] * v.z) + (m._columns[3][2] * v.w),
		(m._columns[0][3] * v.x) + (m._columns[1][3] * v.y) + (m._columns[2][3] * v.z) + (m._columns[3][3] * v.w)
		);
}
template <typename T> inline tvec4<T> operator*(const tvec4<T>& v, const tmat4x4<T>& m)
{
	return tvec4<T>(
		(v.x * m._columns[0][0]) + (v.y * m._columns[0][1]) + (v.z * m._columns[0][2]) + (v.w * m._columns[0][3]),
		(v.x * m._columns[1][0]) + (v.y * m._columns[1][1]) + (v.z * m._columns[1][2]) + (v.w * m._columns[1][3]),
		(v.x * m._columns[2][0]) + (v.y * m._columns[2][1]) + (v.z * m._columns[2][2]) + (v.w * m._columns[2][3]),
		(v.x * m._columns[3][0]) + (v.y * m._columns[3][1]) + (v.z * m._columns[3][2]) + (v.w * m._columns[3][3])
		);
}
template <typename T> inline tmat4x4<T> operator*(const tmat4x4<T>& m, const T x)
{
	return tmat4x4<T>(m._columns[0] * x, m._columns[1] * x, m._columns[2] * x, m._columns[3] * x);
}
template <typename T> inline tmat4x4<T> operator*(const T x, const tmat4x4<T>& m)
{
	return tmat4x4<T>(x * m._columns[0], x * m._columns[1], x * m._columns[2], x * m._columns[3]);
}
template <typename T> inline tmat4x4<T> operator/(const tmat4x4<T>& m0, const tmat4x4<T>& m1)
{
	return m0 * inverse(m1);
}
template <typename T> inline tvec4<T> operator/(const tmat4x4<T>& m, const tvec4<T>& v)
{
	return inverse(m) * v;
}
template <typename T> inline tvec4<T> operator/(const tvec4<T>& v, const tmat4x4<T>& m)
{
	return v * inverse(m);
}
template <typename T> inline tmat4x4<T> operator/(const tmat4x4<T>& m, const T x)
{
	return tmat4x4<T>(m._columns[0] / x, m._columns[1] / x, m._columns[2] / x, m._columns[3] / x);
}
template <typename T> inline tmat4x4<T> operator/(const T x, const tmat4x4<T>& m)
{
	return tmat4x4<T>(x / m._columns[0], x / m._columns[1], x / m._columns[2], x / m._columns[3]);
}

typedef tmat3x3<float> mat3;
typedef tmat3x3<int> imat3;
typedef tmat4x4<float> mat4;
typedef tmat4x4<int> imat4;
#endif

}
#endif
#ifndef FUZZY_H
#define FUZZY_H

#include <math.h>
#include <string.h>

#if !defined(swap)
template <typename T> inline void swap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}
#endif

#if !defined(max)
template <typename T> inline T max(T x, T y) { return x > y ? x : y; }
template <typename T> inline T max(T x, T y, T z) { return max(x, max(y, z)); }
#endif

#if !defined(min)
template <typename T> inline T min(T x, T y) { return x < y ? x : y; }
template <typename T> inline T min(T x, T y, T z) { return min(x, min(y, z)); }
#endif

#if !defined(interp)
template <typename T> inline T interp(float percent, T min, T max)
{
	if (min > max)
	{
		swap(min, max);
	}

	return min + (T)(percent * float(max - min));
}
#endif

#if !defined(truth)
template <typename T> inline T truth(T x) { return min(max(x, (T)0), (T)1); }
#endif

#if !defined(not)
template <typename T> inline T not(T x) { return (T)1 - truth(x); }
#endif

#if !defined(and)
template <typename T> inline T and(T x, T y) { return truth(x) * truth(y); }
#endif

#if !defined(or)
template <typename T> inline T or(T x, T y) { return truth(x + y); }
#endif

#if !defined(xor)
template <typename T> inline T xor(T x, T y) { return truth((x * ((T)1 - y)) + (((T)1 - x) * y)); }
#endif

#if !defined(fuzzy) && !defined(behavior)

class fuzzy
{
public:

#if 1
	typedef double valType;
#else
	typedef float valType;
#endif

	inline fuzzy() : _value((valType)0) {}
	inline fuzzy(const valType value) : _value(truth(value)) {}
	inline fuzzy(const fuzzy& value) : _value(value._value) {}
	inline ~fuzzy() {}

	inline void operator=(const bool value)
	{
		this->_value = value ? (valType)1 : (valType)0;
	}
	inline void operator=(const valType value)
	{
		this->_value = truth(value);
	}
	inline void operator=(const fuzzy& value)
	{
		this->_value = value._value;
	}
	inline operator bool() const
	{
		return this->_value >= (valType)0.5;
	}
	inline operator valType() const
	{
		return this->_value;
	}
	inline void operator+=(const valType x)
	{
		this->_value = truth(this->_value + x);
	}
	inline void operator-=(const valType x)
	{
		this->_value = truth(this->_value - x);
	}
	inline void operator*=(const valType x)
	{
		this->_value = truth(this->_value * x);
	}
	inline void operator/=(const valType x)
	{
		this->_value = truth(this->_value / x);
	}

	template <typename T> inline fuzzy fuzzify(const T x, const T min, const T max)
	{
		T _min = min;
		T _max = max;
		T _x = x;
		if (max < min)
		{
			_max = min;
		}

		if (min > max)
		{
			_min = max;
		}

		if (x < min)
		{
			_x = min;
		}
		else if (x > max)
		{
			_x = max;
		}

		return fuzzy((fuzzy::valType)(_x - _min) / (fuzzy::valType)(_max - _min));
	}

	template <typename T> static inline fuzzy fuzzifyHalf(const T x, const T min, const T max)
	{
		T _min = min;
		T _max = max;
		T _x = x;
		if (max < min)
		{
			_max = min;
		}

		if (min > max)
		{
			_min = max;
		}

		if (x < min)
		{
			_x = min;
		}
		else if (x > max)
		{
			_x = max;
		}

		return fuzzy((fuzzy::valType)(4 * (x - min) * (x - max)) / (fuzzy::valType)((max - min) * (min - max)));
	}

	template <typename T> inline T defuzzify(const fuzzy& x, const T min, const T max)
	{
		if (min == max)
		{
			return min;
		}

		return min + (T)((fuzzy::valType)x * (fuzzy::valType)(max - min));
	}

protected:

	valType _value;

};

inline fuzzy operator+(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x + (fuzzy::valType)y);
}
inline fuzzy operator+(const fuzzy& x, const fuzzy::valType y)
{
	return fuzzy((fuzzy::valType)x + y);
}
inline fuzzy operator+(const fuzzy::valType x, const fuzzy& y)
{
	return fuzzy(x + (fuzzy::valType)y);
}
inline fuzzy operator-(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x - (fuzzy::valType)y);
}
inline fuzzy operator-(const fuzzy& x, const fuzzy::valType y)
{
	return fuzzy((fuzzy::valType)x - y);
}
inline fuzzy operator-(const fuzzy::valType x, const fuzzy& y)
{
	return fuzzy(x - (fuzzy::valType)y);
}
inline fuzzy operator*(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x * (fuzzy::valType)y);
}
inline fuzzy operator*(const fuzzy& x, const fuzzy::valType y)
{
	return fuzzy((fuzzy::valType)x * y);
}
inline fuzzy operator*(const fuzzy::valType x, const fuzzy& y)
{
	return fuzzy(x * (fuzzy::valType)y);
}
inline fuzzy operator/(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x / (fuzzy::valType)y);
}
inline fuzzy operator/(const fuzzy& x, const fuzzy::valType y)
{
	return fuzzy((fuzzy::valType)x / y);
}
inline fuzzy operator/(const fuzzy::valType x, const fuzzy& y)
{
	return fuzzy(x / (fuzzy::valType)y);
}
inline bool operator==(const fuzzy& x, const fuzzy& y)
{
	fuzzy::valType d = y - x;
	return (d <= (fuzzy::valType)0.0001) && (d >= (fuzzy::valType) - 0.0001);
}
inline bool operator!=(const fuzzy& x, const fuzzy& y)
{
	return !(x == y);
}
inline bool operator>(const fuzzy& x, const fuzzy& y)
{
	return (fuzzy::valType)x > (fuzzy::valType)y;
}
inline bool operator<(const fuzzy& x, const fuzzy& y)
{
	return (fuzzy::valType)x < (fuzzy::valType)y;
}
inline bool operator>=(const fuzzy& x, const fuzzy& y)
{
	return (fuzzy::valType)x >= (fuzzy::valType)y;
}
inline bool operator<=(const fuzzy& x, const fuzzy& y)
{
	return (fuzzy::valType)x <= (fuzzy::valType)y;
}
inline fuzzy operator!(const fuzzy& x)
{
	return fuzzy((fuzzy::valType)1 - (fuzzy::valType)x);
}
inline fuzzy operator&&(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x * (fuzzy::valType)y);
}
inline fuzzy operator||(const fuzzy& x, const fuzzy& y)
{
	return fuzzy((fuzzy::valType)x + (fuzzy::valType)y);
}

class behavior
{
public:

	behavior() : _matrix(0), _size(0) {}
	behavior(const int size) : _matrix(new fuzzy[size]), _size(0) {}
	behavior(const behavior& b) : _matrix(new fuzzy[b._size]), _size(b._size)
	{
		memcpy(this->_matrix, b._matrix, sizeof(fuzzy) * b._size);
	}
	~behavior()
	{
		if (this->_matrix != 0)
		{
			delete[] this->_matrix;
		}
	}

	const int count() const
	{
		return this->_size;
	}
	bool inside(const int index) const
	{
		return index < this->_size && index >= 0;
	}

	inline void operator=(const behavior& b)
	{
		this->_size = b._size;
		this->_matrix = new fuzzy[this->_size];
		memcpy(this->_matrix, b._matrix, sizeof(fuzzy) * b._size);
	}
	inline operator const fuzzy*() const
	{
		return this->_matrix;
	}

	inline fuzzy& operator[](const int index)
	{
		return this->_matrix[index % this->_size];
	}

protected:

	fuzzy* _matrix;
	int _size;

};

inline fuzzy distance(const behavior& x, const behavior& y)
{
	fuzzy d((fuzzy::valType)0);
	int l = min(x.count(), y.count());
	for (int i = 0; i < l; i++)
	{
		d += (y[i] - x[i]) * (y[i] - x[i]);
	}

	return d;
}

inline fuzzy closeness(const behavior& x, const behavior& y)
{
	fuzzy d = distance(x, y);
	int l = min(x.count(), y.count());
	fuzzy n = sqrt((fuzzy::valType)l);

	return (n - d) / n;
}
inline fuzzy farness(const behavior& x, const behavior& y)
{
	return (fuzzy::valType)1 - closeness(x, y);
}

inline fuzzy compute(const behavior& conditions, const behavior& behaviors)
{
	if (conditions.count() < 1 || behaviors.count() < 1)
	{
		return fuzzy();
	}

	fuzzy result;
	for (int i = 0; behaviors.inside(i); i++)
	{
		fuzzy row = conditions[0];
		if (!(i & 1))
		{
			row = not(row);
		}

		for (int k = 1; k < conditions.count(); k++)
		{
			if (1 & (int)pow(2.0, k))
			{
				row = and(row, conditions[k]);
			}
			else
			{
				row = and(row, not(conditions[k]));
			}
		}

		result = or(result, behaviors[i] * row);
	}

	return result;
}
#endif

#endif
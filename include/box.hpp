#ifndef BOX_H
#define BOX_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#if !(defined(tbox) || defined(box))
template <typename T> struct tbox
{

	inline tbox() : p0((T)0), p1((T)0), center((T)0), width((T)0), height((T)0) {}
	inline tbox(const T width, const T height) :
		p0(-width / (T)2, -height / (T)2),
		p1(this->p0 + glm::tvec2<T>(width, height)),
		center((T)0),
		width(width),
		height(height) {}
	inline tbox(const glm::tvec2<T>& p0, const glm::tvec2<T>& p1) :
		p0(p0),
		p1(p1),
		center(((p1 - p0) / (T)2) + p0),
		width(p1.x - p0.x),
		height(p1.y - p0.y) {}
	inline tbox(const glm::tvec2<T>& p, const T width, const T height) :
		p0(p - tvec2<T>(width / (T)2, height / (T)2)),
		p1(this->p0 + glm::tvec2<T>(width, height)),
		center(p),
		width(width),
		height(height) {}
	inline ~tbox() {}

	inline void resize(const glm::tvec2<T>& size)
	{
		this->p0 = this->center - (size / (T)2);
		this->p1 = this->p0 + size;
		this->width = size.x;
		this->height = size.y;
	}
	inline void move(const glm::tvec2<T>& p)
	{
		this->p0 += p;
		this->p1 += p;
		this->center += p;
	}

	inline void operator=(const tbox<T>& b)
	{
		this->p0 = b.p0;
		this->p1 = b.p1;
		this->center = b.center;
		this->width = b.width;
		this->height = b.height;
	}
	inline tbox<T> operator+() const
	{
		return tbox<T>(+this->p0, +this->p1);
	}
	inline tbox<T> operator-() const
	{
		return tbox<T>(-this->p0, -this->p1);
	}
	inline void operator+=(const tbox<T>& b)
	{
		this->p0 += b.p0;
		this->p1 += b.p1;
		this->center += b.center;
	}
	inline void operator+=(const glm::tvec2<T>& p)
	{
		this->p0 += p;
		this->p1 += p;
		this->center += p;
	}
	inline void operator-=(const tbox<T>& b)
	{
		this->p0 -= b.p0;
		this->p1 -= b.p1;
		this->center -= b.center;
	}
	inline void operator-=(const glm::tvec2<T>& p)
	{
		this->p0 -= p;
		this->p1 -= p;
		this->center -= p;
	}
	inline bool operator==(const tbox<T>& b) const
	{
		return this->center == b.center && this->width == b.width && this->height == b.height;
	}
	inline bool operator!=(const tbox<T>& b) const
	{
		return this->center != b.center && this->width != b.width && this->height != b.height;
	}
	inline tbox<T> operator&&(const tbox<T>& b) const
	{
		return tbox<T>(this->p0 && b.p0, this->p1 && b.p1);
	}
	inline tbox<T> operator||(const tbox<T>& b) const
	{
		return tbox<T>(this->p0 || b.p0, this->p1 || b.p1);
	}

	glm::tvec2<T> p0;
	glm::tvec2<T> p1;
	glm::tvec2<T> center;
	T width;
	T height;

};

template <typename T> inline tbox<T> operator+(const tbox<T>& b0, const tbox<T>& b1)
{
	return tbox<T>(b0.center + b1.center, max(b0.width, b1.width), max(b0.height, b1.height));
}
template <typename T> inline tbox<T> operator+(const tbox<T>& b, const glm::tvec2<T>& x)
{
	return tbox<T>(b.center + x, b.width, b.height);
}
template <typename T> inline tbox<T> operator+(const glm::tvec2<T>& x, const tbox<T>& b)
{
	return tbox<T>(x + b.center, b.width, b.height);
}
template <typename T> inline tbox<T> operator-(const tbox<T>& b0, const tbox<T>& b1)
{
	return tbox<T>(b0.center - b1.center, min(b0.width, b1.width), min(b0.height, b1.height));
}
template <typename T> inline tbox<T> operator-(const tbox<T>& b, const glm::tvec2<T>& x)
{
	return tbox<T>(b.center - x, b.width, b.height);
}
template <typename T> inline tbox<T> operator-(const glm::tvec2<T>& x, const tbox<T>& b)
{
	return tbox<T>(x - b.center, b.width, b.height);
}
#endif

#endif